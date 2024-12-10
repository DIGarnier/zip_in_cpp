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
        ptrs = {std::data(lists)...};
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
        next(seq);
        return *this;
    }

    zip_iterator& operator--()
    {
        previous(seq);
        return *this;
    }

    bool operator!=(zip_iterator& other)
    {
        return position != other.position;
    }

    auto& operator*() { return *reinterpret_cast<std::tuple<underlying_type_t<List>&...>*>(&ptrs); }

private:

    template<std::size_t... Is>
    void next(const std::index_sequence<Is...>&)
    {
        ++position;
        (std::get<Is>(ptrs)++,...);
    }

    template<std::size_t... Is>
    void previoust(const std::index_sequence<Is...>&)
    {
        --position;
        (std::get<Is>(ptrs)--,...);
    }

    std::size_t position{};
    std::size_t size{};
    std::tuple<underlying_type_t<List>*...> ptrs;
    static constexpr decltype(std::make_index_sequence<sizeof...(List)>{}) seq{};
};
