#pragma once
#include <vector>

namespace Sort
{
    template <typename Type>
    void Comparison<Type>::BubbleSort(std::vector<Type> &data) noexcept {
        const std::size_t vectorSize = data.size();
        if (vectorSize < 2) return;


        // 1. With the first counter start from 0, then start the second counter
        // 2. The second counter starts from 0, ends from the last sorted digit. (Whenever the element is getting swapped, we ensure that the last element is sorted, and the margin of ensured sorted numbers (largest) from the right)
        // 3. Compare every two elements in the array
        for (std::size_t pass = 0; pass < vectorSize - 1; ++pass)
        {
            bool didSwap = false;   // reset at the start of each pass

            for (std::size_t counter = 0; counter < vectorSize - pass - 1; ++counter)
            {
                if (data[counter] > data[counter + 1])
                {
                    std::swap(data[counter], data[counter + 1]);
                    didSwap = true;
                }
            }

            // if already sorted then exit.
            if (!didSwap) break;
        }
    }

    template <typename Type>
    void Comparison<Type>::BubbleSort(std::vector<Type> &data) noexcept {
        const std::size_t vectorSize = data.size();
        if (vectorSize < 2) return;


        // 1. With the first counter start from 0, then start the second counter
        // 2. The second counter starts from 0, ends from the last sorted digit. (Whenever the element is getting swapped, we ensure that the last element is sorted, and the margin of ensured sorted numbers (largest) from the right)
        // 3. Compare every two elements in the array
        for (std::size_t pass = 0; pass < vectorSize - 1; ++pass)
        {
            bool didSwap = false;   // reset at the start of each pass

            for (std::size_t counter = 0; counter < vectorSize - pass - 1; ++counter)
            {
                if (data[counter] > data[counter + 1])
                {
                    std::swap(data[counter], data[counter + 1]);
                    didSwap = true;
                }
            }

            // if already sorted then exit.
            if (!didSwap) break;
        }
    }


}