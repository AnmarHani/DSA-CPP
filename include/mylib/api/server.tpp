#pragma once
#include <vector>
#include <mylib/config/settings.hpp>
#include <type_traits>

template <typename... SetupRouteMethods>
void Server::Start(const bool isAutoSetup, SetupRouteMethods &&...setupRouteMethods)
{

    if (isAutoSetup)
        Setup();

    // Call all Setup Route Methods
    if constexpr (sizeof...(setupRouteMethods) > 0)
    { // constexpr to Evaluate at compile-time
        static_assert(std::is_invocable_v<SetupRouteMethods...>, "SetupRouteMethod must be callable");
        (std::invoke(std::forward<SetupRouteMethods>(setupRouteMethods)), ...);
    }

    m_app.run_async();
}

template <typename HandlerType, typename... Methods>
void Server::AddRoute(const std::string &routePath, HandlerType &&handler, Methods... httpMethods)
{
    static_assert(sizeof...(httpMethods) > 0, "You need atleast one HTTP Method");
    static_assert((std::is_same_v<Methods, crow::HTTPMethod> && ...), "Any HTTP Method must be type of crow::HTTPMethod"); // && ... means that it makes a connjuction, all must be true, if one is false, then all are false.
    
    std::cout << "Registering route: " << routePath << std::endl;
    m_registeredRoutes.push_back(routePath);
    
    m_app.route_dynamic(routePath).methods(httpMethods...)(std::forward<HandlerType>(handler));
}