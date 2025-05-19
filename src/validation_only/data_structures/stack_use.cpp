#include <iostream>
#include "mylib/data_structures/stack.hpp"

int main()
{
    Stack<int, 10> stack;

    try
    {
        stack.Push(10);
        stack.Push(20);
        stack.Push(30);
        stack.Push(40);
        stack.Push(40);
        stack.Push(40);

        std::cout << "Is stack empty? " << (stack.IsEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is stack full? " << (stack.IsFull() ? "Yes" : "No") << std::endl;

        stack.Display();

        const int PEEK_INDEX = 5;

        std::cout << "Peeked Element at [" << PEEK_INDEX << "]: " << stack.Peek(PEEK_INDEX) << std::endl;

        // Example of popping elements to trigger underflow
        for (int i = 0; i < 6; ++i)
        {
            std::cout << "Popped: " << stack.Pop() << std::endl;
        }

        std::cout << "Is stack empty? " << (stack.IsEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is stack full? " << (stack.IsFull() ? "Yes" : "No") << std::endl;

        stack.Display();
    }
    catch (const std::underflow_error &e)
    {
        // Handle underflow error
        std::cerr << "Underflow error: " << e.what() << std::endl;
    }
    catch (const std::overflow_error &e)
    {
        // Handle overflow error
        std::cerr << "Overflow error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        // Handle any other standard exceptions
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        // Generic catch for any other type of exception
        std::cerr << "An unknown error occurred!" << std::endl;
    }

    std::cout << "Do you want to clear the cli? (Y/n) " << std::endl;

    char userChoice = 'Y';
    std::cin >> userChoice;

    if ((char) std::tolower(userChoice) == 'y')
        system("clear");

    return 0;
}