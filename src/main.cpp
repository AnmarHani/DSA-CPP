#include <mylib/api/server.hpp>
#include <iostream>

int main()
{
    try
    {
        Server server = Server();
        server.Start();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}