#pragma once
#include <crow.h>
#include <mylib/config/settings.hpp>

class Server
{
private:
    crow::SimpleApp m_app;

public:
    explicit Server(const Settings::Server &serverConfig = Settings::Server());
    void Start();
};