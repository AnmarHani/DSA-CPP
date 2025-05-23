#pragma once

#include <crow.h>

// READ Operations
crow::response getAll(const crow::request &request);
crow::response getById(const crow::request &request, int linkedListId);

// CREATE Operations
crow::response create(const crow::request &request);

// UPDATE Operations
crow::response updateById(const crow::request &request, int linkedListId);

// DELETE Operations
crow::response deleteById(const crow::request &request, int linkedListId);
