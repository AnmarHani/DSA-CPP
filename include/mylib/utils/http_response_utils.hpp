#pragma once
#include <crow.h>
#include <string>


namespace HTTPResponse {
    crow::response badRequest(const std::string &message);

};