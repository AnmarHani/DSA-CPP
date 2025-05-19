#include <iostream>
#include <mylib/data_structures/linked_list.hpp>
#include <mylib/data_structures/linked_list_node.hpp>

int main()
{
    // Define the capacity of the linked list
    const int CAPACITY = 5;

    // Create a linked list with the specified CAPACITY
    LinkedList<std::string, CAPACITY> list;

    try
    {
        // Unsafe Memory Allocation (Need to manually delete pointers or free memory)
        Node<std::string> *node1 = new Node<std::string>(1, "Data1");
        Node<std::string> *node2 = new Node<std::string>(2, "Data2");
        Node<std::string> *node3 = new Node<std::string>(3, "Data3");

        list.AppendNode(node1);
        list.AppendNode(node2);

        list.PrependNode(node3);

        std::cout << "Linked List after appending and prepending nodes:" << std::endl;
        list.Display();

        list.UpdateNodeByKey(2, "UpdatedData2");

        std::cout << "\nLinked List after updating node with key 2:" << std::endl;
        list.Display();

        // Unsafe may free memory and cause double free error
        list.DeleteNodeByKey(1);

        std::cout << "\nLinked List after deleting node with key 1:" << std::endl;
        list.Display();

        // Unsafe: Clean up dynamically allocated memory (Dangerous can cause malloc_error_break for double free)
        // delete node1;
        delete node2;
        delete node3;
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