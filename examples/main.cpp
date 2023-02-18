#include <iostream>
#include <type_traits>

#include <template/parameters.hpp>

enum Color { None, Red, Green, Blue };

template <Color C> struct BackgroundT : std::integral_constant<Color, C> {};

template <Color C> struct ForegroundT : std::integral_constant<Color, C> {};

template <class... Args> struct S {
  static constexpr Color BG =
      ntp::optional<BackgroundT<Color::Red>, Args...>::value;
  static constexpr Color FG =
      ntp::required<ForegroundT<Color::None>, Args...>::value;

  static constexpr bool Same = FG == BG;
};

int main(int argc, const char* argv[]) {
  using T = S<ForegroundT<Color::Red>, BackgroundT<Color::Red>>;
  std::cout << "Same: " << T::Same << std::endl;
  return 0;
}