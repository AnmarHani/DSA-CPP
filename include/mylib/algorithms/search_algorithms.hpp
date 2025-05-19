#pragma once

namespace Search
{
    template <typename Type>
    class Sequential
    {
    public:
        static int LinearSearch(const std::vector<Type> &data, const Type &target);
    };

    template <typename Type>
    class Interval
    {
    public:
        static int BinarySearch(const std::vector<Type> &data, const Type &target, int start_idx = NULL, int end_idx = NULL);
    };
}

#include <mylib/algorithms/templates/search_algorithms.tpp>