#pragma once
#include <vector>

namespace Sort
{
    template <typename Type>
    class Comparison {
        void BubbleSort(std::vector<Type> &data);
        void InsertionSort(std::vector<Type> &data);
        void SelectionSort(std::vector<Type> &data);
        void QuickSort(std::vector<Type> &data);
        void MergeSort(std::vector<Type> &data);
        void HeapSort(std::vector<Type> &data);
    };

    template <typename Type>
    class NonComparison {
        void CountingSort(std::vector<Type> &data);
        void RadixSort(std::vector<Type> &data);
    };

}

#include <mylib/algorithms/templates/sort_algorithms.tpp>