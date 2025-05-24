#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include <vector>

#include "mylib/utils/http_response_utils.hpp"

#include "mylib/api/models/db.hpp"
#include "mylib/api/models/linked_list_model.hpp"
// #include <system_error>
#include <stdexcept>

crow::response getAll(const crow::request &request)
{
    try
    {
        auto linkedLists = Database::GetStorage().get_all<LinkedListModel>(
            sqlite_orm::order_by(&LinkedListModel::id));

        crow::json::wvalue::list linkedListsJSON;
        for (const auto &linkedList : linkedLists)
        {
            linkedListsJSON.emplace_back(
                crow::json::wvalue{
                    {"id", linkedList.id}});
        }

        crow::json::wvalue JSONResponse;
        JSONResponse["status"] = "SUCCESS";
        JSONResponse["data"]["linked_lists"] = std::move(linkedListsJSON);

        return crow::response{crow::OK, JSONResponse};
    }
    catch (const std::runtime_error &e)
    { // record isn't found etc.

        return HTTPResponse::notFound(e.what());
    }
    catch (const std::exception &e)
    {
        return HTTPResponse::internalServerError(e.what());
        ;
    }
}

crow::response getById(const crow::request &request, int linkedListId)
{
    // // lli = LinkedList ID
    // auto queryParameter = request.url_params.get("lli") == nullptr ? "" : request.url_params.get("lli");

    try
    {
        std::optional<LinkedListModel> optionalLinkedList = Database::GetStorage().get_optional<LinkedListModel>(linkedListId);
        if (!optionalLinkedList)
            throw std::runtime_error("linked list not found");

        // sqlite_orm::c is a column wrapper
        auto linkedListNodes =
            Database::GetStorage().get_all<LinkedListNodeModel>(
                sqlite_orm::where(sqlite_orm::c(&LinkedListNodeModel::associatedLinkedListId) == linkedListId),
                sqlite_orm::order_by(&LinkedListNodeModel::key));

        crow::json::wvalue::list linkedListNodesListJSON;
        for (const auto &linkedListNode : linkedListNodes)
        {
            crow::json::wvalue nextNodeKey = linkedListNode.nextNodeKey ? crow::json::wvalue{linkedListNode.nextNodeKey.value()} : crow::json::wvalue();
            crow::json::wvalue prevNodeKey = linkedListNode.prevNodeKey ? crow::json::wvalue{linkedListNode.prevNodeKey.value()} : crow::json::wvalue();

            linkedListNodesListJSON.emplace_back(
                crow::json::wvalue{
                    {"key", linkedListNode.key},
                    {"data", linkedListNode.data},
                    {"next_node_key", nextNodeKey},
                    {"previous_node_key", prevNodeKey}});
        }

        crow::json::wvalue JSONResponse;
        JSONResponse["status"] = "SUCCESS";
        JSONResponse["data"]["linked_list_id"] = linkedListId;
        JSONResponse["data"]["linked_list_nodes"] = std::move(linkedListNodesListJSON);

        return crow::response{crow::OK, JSONResponse};
    }
    catch (const std::runtime_error &e)
    { // record isn't found etc.

        return HTTPResponse::notFound(e.what());
    }
    catch (const std::exception &e)
    {
        return HTTPResponse::internalServerError(e.what());
        ;
    }
}

crow::response create(const crow::request &request)
{
    try
    {
        crow::json::rvalue body = crow::json::load(request.body);
        std::cout << "Request body: " << request.body << std::endl;

        if (!body || !body.has("linked_list_nodes"))
            throw std::runtime_error("missing `linked_list_nodes`");

        LinkedListModel list; // Empty Linkedlist, no fields other than ID
        int linkedListId = Database::GetStorage().insert(list);

        std::vector<LinkedListNodeModel> linkedListNodes;

        for (const crow::json::rvalue &linkedListNodeJSON : body["linked_list_nodes"])
        {
            if (linkedListNodeJSON.t() != crow::json::type::Object)
                throw std::runtime_error("Each linked_list_node must be an object");

            if (!linkedListNodeJSON.has("key") || !linkedListNodeJSON.has("data"))
                throw std::runtime_error("missing `key` or `data` in LinkedList Node");

            LinkedListNodeModel linkedListNodeToSave;

            linkedListNodeToSave.key = linkedListNodeJSON["key"].i();   // Convert to Int
            linkedListNodeToSave.data = linkedListNodeJSON["data"].s(); // Convert to String

            crow::json::rvalue nextNodeKey = linkedListNodeJSON["next_node_key"];
            linkedListNodeToSave.nextNodeKey = nextNodeKey ? std::optional<int>{nextNodeKey.i()} : std::nullopt;

            crow::json::rvalue prevNodeKey = linkedListNodeJSON["prev_node_key"];
            linkedListNodeToSave.prevNodeKey = prevNodeKey ? std::optional<int>{prevNodeKey.i()} : std::nullopt;

            linkedListNodeToSave.associatedLinkedListId = linkedListId;

            linkedListNodes.push_back(std::move(linkedListNodeToSave));
        }

        Database::GetStorage().transaction([&]
                                           {
            Database::GetStorage().insert_range(linkedListNodes.begin(), linkedListNodes.end());

            return true; });

        crow::json::wvalue JSONResponse;
        JSONResponse["id"] = linkedListId;
        JSONResponse["status"] = "SUCCESS";

        return crow::response{crow::CREATED, JSONResponse};
    }
    catch (const std::exception &e)
    {
        return HTTPResponse::internalServerError(e.what());
        ;
    }
}

