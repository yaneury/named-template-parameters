#include <string>
#include <iostream>

#if __cplusplus < 201103L 
namespace std{
template<bool B, typename T>
struct enable_if {};template<typename T>
struct enable_if<true, T> { typedef T type; };
}
#endif

#if __cplusplus < 201103L // Prior to C++11
template< bool B, class T = void >
struct enable_if_t : public std::enable_if<B, T> {};
#elif __cplusplus < 201402L // C++11
// `std::enablie_if_t` polyfill for C++11
template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;
#else // C++14 and above
using enable_if_t = std::enable_if_t;
#endif

template <typename Default, typename... Args> struct GetValueT;

template <typename Default, typename T2, typename... Args>
struct GetValueT<Default, T2, Args...> {
  template <typename D2, typename T22, typename Enable = void>
  struct impl : std::integral_constant<decltype(Default::value),
                                       GetValueT<Default, Args...>::value> {};

  template <typename Default2, typename T22>
  struct impl<Default2, T22,
              enable_if_t<std::is_same<typename Default2::Id_, typename T22::Id_>::value>>
      : std::integral_constant<decltype(Default::value), T22::value> {};

  static constexpr const auto value = impl<Default, T2>::value;
};

template <typename Default>
struct GetValueT<Default>
    : std::integral_constant<decltype(Default::value), Default::value> {};

// Library 

enum Engine {
  V4 = 1,
  V6 = 2
};

enum DriveTrain {
  Two = 4,
  Four = 8,
  All = 16
};

std::string ToString(Engine engine) {
  if (engine == Engine::V4)
    return "V4";
  return "V6";
}

std::string ToString(DriveTrain dt) {
  if (dt == DriveTrain::Two)
    return "Two";
  if (dt == DriveTrain::Four)
    return "Four";
  return "All";
}

struct Specs {
  Engine engine;
  DriveTrain dt;
};

struct EngineId {};

template <Engine E>
struct EngineT : std::integral_constant<Engine, E> {
  using Id_ = EngineId;
};

struct DriveTrainId {};

template <DriveTrain DT>
struct DriveTrainT : std::integral_constant<DriveTrain, DT> {
  using Id_ = DriveTrainId;
};

template <class ...Args>
class Car {
  public:
    Specs GetSpecs() const {
      return Specs{.engine = E, .dt = DT};
    }

  private:
    static constexpr Engine E = GetValueT<EngineT<Engine::V4>, Args...>::value;
    static constexpr DriveTrain DT = GetValueT<DriveTrainT<DriveTrain::Two>, Args...>::value;
};

using V6CarWithAWD = Car<EngineT<Engine::V6>, DriveTrainT<DriveTrain::All>>;

int main(int argc, const char* argv[]) {
  constexpr auto car = V6CarWithAWD();

  std::cout << "Engine: " << ToString(car.GetSpecs().engine) << std::endl;
  std::cout << "DriveTrain: " << ToString(car.GetSpecs().dt) << std::endl;

  return 0;
}