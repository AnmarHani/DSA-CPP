#pragma once
#include <vector>

namespace Search
{
    template <typename Type>
    int Sequential<Type>::LinearSearch(const std::vector<Type> &data, const Type &target)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] == target)
            {
                return i;
            }
        }

        return -1;
    }

    template <typename Type>
    int Interval<Type>::BinarySearch(const std::vector<Type> &data, const Type &target, int start_idx, int end_idx)
    {
        if (start_idx > end_idx)
            return -1;

        if (start_idx == NULL && end_idx == NULL)
        {
            start_idx = 0;
            end_idx = data.size() - 1;
        }

        int mid_idx = static_cast<int>(start_idx + (end_idx - start_idx) / 2);
        if (data[mid_idx] == target)
            return mid_idx;

        if (data[mid_idx] < target)
            return Interval<Type>::BinarySearch(data, target, (mid_idx + 1), end_idx);

        return Interval<Type>::BinarySearch(data, target, start_idx, (mid_idx - 1));
    }
}