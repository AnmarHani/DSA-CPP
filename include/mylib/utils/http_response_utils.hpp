#pragma once
#include <crow.h>
#include <string>


namespace HTTPResponse {
    crow::response badRequest(const std::string &message);
    crow::response internalServerError(const std::string &message);
    crow::response notFound(const std::string &message);
    crow::response success(const std::string &message);

};