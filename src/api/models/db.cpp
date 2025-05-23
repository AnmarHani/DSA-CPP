#include <sqlite_orm/sqlite_orm.h>

#include <mylib/api/models/db.hpp>
#include <mylib/api/models/linked_list_model.hpp>

#include <mylib/config/settings.hpp>


namespace Database {
    Storage &GetStorage() {
        static Storage storage = sqlite_orm::make_storage(Settings::Database::HOST,
                                                       makeLinkedListTable(),
                                                       makeLinkedListNodeTable());
        return storage;
    }
}
