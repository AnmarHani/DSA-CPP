cmake_minimum_required(VERSION 3.15)

project(DSACPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
add_definitions(-DASIO_HAS_IO_CONTEXT=1)

# Output binaries to /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ------------------------------
# Dependency Management (CPM)
# ------------------------------
# include(FetchContent)
# FetchContent_Declare(
#   CPM
#   GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
#   GIT_TAG v0.42.0
# )
# FetchContent_MakeAvailable(CPM)

# # Catch2 for testing
# CPMAddPackage(
#   NAME Catch2
#   GITHUB_REPOSITORY catchorg/Catch2
#   VERSION 3.4.0
# )

# # Crow for HTTP server
# CPMAddPackage(
#   NAME crow
#   GITHUB_REPOSITORY CrowCpp/crow
#   VERSION 1.0+4
# )

# Bootstrap CPM.cmake (CPM recommends this minimal "bootstrap" pattern)
set(CPM_DOWNLOAD_VERSION 0.42.0)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  file(DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION}
    EXPECTED_HASH SHA256=2020b4fc42dba44817983e06342e682ecfc3d2f484a581f11cc5731fbe4dce8a
  )
endif()
include(${CPM_DOWNLOAD_LOCATION})

# Add ASIO for Crow
CPMAddPackage(
  NAME asio
  GITHUB_REPOSITORY chriskohlhoff/asio
  GIT_TAG asio-1-24-0
  OPTIONS
    "ASIO_BUILD_EXAMPLES OFF"
    "ASIO_BUILD_TESTS OFF"
    "ASIO_BUILD_DOCS OFF"
)

# Catch2 for testing
CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 3.8.1
)

# Crow for HTTP server
CPMAddPackage(
  NAME crow
  GITHUB_REPOSITORY CrowCpp/crow
  VERSION 1.2.1
)

# SQLite ORM for Database Operations
CPMAddPackage(
  NAME sqlite_orm
  GITHUB_REPOSITORY fnc12/sqlite_orm
  VERSION 1.9.1
)

# ------------------------------
# Build Library from src/*
# ------------------------------
# Collect all .cpp files except src/main.cpp
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp") 

# Remove all files in src/validation_only from LIB_SOURCES (it is just indiviually run, just for validating the code, not in production)
file(GLOB_RECURSE VALIDATION_SOURCES CONFIGURE_DEPENDS src/validation_only/*.cpp)
list(REMOVE_ITEM LIB_SOURCES ${VALIDATION_SOURCES})

add_library(mylib STATIC ${LIB_SOURCES})
target_include_directories(mylib PUBLIC include)
target_compile_options(mylib PRIVATE -Wall -Wextra -Wpedantic)

# ------------------------------
# Main Application
# ------------------------------
add_executable(DSACPP src/main.cpp)

target_compile_definitions(DSACPP PRIVATE ASIO_STANDALONE)  # Required for Crow+ASIO
target_include_directories(mylib PUBLIC ${asio_SOURCE_DIR}/asio/include)

target_include_directories(DSACPP PRIVATE ${asio_SOURCE_DIR}/asio/include)
target_include_directories(DSACPP PRIVATE ${crow_SOURCE_DIR}/include)

target_include_directories(mylib PUBLIC ${sqlite_orm_SOURCE_DIR}/include)
target_include_directories(DSACPP PRIVATE ${sqlite_orm_SOURCE_DIR}/include)

target_compile_options(DSACPP PRIVATE -Wall -Wextra -Wpedantic)
set_target_properties(DSACPP PROPERTIES OUTPUT_NAME "DSA-CPP")

# ------------------------------
# Unit Tests
# ------------------------------
enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE mylib Catch2::Catch2WithMain)
target_include_directories(unit_tests PRIVATE include)

# Add Catch2's extras directory to CMake module path
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

# Include Catch2's CMake module for test discovery
include(Catch)
catch_discover_tests(unit_tests)

# ------------------------------
# IDE Organization
# ------------------------------
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${LIB_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/tests PREFIX "Tests" FILES ${TEST_SOURCES})
