#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <cpr/cpr.h>
#include <iostream>

TEST_CASE("LinkedList API integration", "[LinkedList_API]")
{
    const std::string BASE_URL = "http://localhost:8080/v1/api/linked-lists";

    SECTION("GET all linked lists")
    {
        auto r = cpr::Get(cpr::Url{BASE_URL});
        REQUIRE(r.status_code == 200);
        // Optionally, check JSON structure
    }

    SECTION("POST create linked list")
    {
        const std::string CREATE_BODY_JSON = R"({
                "linked_list_nodes": [
                    {"key": 1, "data": "Data1", "next_node_key": 2, "prev_node_key": 3},
                    {"key": 2, "data": "Data2", "next_node_key": 3, "prev_node_key": 1},
                    {"key": 3, "data": "Data3", "next_node_key": 1, "prev_node_key": 2}
                ]
            })";

        std::cout << "Sending JSON:\n"
                  << CREATE_BODY_JSON << std::endl;

        auto r = cpr::Post(cpr::Url{BASE_URL + "/create"},
                           cpr::Body{CREATE_BODY_JSON},
                           cpr::Header{{"Content-Type", "application/json"}});

        std::cout << "Status: " << r.status_code << "\nBody: " << r.text << std::endl;

        REQUIRE((r.status_code == 201));
    }

    SECTION("GET by id returns 404 for missing")
    {
        auto r = cpr::Get(cpr::Url{BASE_URL + "/99999"});
        REQUIRE(r.status_code == 404);
    }
}