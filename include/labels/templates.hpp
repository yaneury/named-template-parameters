#pragma once

#include <type_traits>

#include <labels/traits.hpp>

namespace labels {

// TODO: Add support for required fields
template <typename Default, typename... Args> struct Extract;

template <typename Default, typename T, typename... Args>
struct Extract<Default, T, Args...> {
  template <typename _UnusedDefault, typename _UnusedT, typename Enable = void>
  struct impl : std::integral_constant<decltype(Default::value),
                                       Extract<Default, Args...>::value> {};

  template <typename ProvidedDefault, typename ProvidedT>
  struct impl<ProvidedDefault, ProvidedT, std::enable_if_t<internal::IsSameTemplate<ProvidedDefault, ProvidedT>::value>>
      : std::integral_constant<decltype(Default::value), ProvidedT::value> {};

  static constexpr const auto value = impl<Default, T>::value;
};

template <typename Default>
struct Extract<Default>: std::integral_constant<decltype(Default::value), Default::value> {};

}