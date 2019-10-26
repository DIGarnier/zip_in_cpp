#include <vector>
#include <array>
#include <iostream>
#include "zip_iterator.hpp"
#include "zip.hpp"

int main()
{
    auto vec = std::vector{1,2,3,4,5};
    auto arr = std::array{5,4,3,2,1};
    int c_arr[] = {4,4,4,4,4};

    for(auto& [a, b]: zip_iterator(arr, c_arr)){
        std::cout << a << " " << b  << std::endl;
    }

    return 1;
}