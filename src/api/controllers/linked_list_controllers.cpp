#include <crow.h>

crow::response GetLinkedListByQueryParam(const crow::request &request) {
    // lli = LinkedList ID
    auto queryParameter = request.url_params.get("lli") == nullptr ? "" : request.url_params.get("lli");

    
};