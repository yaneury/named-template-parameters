#pragma once

#include <type_traits>

#include <template/traits.hpp>

namespace ntp {

template <typename T> struct integral_type { using value = T; };

template <typename Default, typename... Args> struct type;

template <typename Default, typename T, typename... Args>
struct type<Default, T, Args...> {
  template <typename _UnusedDefault, typename _UnusedT, typename Enable = void>
  struct impl {
    using value = typename type<Default, Args...>::value;
  };

  template <typename ProvidedDefault, typename ProvidedT>
  struct impl<
      ProvidedDefault, ProvidedT,
      std::enable_if_t<detail::are_same<ProvidedDefault, ProvidedT>::value>> {
    using value = typename ProvidedT::value;
  };

  using value = typename impl<Default, T>::value;
};

template <typename Default> struct type<Default> {
  using value = typename Default::value;
};

} // namespace ntp
