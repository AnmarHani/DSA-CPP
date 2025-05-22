#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <mylib/api/models/linked_list_model.hpp>

using namespace sqlite_orm;
auto storage = make_storage("db.sqlite",
                            makeLinkedListTable(),
                            makeLinkedListNodeTable());