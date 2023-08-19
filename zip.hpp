#pragma once

#include <array>
#include <algorithm>
#include <tuple>
#include <functional>

#include "specializations.hpp"

namespace detail
{
    template<std::size_t I, typename ...List>
    constexpr auto tuple_Nt_elements(const List& ...lists)
    {
        return std::tuple{std::ref(get<I>(lists))...};
    }

    template<typename... List, std::size_t... Is>
    constexpr auto zip(std::index_sequence<Is...>, const List&... lists)
    {
        return std::array{tuple_Nt_elements<Is>(lists...)...};
    }
} // detail


template<typename... List>
constexpr auto zip(const List& ...lists)
{
    constexpr auto min = std::min({std::tuple_size_v<List>...});
    return detail::zip(std::make_index_sequence<min>{}, lists...);
}
