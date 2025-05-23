#include <mylib/api/server.hpp>
#include <iostream>

#include "mylib/api/models/db.hpp"
#include "mylib/api/routes/linked_list_routes.hpp"

int main()
{
    try
    {
        Database::GetStorage().sync_schema();
        Server &server = Server::GetInstance();
        server.Start(true, createAllLinkedListRoutes);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
