#include <crow.h>
#include <string>

#include "mylib/api/server.hpp"
#include "mylib/api/controllers/linked_list_controllers.hpp"
#include "mylib/config/settings.hpp"

static const std::string PREFIX = Settings::Server::API_PREFIX + "/linked-lists";

void createAllLinkedListRoutes()
{
    Server::GetInstance().AddRoute(PREFIX, [](const crow::request &req)
                                   { return getAll(req); }, crow::HTTPMethod::GET);
    Server::GetInstance().AddRoute(PREFIX + "/<int>", [](const crow::request &req, int id)
                                   { return getById(req, id); }, crow::HTTPMethod::GET);

    Server::GetInstance().AddRoute(PREFIX + "/create", [](const crow::request &req)
                                   { return create(req); }, crow::HTTPMethod::POST);

    Server::GetInstance().AddRoute(PREFIX + "/<int>", [](const crow::request &req, int id)
                                   { return updateById(req, id); }, crow::HTTPMethod::PUT);

    Server::GetInstance().AddRoute(PREFIX + "/<int>", [](const crow::request &req, int id)
                                   { return deleteById(req, id); }, crow::HTTPMethod::DELETE);
}