#pragma once

#include <array>
#include <algorithm>
#include <tuple>
#include <functional>

#include "specializations.h"



namespace detail
{
    template<size_t N, typename ...List>
	constexpr auto tuple_Nt_elements(List &... list)
	{
		return std::tuple{std::ref(get<N>(list))...};
	}

    template<typename... List, std::size_t... Is>
    constexpr auto zip(std::index_sequence<Is...>, List &... list)
    {
        return std::array{tuple_Nt_elements<Is>(list...)...};
    }    
} // detail


template<typename... List>
constexpr auto zip(List &... list)
{
    constexpr auto min_max = std::minmax({std::tuple_size_v<List>...});
    static_assert(min_max.first == min_max.second, "Only same size containers can be zipped");
    return detail::zip(std::make_index_sequence<min_max.first>{}, list...);
}