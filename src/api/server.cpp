#include <crow/middlewares/cors.h>

#include <mylib/api/server.hpp>
#include <mylib/config/settings.hpp>

const Server &Server::GetInstance()
{
    static const Server instance;
    return instance;
}

void Server::Setup()
{
    m_app.server_name("DSA-CPP API");
    if (Settings::Server::IS_CORS_ENABLED)
    {
        auto &cors = m_app.get_middleware<crow::CORSHandler>();
        cors
            .global()
            .methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST, crow::HTTPMethod::PUT, crow::HTTPMethod::DELETE)
            .headers("Content-Type", "Authorization")
            .origin(Settings::Server::ALLOWED_CORS_ORIGINS)
            .prefix("/api")
            .max_age(3600);
    }
    m_app.port(Settings::Server::PORT);
    m_app.bindaddr(Settings::Server::HOST);
    m_app.multithreaded().concurrency(Settings::Server::THREADS_NUM);
    crow::logger::setLogLevel(static_cast<crow::LogLevel>(Settings::Server::LOG_LEVEL));
}

void Server::Start(bool isAutoSetup)
{
    if (isAutoSetup)
        Setup();

    m_app.run_async();
}