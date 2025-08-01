#include <crow.h>
#include <string>

#include <mylib/utils/http_response_utils.hpp>

crow::response HTTPResponse::badRequest(const std::string &message)
{
    return crow::response(
        crow::BAD_REQUEST,
        crow::json::wvalue{{"status", "ERROR"}, {"message", message}});
}
crow::response HTTPResponse::internalServerError(const std::string &message)
{
    return crow::response(
        crow::INTERNAL_SERVER_ERROR,
        crow::json::wvalue{{"status", "ERROR"}, {"message", message}});
}
crow::response HTTPResponse::notFound(const std::string &message)
{
    return crow::response(
        crow::NOT_FOUND,
        crow::json::wvalue{{"status", "ERROR"}, {"message", message}});
}