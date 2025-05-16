#pragma once
#include <iostream>
#include <stdexcept>
#include <linked_list_node.hpp>

// Double-Circular Linked List
template <int capacity>
class LinkedList
{
private:
    Node *m_head;
    Node *m_tail;
    Node *m_list[capacity];

    Node *getLastNode() const
    {
        if (IsEmpty())
            throw std::underflow_error("LinkedList is Empty!");

        Node *ptr = head;

        while (ptr->next != NULL)
            ptr = ptr->next;

        return ptr;
    }

public:
    LinkedList()
    {
        m_head = NULL;
    };
    LinkedList(Node *node)
    {
        m_head = node;
    };
    ~LinkedList() = default;

    bool AppendNode(Node *node)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (SearchNode((node->key) != NULL)) // Key already exists.
            throw std::exception("Key Already Exists!");

        if (m_head == NULL)
        {
            m_head = node; // Assign head to current node.
            return true;
        }

        Node *lastNode = getLastNode();
        lastNode->next = node;

        return true;
    }

    bool PrependNode(Node *node)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        if (SearchNode((node->key) != NULL)) // Key already exists.
            throw std::exception("Key Already Exists!");

        if (m_head == NULL)
        {
            m_head = node; // Assign head to current node.
            return true;
        }

        node->next = m_head;
        m_head->prev = node;
        m_head = node;

        return true;
    }

    bool InsertNodeAfter(int key, Node *node)
    {
        if (IsFull())
            throw std::overflow_error("LinkedList Overflow");

        Node *currentNodeWithKey = SearchNode(key);

        if (currentNodeWithKey == NULL) // There is no Node within the Requested Key.
            throw std::exception("No Key was Found!");

        if (SearchNode((node->key) != NULL)) // Node is already inserted with a Key.
            throw std::exception("Node is Already Inserted with a Key [%s]!", std::string(node->key));

        node->next = currentNodeWithKey->next;
        node->prev = currentNodeWithKey;
        currentNodeWithKey->prev = node->prev;
        currentNodeWithKey->next = node;

        return true;
    }

    Node *DeleteNode()
    {
        if (IsEmpty())
            throw std::underflow_error("LinkedList Underflow");

        return m_stack[m_top--];
    }

    Node *SearchNode(int key) const
    {
        if (key < 0 || key > capacity)
            throw std::out_of_range("Invalid key");

        Node *temp = NULL;

        Node *ptr = m_head;

        while (ptr != NULL)
        {
            if (ptr->key == key)
                temp = ptr;

            ptr = ptr->next;
        }

        // if (temp == NULL)
        //     throw std::exception("Key not Found!");

        return temp;
    }

    int Count() const
    {
        return sizeof(m_list) / sizeof(Node);
    }

    bool IsEmpty() const
    {
        return m_head == NULL;
    }

    bool IsFull() const
    {
        return sizeof(m_list) / sizeof(Node) == capacity;
    }

    std::ostream &operator<<(std::ostream &os, const Node &node) const
    {
        os << "Node Key: [" << node.key << "]"
           << "\tNode Next: [" << (node.next ? std::to_string(node.next->key) : "nullptr") << "]"
           << "\tNode Previous: [" << (node.prev ? std::to_string(node.prev->key) : "nullptr") << "]";
        return os;
    }

    void Display() const
    {
        Node *current = m_head;
        int index = 0;

        while (current != nullptr)
        {
            std::cout << "Node [" << index << "]: " << *current << std::endl;
            current = current->next;
            index++;
        }
    }
};
