#pragma once
#include <iostream>

template <typename DataType>
class Node
{
public:
    int key;
    DataType data;
    Node *next;
    Node *prev;

    Node() : key(1), next(nullptr), prev(nullptr), data(NULL) {}
    Node(int key, const DataType &data, Node *next = nullptr, Node *prev = nullptr)
        : key(key), data(data), next(next), prev(prev) {}
    ~Node() = default;

    friend std::ostream &operator<<(std::ostream &os, const Node &node)
    {
        os << "Node Key: [" << node.key << "]"
           << "\tNode Next: [" << (node.next ? std::to_string(node.next->key) : "nullptr") << "]"
           << "\tNode Previous: [" << (node.prev ? std::to_string(node.prev->key) : "nullptr") << "]";
        return os;
    }
};