#pragma once
#include <iostream>

template <typename DataType>
class SafeNode
{
public:
    int key;
    DataType data;
    std::unique_ptr<SafeNode<DataType>> next;
    SafeNode<DataType> *prev;

    SafeNode(int k, const DataType &d) : key(k), data(d), next(nullptr), prev(nullptr)
    {
        std::cout << "SafeNode Created" << std::endl;
    }
    ~SafeNode()
    {
        std::cout << "SafeNode Deleted" << std::endl;
    };

    friend std::ostream &operator<<(std::ostream &os, const SafeNode &node)
    {
        os << "Node Key: [" << node.key << "]"
           << "\tNode Data: [" << node.data << "]"
           << "\tNode Next: [" << (node.next ? std::to_string(node.next->key) : "nullptr") << "]"
           << "\tNode Previous: [" << (node.prev ? std::to_string(node.prev->key) : "nullptr") << "]";
        return os;
    }
};