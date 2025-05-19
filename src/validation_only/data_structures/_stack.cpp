// // This file is no long needed.

// #include <iostream>
// // #include <vector>
// #include "mylib/data_structures/stack.hpp"

// // Constructor
// template <typename Type, int capacity>
// Stack<Type, capacity>::Stack() : m_top(-1) {}

// // Check if the stack is empty
// template <typename Type, int capacity>
// bool Stack<Type, capacity>::IsEmpty() const
// {
//     return m_top == -1;
// }

// // Check if the stack is full
// template <typename Type, int capacity>
// bool Stack<Type, capacity>::IsFull() const
// {
//     return m_top == capacity - 1;
// }

// // Push an element onto the stack
// template <typename Type, int capacity>
// bool Stack<Type, capacity>::Push(Type value)
// {
//     if (IsFull())
//     {
//         std::cout << "Stack Overflow" << std::endl;
//         return false;
//     }
//     m_stack[++m_top] = value;
//     return true;
// }

// // Pop an element from the stack
// template <typename Type, int capacity>
// Type Stack<Type, capacity>::Pop()
// {
//     if (IsEmpty())
//     {
//         throw std::underflow_error("Stack Underflow");
//     }
//     return m_stack[m_top--];
// }

// template <typename Type, int capacity>
// int Stack<Type, capacity>::Count() const
// {
//     return m_top + 1;
// }

// template <typename Type, int capacity>
// Type Stack<Type, capacity>::Peek(int position) const
// {
//     {
//         if (position > capacity && position < 0)
//         {
//             throw std::out_of_range("Out of Index");
//             ;
//         }
//         if (IsEmpty())
//         {
//             throw std::overflow_error("Overflow");
//             ;
//         }
//         return m_stack[position];
//     }
// }

// template <typename Type, int capacity>
// bool Stack<Type, capacity>::Change(int position, Type value)
// {
//     if (position > capacity && position < 0)
//     {
//         std::cout << "Out of Index" << std::endl;
//         return false;
//     }
//     if (IsEmpty())
//     {
//         std::cout << "Stack UnderFlow" << std::endl;
//         return false;
//     }

//     m_stack[position] = value;
//     return true;
// }

// template <typename Type, int capacity>
// void Stack<Type, capacity>::Display() const
// {
//     for (int idx = 0; idx < capacity; idx++)
//     {
//         std::cout << "Element {" << idx << "}: " << m_stack[idx] << std::endl;
//     }
// }