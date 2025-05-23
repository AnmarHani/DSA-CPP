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
        static inline const std::string HOST = "127.0.0.1";
        static inline const int PORT = 8080;
        static inline const int THREADS_NUM = 2;

        static inline const LOG_LEVELS LOG_LEVEL = LOG_LEVELS::DEBUG;

        static inline const bool IS_CORS_ENABLED = true;
        static inline const std::string ALLOWED_CORS_ORIGINS = "*";

        static inline const std::string API_VERSION = "v1";
        static inline const std::string API_PREFIX = "/" + API_VERSION + "/api";

        static inline const std::string STATIC_FILES_PATH = "static";
        static inline const std::string DYNAMIC_FILES_PATH = "media";
    };

    struct Database
    {
        static inline const std::string DB_ENGINE = "sqlite";
        static inline const std::string HOST = "db.sqlite";
    };
}
