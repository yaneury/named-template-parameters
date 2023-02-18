#pragma once

#include <type_traits>

#include <template/traits.hpp>

namespace ntp {

template <typename Default, typename... Args> struct optional;

template <typename Default, typename T, typename... Args>
struct optional<Default, T, Args...> {
  template <typename _UnusedDefault, typename _UnusedT, typename Enable = void>
  struct impl : std::integral_constant<decltype(Default::value),
                                       optional<Default, Args...>::value> {};

  template <typename ProvidedDefault, typename ProvidedT>
  struct impl<
      ProvidedDefault, ProvidedT,
      std::enable_if_t<detail::are_same<ProvidedDefault, ProvidedT>::value>>
      : std::integral_constant<decltype(Default::value), ProvidedT::value> {};

  static constexpr const auto value = impl<Default, T>::value;
};

template <typename Default>
struct optional<Default>
    : std::integral_constant<decltype(Default::value), Default::value> {};

} // namespace ntp