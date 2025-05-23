#pragma once

#include <string>
#include <sqlite_orm/sqlite_orm.h>

struct LinkedListNodeModel
{
    int key;
    std::string data;
    std::optional<int> nextNodeKey;
    std::optional<int> prevNodeKey;

    int associatedLinkedListId;
};

struct LinkedListModel
{
    int id;
};

inline auto makeLinkedListTable()
{
    return sqlite_orm::make_table("linked_lists",
                                  sqlite_orm::make_column("id", &LinkedListModel::id, sqlite_orm::primary_key().autoincrement()));
}

inline auto makeLinkedListNodeTable()
{
    return sqlite_orm::make_table("linked_list_nodes",
                      sqlite_orm::make_column("key", &LinkedListNodeModel::key, sqlite_orm::primary_key().autoincrement()),
                      sqlite_orm::make_column("data", &LinkedListNodeModel::data, sqlite_orm::default_value("0")),
                      sqlite_orm::make_column("next_node_key", &LinkedListNodeModel::nextNodeKey),
                      sqlite_orm::make_column("prev_node_key", &LinkedListNodeModel::prevNodeKey),
                      sqlite_orm::make_column("associated_linked_list_id", &LinkedListNodeModel::associatedLinkedListId),
                      sqlite_orm::foreign_key(&LinkedListNodeModel::associatedLinkedListId).references(&LinkedListModel::id));
}