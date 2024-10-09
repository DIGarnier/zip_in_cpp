#pragma once

#include <array>
#include <tuple>
#include "type_utils.hpp"

template<typename... List>
class zip_iterator
{
public:
    explicit zip_iterator(List& ...lists)
    {
        begin_ptrs = {static_cast<const void*>(std::data(lists))...};
        size = std::min({std::size(lists)...});
    }

    zip_iterator begin()
    {
        auto copy = *this;
        copy.position = 0;
        return copy;
    }
    zip_iterator end()
    {
        auto copy = *this;
        copy.position = size;
        return copy;
    }
    zip_iterator& operator++()
    {
        ++position;
        return *this;
    }

    bool operator!=(zip_iterator& other)
    {
        return position != other.position;
    }

    auto operator*(){ return get_Nt_tuple();};

    auto get_Nt_tuple()
    {
        return get_Nt_tuple_impl(seq);
    }

private:

    template<std::size_t... Is>
    auto get_Nt_tuple_impl(std::index_sequence<Is...>)
    {
        return std::tuple{*(static_cast<underlying_type_t<List> *>(begin_ptrs[Is]) + position)...};
    }

    std::size_t position{};
    std::size_t size{};
    std::array<const void*, sizeof...(List)> begin_ptrs;
    decltype(std::make_index_sequence<sizeof...(List)>{}) seq{};
};

