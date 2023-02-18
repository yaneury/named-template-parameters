#pragma once

#include <type_traits>

namespace ntp::detail {

template <typename T, typename U> struct are_same : std::false_type {};

template <template <typename...> typename T, typename... A, typename... B>
struct are_same<T<A...>, T<B...>> : std::true_type {};

// TODO: Add C++11, C++14 support with nested type
template <template <auto...> typename T, auto... A, auto... B>
struct are_same<T<A...>, T<B...>> : std::true_type {};

} // namespace ntp::detail