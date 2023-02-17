#pragma once

#include <type_traits>

#include <template/traits.hpp>

namespace ta {

template <typename Default, typename... Args> struct required;

template <typename Default, typename T, typename... Args>
struct required<Default, T, Args...> {
  template <typename _UnusedDefault, typename _UnusedT, typename Enable = void>
  struct impl : std::integral_constant<decltype(Default::value),
                                       required<Default, Args...>::value> {};

  template <typename ProvidedDefault, typename ProvidedT>
  struct impl<
      ProvidedDefault, ProvidedT,
      std::enable_if_t<detail::are_same<ProvidedDefault, ProvidedT>::value>>
      : std::integral_constant<decltype(Default::value), ProvidedT::value> {};

  static constexpr const auto value = impl<Default, T>::value;
};

} // namespace ta
