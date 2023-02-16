#include <iostream>
#include <type_traits>

template<typename T, typename U>
struct is_same_template : std::false_type {};

template<template<typename...> typename T, typename... A, typename... B>
struct is_same_template<T<A...>, T<B...>> : std::true_type {};

template<template<auto...> typename T, auto... A, auto... B>
struct is_same_template<T<A...>, T<B...>> : std::true_type {};

template <typename Default, typename... Args> struct GetValueT;

template <typename Default, typename T2, typename... Args>
struct GetValueT<Default, T2, Args...> {
  template <typename D2, typename T22, typename Enable = void>
  struct impl : std::integral_constant<decltype(Default::value),
                                       GetValueT<Default, Args...>::value> {};

  template <typename Default2, typename T22>
  struct impl<Default2, T22, std::enable_if_t<is_same_template<Default2, T22>::value>>
      : std::integral_constant<decltype(Default::value), T22::value> {};

  static constexpr const auto value = impl<Default, T2>::value;
};

template <typename Default>
struct GetValueT<Default>: std::integral_constant<decltype(Default::value), Default::value> {};

enum Color {
  Red,
  Green,
  Blue
};

template <Color C>
struct BackgroundT : std::integral_constant<Color, C> {};

template <Color C>
struct ForegroundT : std::integral_constant<Color, C> {};

template <class ...Args>
struct S {
  static constexpr Color BG = GetValueT<BackgroundT<Color::Red>, Args...>::value;
  static constexpr Color FG = GetValueT<ForegroundT<Color::Blue>, Args...>::value;

  static constexpr bool Same = FG == BG;
};

int main(int argc, const char* argv[]) {
  using T = S<ForegroundT<Color::Red>, BackgroundT<Color::Red>>;
  std::cout << "Same: " << T::Same << std::endl;
  return 0;
}