crow::response updateById(const crow::request &request, int linkedListId)
{
    // Use instead of Always Writing Database::GetStorage()
    // decltype(Database::GetStorage())& storage = Database::GetStorage();
    // auto &storage = Database::GetStorage();

    try
    {
        std::optional<LinkedListModel> optionalLinkedList = Database::GetStorage().get_optional<LinkedListModel>(linkedListId);
        if (!optionalLinkedList)
            throw std::runtime_error("linked list not found");

        // const LinkedListModel& linkedList = *optionalLinkedList;  // safe to use

        crow::json::rvalue body = crow::json::load(request.body);

        if (!body || !body.has("linked_list_nodes"))
            throw std::runtime_error("missing `linked_list_nodes`");

        std::vector<LinkedListNodeModel> linkedListNodes;

        for (crow::json::rvalue &linkedListNodeJSON : body["linked_list_nodes"])
        {
            if (linkedListNodeJSON.t() != crow::json::type::Object)
                throw std::runtime_error("Each linked_list_node must be an object");

            if (!linkedListNodeJSON.has("key") || !linkedListNodeJSON.has("data"))
                throw std::runtime_error("missing `key` or `data` in LinkedList Node");

            LinkedListNodeModel linkedListNodeToSave;

            linkedListNodeToSave.key = linkedListNodeJSON["key"].i();   // Convert to Int
            linkedListNodeToSave.data = linkedListNodeJSON["data"].s(); // Convert to String

            crow::json::rvalue nextNodeKey = linkedListNodeJSON["next_node_key"];
            linkedListNodeToSave.nextNodeKey = nextNodeKey ? std::optional<int>{nextNodeKey.i()} : std::nullopt;

            crow::json::rvalue prevNodeKey = linkedListNodeJSON["prev_node_key"];
            linkedListNodeToSave.prevNodeKey = prevNodeKey ? std::optional<int>{prevNodeKey.i()} : std::nullopt;

            linkedListNodeToSave.associatedLinkedListId = linkedListId;

            linkedListNodes.push_back(std::move(linkedListNodeToSave));
        }

        Database::GetStorage().transaction([&]
                                           {
            Database::GetStorage().remove_all<LinkedListNodeModel>(
                sqlite_orm::where(
                    sqlite_orm::c(&LinkedListNodeModel::associatedLinkedListId) == linkedListId
                ));

            Database::GetStorage().insert_range(linkedListNodes.begin(), linkedListNodes.end());

            return true; });

        crow::json::wvalue JSONResponse;
        JSONResponse["id"] = linkedListId;
        JSONResponse["status"] = "SUCCESS";

        return crow::response{crow::CREATED, JSONResponse};
    }
    catch (const std::runtime_error &e)
    { // record isn't found etc.
        return HTTPResponse::notFound(e.what());
    }
    catch (const std::exception &e)
    {
        return HTTPResponse::internalServerError(e.what());
        ;
    }
}

crow::response deleteById(const crow::request &request, int linkedListId)
{
    try
    {
        std::optional<LinkedListModel> optionalLinkedList = Database::GetStorage().get_optional<LinkedListModel>(linkedListId);
        if (!optionalLinkedList)
            throw std::runtime_error("linked list not found");

        // const LinkedListModel& linkedList = *optionalLinkedList;  // safe to use

        Database::GetStorage().transaction([&]
                                           {
            Database::GetStorage().remove_all<LinkedListNodeModel>(
                sqlite_orm::where(
                    sqlite_orm::c(&LinkedListNodeModel::associatedLinkedListId) == linkedListId
                ));

            Database::GetStorage().remove<LinkedListModel>(linkedListId);
            return true; });

        crow::json::wvalue JSONResponse;
        JSONResponse["id"] = linkedListId;
        JSONResponse["status"] = "SUCCESS";

        return crow::response{crow::OK, JSONResponse};
    }
    catch (const std::runtime_error &e)
    { // record isn't found etc.
        return HTTPResponse::notFound(e.what());
    }
    catch (const std::exception &e)
    {
        return HTTPResponse::internalServerError(e.what());
        ;
    }
}
