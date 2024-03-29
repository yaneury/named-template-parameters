#include <iostream>
#include <string>
#include <type_traits>

#include <template/parameters.hpp>

enum Engine { V4 = 1, V6 = 2 };

std::string ToString(Engine e) {
  if (e == Engine::V4)
    return "V4";
  return "V6";
}

template <Engine E> struct EngineT : std::integral_constant<Engine, E> {};

enum DriveTrain { Two = 4, Four = 8, All = 16 };

std::string ToString(DriveTrain dt) {
  if (dt == DriveTrain::Two)
    return "2WD";
  if (dt == DriveTrain::Four)
    return "4WD";
  if (dt == DriveTrain::All)
    return "AWD";
  return "UNKNOWN";
}

template <DriveTrain DT = DriveTrain()>
struct DriveTrainT : std::integral_constant<DriveTrain, DT> {};

struct Specs {
  Engine engine;
  DriveTrain dt;
};

template <class... Args> struct Car {
  static constexpr Engine E =
      ntp::optional<EngineT<Engine::V4>, Args...>::value;
  static constexpr DriveTrain DT =
      ntp::required<DriveTrainT<DriveTrain{}>, Args...>::value;
};

template <typename T> struct TypeT : ntp::integral_type<T> {};

template <class... Args> struct Vehicle {
  using V = typename ntp::type<TypeT<Car<>>, Args...>::value;
};

int main(int argc, const char* argv[]) {
  using V6CarWithAWD = Car<EngineT<Engine::V6>, DriveTrainT<DriveTrain::All>>;

  std::cout << "Engine: " << ToString(V6CarWithAWD::E) << std::endl;
  std::cout << "DriveTrain: " << ToString(V6CarWithAWD::DT) << std::endl;

  using V = Vehicle<TypeT<V6CarWithAWD>>;

  std::cout << "V.Engine: " << ToString(V::V::E) << std::endl;
  std::cout << "V.DriveTrain: " << ToString(V::V::DT) << std::endl;

  return 0;
}
