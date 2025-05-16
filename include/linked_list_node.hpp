#pragma once

template <typename DataType>
class Node
{
public:
    int key;
    DataType data;
    Node *next;
    Node *prev;

    Node() : key(0), next(nullptr), prev(nullptr), data(NULL) {}
    ~Node() = default;

};