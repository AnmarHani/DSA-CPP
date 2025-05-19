#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <mylib/data_structures/safe_linked_list_node.hpp>

template <typename DataType, int capacity>
class SafeLinkedList
{
private:
    std::unique_ptr<SafeNode<DataType>> m_head;
    SafeNode<DataType> *m_tail;
    int m_size;

public:
    SafeLinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        std::cout << "SafeLinkedList Created" << std::endl;
    }
    ~SafeLinkedList()
    {
        std::cout << "SafeLinkedList Deleted" << std::endl;
    };

    bool IsEmpty() const { return m_size == 0; }
    bool IsFull() const { return m_size == capacity; }

    void AppendNode(std::unique_ptr<SafeNode<DataType>> newNode)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (IsEmpty())
        {
            // First node in the list
            m_head = std::move(newNode);
            m_tail = m_head.get();
            m_head->next = nullptr;
            m_head->prev = nullptr;
        }
        else
        {
            // Append to the end
            newNode->prev = m_tail;
            m_tail->next = std::move(newNode);
            m_tail = m_tail->next.get();
        }

        ++m_size;
    }

    void PrependNode(std::unique_ptr<SafeNode<DataType>> newNode)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (IsEmpty())
        {
            // First node in the list
            m_head = std::move(newNode);
            m_tail = m_head.get();
            m_head->next = nullptr;
            m_head->prev = nullptr;
        }
        else
        {
            // Prepend to the beginning
            newNode->next = std::move(m_head);
            newNode->prev = nullptr;
            newNode->next->prev = newNode.get();
            m_head = std::move(newNode);
        }

        ++m_size;
    }

    void DeleteNodeByKey(int key)
    {
        if (IsEmpty())
            throw std::underflow_error("LinkedList Underflow");

        SafeNode<DataType> *current = m_head.get();

        while (current && current->key != key)
        {
            current = current->next.get();
        }

        if (!current)
            throw std::invalid_argument("Node with the given key not found");

        if (current == m_head.get())
        {
            // Deleting the head
            m_head = std::move(current->next);
            if (m_head)
                m_head->prev = nullptr;
            else
                m_tail = nullptr; // List is now empty
        }
        else if (current == m_tail)
        {
            // Deleting the tail
            m_tail = m_tail->prev;
            m_tail->next.reset();
        }
        else
        {
            // Deleting a middle node
            current->prev->next = std::move(current->next);
            if (current->prev->next)
                current->prev->next->prev = current->prev;
        }

        --m_size;
    }

    SafeNode<DataType>* SearchNode(int key) const
    {
        SafeNode<DataType>* current = m_head.get();

        while (current)
        {
            if (current->key == key)
                return current;

            current = current->next.get();
        }

        return nullptr; // Node not found
    }

    void Display() const
    {
        if (IsEmpty())
        {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        SafeNode<DataType> *current = m_head.get();
        while (current)
        {
            std::cout << *current << std::endl;
            current = current->next.get();
        }
    }
};