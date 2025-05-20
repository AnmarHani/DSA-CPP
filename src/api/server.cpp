#include <mylib/api/server.hpp>
#include <mylib/config/settings.hpp>

Server::Server(const Settings::Server &serverConfig)
{
    m_app.port(serverConfig.PORT);
    m_app.bindaddr(serverConfig.HOST);
    m_app.concurrency(serverConfig.THREADS_NUM);
    crow::logger::setLogLevel(static_cast<crow::LogLevel>(serverConfig.LOG_LEVEL));
}

void Server::Start()
{
    m_app.multithreaded().run();
}