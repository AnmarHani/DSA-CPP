#pragma once

#include <chrono>
#include <functional>
#include <type_traits>

template <typename T>
struct FunctionResult
{
    T result;
    double duration; // in Seconds
};

class Algorithm
{
private:
    Algorithm(); // Disable Constructor
public:
    template <typename Function, typename... Args>
    static FunctionResult<typename std::invoke_result_t<Function, Args...>>
    MeasureTimeComplexity(Function &&function, Args &&...args)
    {
        // Start the timer
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        // Call the function and get result
        typename std::invoke_result_t<Function, Args...> result =
            std::forward<Function>(function)(std::forward<Args>(args)...);

        // End the timer
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        // Calculate the duration in seconds
        std::chrono::duration<double> duration = end - start;

        // Return the result and the duration
        return FunctionResult<typename std::invoke_result_t<Function, Args...>>{result, duration.count()};
    }
};