#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <mylib/data_structures/linked_list.hpp>
#include <mylib/data_structures/linked_list_node.hpp>
#include <string>

TEST_CASE("LinkedList basic operations", "[LinkedList]")
{
    LinkedList<std::string, 10> list;

    SECTION("List is empty on creation")
    {
        REQUIRE(list.IsEmpty());
        REQUIRE(list.Count() == 0);
    }

    SECTION("Append and search node")
    {
        Node<std::string> *nodeToAppend = new Node<std::string>(1, "Data1");
        list.AppendNode(nodeToAppend);

        REQUIRE_FALSE(list.IsEmpty());

        REQUIRE(list.Count() == 1);

        Node<std::string> *node = list.SearchNode(1);

        REQUIRE(node != nullptr);
        REQUIRE(node->data == "Data1");

        // delete nodeToAppend;
    }

    SECTION("Delete node by key")
    {
        Node<std::string> *nodeToAppend = new Node<std::string>(1, "Data1");
        list.AppendNode(nodeToAppend);

        REQUIRE(list.DeleteNodeByKey(1));
        REQUIRE(list.IsEmpty());

        // delete nodeToAppend;
    }

    SECTION("Delete non-existent node returns false")
    {
        REQUIRE_THROWS(list.DeleteNodeByKey(999));
    }
}