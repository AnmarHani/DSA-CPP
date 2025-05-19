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
                std::cout << "Element Found at location: [" << i << "]" << std::endl;
                return i;
            }
        }
        std::cout << "Element Not Found! No Target as [" << std::to_string(target) << "]" << std::endl;

        return -1;
    }

    template <typename Type>
    int Interval<Type>::BinarySearch(const std::vector<Type> &data, const Type &target)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] == target)
            {
                std::cout << "Element Found at location: [" << i << "]" << std::endl;
                return i;
            }
        }
        std::cout << "Element Not Found! No Target as [" << std::to_string(target) << "]" << std::endl;

        return -1;
    }
}