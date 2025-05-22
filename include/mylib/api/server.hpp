#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <mylib/config/settings.hpp>
#include <string>


namespace HTTPResponse {
    
}

class Server
{
private:
    crow::App<crow::CORSHandler> m_app;
    Server();

public:
    const static Server& GetInstance();
    void Setup();
    void Start(bool isAutoSetup = true);
    void AddRoute(const std::string &routePath, const crow::HTTPMethod &httpMethod, const std::string &handler);
};