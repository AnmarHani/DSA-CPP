#pragma once
#include <string>

namespace Settings
{
    enum LOG_LEVELS
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    struct Server
    {
        std::string HOST = "127.0.0.1";
        int PORT = 8080;
        int THREADS_NUM = 2;

        LOG_LEVELS LOG_LEVEL = LOG_LEVELS::DEBUG;

        bool IS_CORS_ENABLED = true;
        std::string ALLOWED_CORS_ORIGINS = "*";
    };

    struct Database
    {
        std::string DB_ENGINE = "sqlite";
        std::string HOST = "db.sqlite";
    };
}
