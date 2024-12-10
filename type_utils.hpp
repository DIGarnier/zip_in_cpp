#pragma once
#include <cstddef>

template<typename T>
constexpr auto underlying_type = T{};

template<typename T>
using underlying_type_t = decltype(underlying_type<T>);

// specialization for std::array
template<typename T, std::size_t N>
constexpr auto underlying_type<std::array<T, N>> = T{};

// specialization for std::vector
template<typename T, typename ...Args>
constexpr auto underlying_type<std::vector<T, Args...>> = T{};

 // specialization for c-array
template<typename T, std::size_t N>
constexpr auto  underlying_type<T[N]> = T{};
