#pragma once
#include <iostream>
#include <stdexcept>

template <typename Type, int capacity>
class Stack {
private:
    int m_top;
    Type m_stack[capacity];

public:
    Stack() : m_top(-1) {}
    ~Stack() = default;

    bool Push(Type value) {
        if (IsFull()) {
            throw std::overflow_error("Stack Overflow");
        }
        m_stack[++m_top] = value;
        return true;
    }

    Type Pop() {
        if (IsEmpty()) {
            throw std::underflow_error("Stack Underflow");
        }
        return m_stack[m_top--];
    }

    Type Peek(int position) const {
        if (position < 0 || position > m_top) {
            throw std::out_of_range("Invalid position");
        }
        return m_stack[position];
    }

    int Count() const {
        return m_top + 1;
    }

    bool Change(int position, Type value) {
        if (position < 0 || position > m_top) {
            throw std::out_of_range("Invalid position");
        }
        
        m_stack[position] = value;
        return true;
    }

    bool IsEmpty() const {
        return m_top == -1;
    }

    bool IsFull() const {
        return m_top >= capacity - 1;
    }

    void Display() const {
        for (int i = 0; i <= m_top; ++i) {
            std::cout << "Element [" << i << "]: " << m_stack[i] << std::endl;
        }
    }
};