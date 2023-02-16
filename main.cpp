#include <iostream>
#include <type_traits>

#include <template/arguments/extract.hpp>

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
  static constexpr Color BG = ta::Extract<BackgroundT<Color::Red>, Args...>::value;
  static constexpr Color FG = ta::Extract<ForegroundT<Color::Blue>, Args...>::value;

  static constexpr bool Same = FG == BG;
};

int main(int argc, const char* argv[]) {
  using T = S<ForegroundT<Color::Red>, BackgroundT<Color::Blue>>;
  std::cout << "Same: " << T::Same << std::endl;
  return 0;
}