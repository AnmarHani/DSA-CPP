// SQLITE Boilerplate

#include <sqlite_orm/sqlite_orm.h>
#include <string>

// Define the User class
struct User
{
    int id;
    std::string firstName;
    std::string lastName;
    std::string birthDate;
    std::string imageUrl;
    int typeId;
};

// Define the UserType class
struct UserType
{
    int id;
    std::string name;
};

using namespace sqlite_orm;
auto storage = make_storage("db.sqlite",
                            make_table("users",
                                       make_column("id", &User::id, primary_key().autoincrement()),
                                       make_column("first_name", &User::firstName),
                                       make_column("last_name", &User::lastName),
                                       make_column("birth_date", &User::birthDate),
                                       make_column("image_url", &User::imageUrl),
                                       make_column("type_id", &User::typeId)),
                            make_table("user_types",
                                       make_column("id", &UserType::id, primary_key().autoincrement()),
                                       make_column("name", &UserType::name, default_value("name_placeholder"))));