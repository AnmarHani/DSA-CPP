#pragma once
#include <iostream>
#include <stdexcept>

template <typename Type, int capacity>
class CircularQueue
{
private:
    int m_front;
    int m_rear;
    int m_queue[capacity];

public:
    CircularQueue() : m_front(-1), m_rear(-1)
    {
        std::fill(m_queue, m_queue + capacity, 0);
    }
    ~CircularQueue() = default;

    Type Enqueue(Type value)
    {
        if (IsFull())
            throw std::overflow_error("Queue Overflow");

        if (IsEmpty())
            m_rear = m_front = 0; // Becuase we wouldnt store in index -1
        else
            m_rear = (m_rear + 1) % capacity;

        m_queue[m_rear] = value;

        return true;
    }

    Type Dequeue()
    {
        Type temp;

        if (IsEmpty())
            throw std::underflow_error("Queue Underflow");

        if (m_front == m_rear) // Only for the first element, they be at the same position.
        {
            temp = m_queue[m_front]; // Either front or rear, no difference.

            m_queue[m_front] = 0;
            m_queue[m_rear] = 0;

            m_front = m_rear = -1;

            return temp;
        }

        // If not empty nor single element, the elements will be removed from the front (and inserted from the rear),
        // so, here, we will remove from the front.

        temp = m_queue[m_front];
        m_queue[m_front] = 0;
        m_front = (m_front + 1) % capacity;

        return temp;
    }

    Type Peek(int position) const
    {
        if (position < 0 || position > Count())
        {
            throw std::out_of_range("Invalid position");
        }
        return m_queue[position];
    }

    int Count() const
    {
        int currentQueueCapacity = sizeof(m_queue) / sizeof(Type);
        return currentQueueCapacity;
    }

    bool Change(int position, Type value)
    {
        if (position < 0 || position > capacity)
        {
            throw std::out_of_range("Invalid position");
        }

        m_queue[position] = value;
        return true;
    }

    bool IsEmpty() const
    {
        return m_rear == -1 && m_front == -1;
    }

    bool IsFull() const
    {
        return (m_rear + 1) % capacity == m_front;
    }

    void Display() const
    {
        for (int idx = 0; idx <= Count(); idx++)
        {
            std::cout << "Element [" << idx << "]: " << m_queue[idx] << std::endl;
        }
    }
};