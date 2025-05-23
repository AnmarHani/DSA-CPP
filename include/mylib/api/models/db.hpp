#pragma once

#include <mylib/api/models/linked_list_model.hpp>
#include <sqlite_orm/sqlite_orm.h>
#include <string>

namespace Database {
    using Storage = decltype(sqlite_orm::make_storage("",
                                                      makeLinkedListTable(),
                                                      makeLinkedListNodeTable()));

    Storage &GetStorage();
}
