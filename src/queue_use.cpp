#include <iostream>
#include "queue.hpp"

int main()
{
    Queue<int, 10> queue;

    try
    {
        queue.Enqueue(10);
        queue.Enqueue(20);
        queue.Enqueue(30);
        queue.Enqueue(40);
        queue.Enqueue(50);
        queue.Enqueue(60);
        queue.Enqueue(70);
        queue.Enqueue(80);

        std::cout << "Is queue empty? " << (queue.IsEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is queue full? " << (queue.IsFull() ? "Yes" : "No") << std::endl;

        queue.Display();

        const int PEEK_INDEX = 5;

        std::cout << "Peeked Element at [" << PEEK_INDEX << "]: " << queue.Peek(PEEK_INDEX) << std::endl;

        // Example of popping elements to trigger underflow
        for (int i = 0; i < 6; ++i)
        {
            std::cout << "Dequeued: " << queue.Dequeue() << std::endl;
        }

        std::cout << "Is queue empty? " << (queue.IsEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is queue full? " << (queue.IsFull() ? "Yes" : "No") << std::endl;

        queue.Enqueue(10);
        queue.Enqueue(20);
        queue.Enqueue(30);
        queue.Enqueue(40);
        queue.Enqueue(50);
        queue.Enqueue(60);
        queue.Enqueue(70);
        queue.Enqueue(80);
        queue.Enqueue(10);
        queue.Enqueue(20); // Trigger Overflow
        queue.Enqueue(30);
        queue.Enqueue(40);
        queue.Enqueue(50);
        queue.Enqueue(60);
        queue.Enqueue(70);
        queue.Enqueue(80);

        queue.Display();
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

    if ((char)std::tolower(userChoice) == 'y')
        system("clear");

    return 0;
}