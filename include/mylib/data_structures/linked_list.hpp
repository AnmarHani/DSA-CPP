#pragma once
#include <iostream>
#include <stdexcept>
#include <mylib/data_structures/linked_list_node.hpp>

/**
 * @brief Double-Circular Linked List.
 *
 * @tparam NodesDataType The type of data each node in the linked list holds.
 * @tparam capacity The fixed capacity of the linked list.
 *
 * @note Time Complexity: O(n)
 * @note Space Complexity: O(1)
 *
 * @throws std::invalid_argument if an operation receives invalid input.
 *
 * @example
 * LinkedList<int, 10> list1{};                     // Preferred default construction
 * auto list2 = std::make_unique<LinkedList<int, 10>>(); // Smart pointer (unique), Preferred for exclusive ownership.
 * auto list3 = std::make_shared<LinkedList<int, 10>>(); // Smart pointer (shared), Use when multiple objects share the same instance.
 *
 * // Not Recommended:
 * LinkedList<int, 10>* list4 = new LinkedList<int, 10>(); // Manual delete required
 * delete list4;
 * 
 * // Not Recommended:
 * LinkedList<int, 10> list(); // This does NOT create an object "Most Vexing Parse". It is a function named list returning a LinkedList<int, 10>.
 */
template <typename NodesDataType, int capacity>
class LinkedList
{
private:
    Node<NodesDataType> *m_head;
    Node<NodesDataType> *m_tail;

    Node<NodesDataType> *getLastNode() const
    {
        if (IsEmpty())
            throw std::underflow_error("LinkedList is Empty!");

        Node<NodesDataType> *ptr = m_head;

        while (ptr->next != m_head) // Traverse until the last node<NodesDataType> in the circular list
            ptr = ptr->next;

        return ptr;
    }

public:
    LinkedList()
    {
        m_head = NULL;
    };
    LinkedList(Node<NodesDataType> *node)
    {
        m_head = node;
    };
    ~LinkedList() = default;

    Node<NodesDataType> *UpdateNodeByKey(int key, NodesDataType data)
    {
        if (IsEmpty())
            throw std::underflow_error("LinkedList is Empty!");

        Node<NodesDataType> *searchedNode = SearchNode(key);

        if (searchedNode == NULL) // Key doesnt exist.
            throw std::runtime_error("Key Doesnt Exist!");

        searchedNode->data = data;

        return searchedNode;
    }

    bool AppendNode(Node<NodesDataType> *node)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (SearchNode(node->key) != NULL) // Key already exists.
            throw std::runtime_error("Key Already Exists!");

        if (m_head == NULL)
        {
            // First node<NodesDataType> in the list
            m_head = node;
            m_tail = node;
            node->next = node; // Circular link
            node->prev = node;
            return true;
        }

        // Append to the end
        m_tail->next = node;
        node->prev = m_tail;
        node->next = m_head;
        m_head->prev = node;
        m_tail = node; // Update tail

        return true;
    }

    bool PrependNode(Node<NodesDataType> *node)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (SearchNode(node->key) != NULL) // Key already exists.
            throw std::runtime_error("Key Already Exists!");

        if (m_head == NULL)
        {
            // First node<NodesDataType> in the list
            m_head = node;
            m_tail = node;
            node->next = node; // Circular link
            node->prev = node;
            return true;
        }

        // Prepend to the beginning
        node->next = m_head;
        node->prev = m_tail;
        m_head->prev = node;
        m_tail->next = node;
        m_head = node; // Update head

        return true;
    }

    bool InsertNodeAfter(int key, Node<NodesDataType> *node)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (SearchNode(node->key) != NULL) // Node<NodesDataType> is already inserted with a Key.
            throw std::runtime_error("Node<NodesDataType> is Already Inserted with a Key!");

        Node<NodesDataType> *currentNodeWithKey = SearchNode(key);

        if (currentNodeWithKey == NULL) // Key not found
            throw std::runtime_error("No Key was Found!");

        // Update tail if inserted after the tail
        if (currentNodeWithKey == m_tail)
            return AppendNode(node);

        node->next = currentNodeWithKey->next;
        node->prev = currentNodeWithKey;

        currentNodeWithKey->next->prev = node;
        currentNodeWithKey->next = node;

        return true;
    }

    bool DeleteNodeByKey(int key)
    {
        if (IsEmpty())
            throw std::underflow_error("LinkedList Underflow");

        Node<NodesDataType> *nodeToDelete = SearchNode(key);

        if (nodeToDelete == NULL)
            throw std::runtime_error("Key Not Found!");

        if (nodeToDelete == m_head && nodeToDelete == m_tail)
        {
            // Only one node<NodesDataType> in the list
            m_head = NULL;
            m_tail = NULL;

            delete nodeToDelete;
            return true;
        }

        if (nodeToDelete == m_head)
        {
            // Deleting the head
            m_head = m_head->next;
            m_head->prev = m_tail;
            m_tail->next = m_head;

            delete nodeToDelete;
            return true;
        }

        if (nodeToDelete == m_tail)
        {
            // Deleting the tail
            m_tail = m_tail->prev;
            m_tail->next = m_head;
            m_head->prev = m_tail;

            delete nodeToDelete;
            return true;
        }

        // Deleting a middle node
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;

        delete nodeToDelete;
        return true;
    }

    Node<NodesDataType> *SearchNode(int key) const
    {

        if (IsEmpty())
            return NULL;

        Node<NodesDataType> *ptr = m_head;

        do
        {
            if (ptr->key == key)
                return ptr;

            ptr = ptr->next;
        } while (ptr != m_head); // Stop after one full cycle

        return NULL;
    }

    int Count() const
    {
        if (IsEmpty())
            return 0;

        int count = 0;
        Node<NodesDataType> *current = m_head;

        do
        {
            count++;
            current = current->next;
        } while (current != m_head); // Stop after one full cycle

        return count;
    }

    bool IsEmpty() const
    {
        // The list is empty if the head pointer is NULL

        return m_head == NULL;
    }

    bool IsFull() const
    {
        // The list is empty if the head pointer is NULL

        return Count() == capacity;
    }

    void Display() const
    {
        if (IsEmpty())
        {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        Node<NodesDataType> *current = m_head;

        do
        {
            std::cout << *current << std::endl;
            current = current->next;
        } while (current != m_head); // Stop after one full cycle
    }
};
