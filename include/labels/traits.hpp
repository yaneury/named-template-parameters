#pragma once

#include <type_traits>

namespace labels::internal {

template<typename T, typename U>
struct IsSameTemplate : std::false_type {};

template<template<typename...> typename T, typename... A, typename... B>
struct IsSameTemplate<T<A...>, T<B...>> : std::true_type {};

// TODO: Add C++11, C++14 support with nested type
template<template<auto...> typename T, auto... A, auto... B>
struct IsSameTemplate<T<A...>, T<B...>> : std::true_type {};

}