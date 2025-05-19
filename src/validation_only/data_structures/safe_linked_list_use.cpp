#include <iostream>
#include "mylib/data_structures/safe_linked_list.hpp"
#include "mylib/data_structures/safe_linked_list_node.hpp"

int main()
{
    const int CAPACITY = 5;
    SafeLinkedList<std::string, CAPACITY> list;

    std::unique_ptr<SafeNode<std::string>> node1 = std::make_unique<SafeNode<std::string>>(1, "Data1");
    std::unique_ptr<SafeNode<std::string>> node2 = std::make_unique<SafeNode<std::string>>(2, "Data2");
    std::unique_ptr<SafeNode<std::string>> node3 = std::make_unique<SafeNode<std::string>>(3, "Data3");

    try
    {
        list.AppendNode(std::move(node1));
        list.AppendNode(std::move(node2));
        list.PrependNode(std::move(node3));

        std::cout << "Linked List after appending and prepending nodes:" << std::endl;
        list.Display();

        SafeNode<std::string> *foundNode = list.SearchNode(2);
        if (foundNode)
            std::cout << "Found Node: " << *foundNode << std::endl;
        else
            std::cout << "Node with key 2 not found." << std::endl;

        list.DeleteNodeByKey(2);

        std::cout << "\nLinked List after deleting node with key 2:" << std::endl;
        list.Display();
    }
    catch (const std::underflow_error &e)
    {
        std::cerr << "Underflow error: " << e.what() << std::endl;
    }
    catch (const std::overflow_error &e)
    {
        std::cerr << "Overflow error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred!" << std::endl;
    }

    return 0;
}