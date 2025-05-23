#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <string>


class Server
{
private:
    crow::App<crow::CORSHandler> m_app;
    std::vector<std::string> m_registeredRoutes;
    
    Server();

public:
    static Server& GetInstance();
    void Setup();

    template <typename... SetupRouteMethods>
    void Start(bool isAutoSetup = true, SetupRouteMethods&&... setupRouteMethods);

    template <typename HandlerType, typename... Methods>
    void AddRoute(const std::string &routePath, HandlerType &&handler, Methods... httpMethods);
};

#include <mylib/api/server.tpp>