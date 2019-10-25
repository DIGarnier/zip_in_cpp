#pragma once

#include <tuple>

namespace std
{
  template<typename T, std::size_t Size>
  struct tuple_size<T[Size]> : public std::integral_constant<std::size_t, Size> {};
}

template <std::size_t I, typename T, std::size_t Size>
constexpr T& get (T(&c_array)[Size]) { return c_array[I]; }

template <std::size_t I, typename T, std::size_t Size>
constexpr T get (T(&c_array)[Size]) { return c_array[I]; }