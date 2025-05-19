#include <iostream>
#include <vector>
#include <mylib/algorithms/search_algorithms.hpp>
#include <mylib/algorithms/algorithms_interface.hpp>

int main()
{

    std::vector<int> testArray = {1, 2, 4, 52, 3, 12, 4};
    std::vector<int> testArraySecond(1000000, 42); // Creates a vector of size 1000000 with all elements set to 42

    // int isFound = Search::Sequential<int>::LinearSearch(testArray, 52);
    // int isFoundSecond = Search::Sequential<int>::LinearSearch(testArraySecond, 52);

    // int isBinaryFound = Search::Interval<int>::BinarySearch(testArray, 52);
    // int isBinaryFoundSecond = Search::Interval<int>::BinarySearch(testArraySecond, 52);

    FunctionResult<int> isFound = Algorithm::MeasureTimeComplexity(std::bind(&Search::Sequential<int>::LinearSearch, testArray, 52));
    FunctionResult<int> isBinaryFound = Algorithm::MeasureTimeComplexity([&]()
                                                                         { return Search::Interval<int>::BinarySearch(testArray, 52); });

    FunctionResult<int> isFoundSecond = Algorithm::MeasureTimeComplexity(std::bind(&Search::Sequential<int>::LinearSearch, testArraySecond, 52));
    FunctionResult<int> isBinaryFoundSecond = Algorithm::MeasureTimeComplexity([&]()
                                                                               { return Search::Interval<int>::BinarySearch(testArraySecond, 52); });

    std::cout << "Linear First Found? " << (isFound.result != -1 ? "True" : "False") << " With Time [" << std::to_string(isFound.duration) << "]" << ", Linear Second Found? " << (isFoundSecond.result != -1 ? "True" : "False") << " With Time [" << std::to_string(isFoundSecond.duration) << "]" << std::endl;
    std::cout << "Binary First Found?  " << (isBinaryFound.result != -1 ? "True" : "False") << " With Time [" << std::to_string(isBinaryFound.duration) << "]" << ", Binary Second Found? " << (isBinaryFoundSecond.result != -1 ? "True" : "False") << " With Time [" << std::to_string(isBinaryFoundSecond.duration) << "]" << std::endl;

    return 0;
}