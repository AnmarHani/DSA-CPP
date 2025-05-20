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

# Builds the code (except main.cpp and validation_only files) into a static library called mylib.
add_library(mylib STATIC ${LIB_SOURCES})
target_include_directories(mylib PUBLIC include)

# ------------------------------
# Main Application
# ------------------------------
add_executable(DSACPP src/main.cpp)

target_include_directories(DSACPP PRIVATE include)

target_compile_definitions(DSACPP PRIVATE ASIO_STANDALONE)  # Required for Crow+ASIO
target_include_directories(mylib PUBLIC ${asio_SOURCE_DIR}/asio/include)
target_include_directories(DSACPP PRIVATE ${asio_SOURCE_DIR}/asio/include)

target_include_directories(mylib PUBLIC ${crow_SOURCE_DIR}/include)
target_include_directories(DSACPP PRIVATE ${crow_SOURCE_DIR}/include)

target_include_directories(mylib PUBLIC ${sqlite_orm_SOURCE_DIR}/include)
target_include_directories(DSACPP PRIVATE ${sqlite_orm_SOURCE_DIR}/include)

target_link_libraries(DSACPP PRIVATE mylib)

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



# ------------------------------
# CMake Crash Course For Reference, because its confusing :)
# ------------------------------
## project-root/
## ├── CMakeLists.txt
## ├── src/
## │   └── main.cpp
## ├── FirstInclude/
## │   ├── mylib1.hpp
## │   └── mylib1.cpp
## ├── SecondInclude/
## │   ├── mylib2.hpp
## │   └── mylib2.cpp
## ├── external/
## │   └── myheaderonly.hpp
## ├── thirdparty/
## │   └── mysourceonly/
## │       ├── mysourceonly.hpp
## │       ├── mysourceonly.cpp
## │       └── CMakeLists.txt

# cmake_minimum_required(VERSION 3.15)
# project(HelloWorldExample LANGUAGES CXX)

# # Static library from FirstInclude
# add_library(mylib1 STATIC FirstInclude/mylib1.cpp)
# target_include_directories(mylib1 PUBLIC FirstInclude)

# # Dynamic library from SecondInclude
# add_library(mylib2 SHARED SecondInclude/mylib2.cpp)
# target_include_directories(mylib2 PUBLIC SecondInclude)

# # Header-only library
# add_library(myheaderonly INTERFACE)
# target_include_directories(myheaderonly INTERFACE external)

# # Source-only library (with its own CMakeLists.txt)
# add_subdirectory(thirdparty/mysourceonly)

# # External library from GitHub (CPM)
# include(cmake/CPM.cmake)
# CPMAddPackage(
#   NAME fmt
#   GITHUB_REPOSITORY fmtlib/fmt
#   VERSION 10.2.1
# )

# # External prebuilt library
# find_library(MYEXTLIB myextlib PATHS /usr/local/lib)

## PUBLIC
## Use when headers are needed by both the library and anything that links to it.
## Example: target_include_directories(mylib1 PUBLIC FirstInclude)
## FirstInclude/mylib1.hpp is needed by both mylib1.cpp and any code using mylib1.

## PRIVATE
## Use when headers are only needed to build the library itself.
## Example: If mylib1.cpp uses a helper header not needed by users:

## INTERFACE
## Use for header-only libraries.
## Example: target_include_directories(myheaderonly INTERFACE external)
## Only users of myheaderonly need the headers; there is no compiled code.

## PRIVATE here means only the target (hello) needs to link these libraries.
## If you want to propagate the link to targets that depend on hello, use PUBLIC.
## For executables, PRIVATE is almost always correct.

# add_executable(hello src/main.cpp)
# target_link_libraries(hello
#     PRIVATE
#         mylib1        # Our static lib
#         mylib2        # Our dynamic lib
#         myheaderonly  # Header-only lib
#         mysourceonly  # Source-only lib
#         fmt::fmt      # External (CPM/fmt)
#         ${MYEXTLIB}   # Prebuilt
# )

# target_include_directories(hello
#     PRIVATE
#         FirstInclude
#         SecondInclude
#         external
#         /usr/local/include/myextlib
# )

## main.cpp
# #include <mylib1.hpp>           // From FirstInclude (static lib)
# #include <mylib2.hpp>           // From SecondInclude (dynamic lib)
# #include <myheaderonly.hpp>     // From external (header-only)
# #include <mysourceonly.hpp>     // From thirdparty/mysourceonly (source-only)
# #include <fmt/core.h>           // From CPM/fmt

# int main() {
#   mylib1_func();              // Provided by mylib1
#   mylib2_func();              // Provided by mylib2
#   myheaderonly_func();        // Provided by myheaderonly
#   mysourceonly_func();        // Provided by mysourceonly
#   fmt::print("Hello, world!\n"); // Provided by fmtlib
#   // If MYEXTLIB provides a function:
#   // myextlib_func();
#   return 0;
# }

## Static Library (.a or .lib):
## Description: Code is copied into your executable at build time.
## Pros: No external dependencies at runtime, easier deployment.
## Cons: Larger executables, updating library requires rebuilding your app.

## Dynamic Library (.so on Linux, .dylib on Mac, .dll on Windows):
## Description: Code is loaded at runtime.
## Pros: Smaller executables, can update library without rebuilding app.
## Cons: Need to ship the .so/.dylib/.dll with your app, can have versioning issues.

# Including: Tells the compiler where to find header files (for declarations).
# Linking: Tells the linker where to find compiled code (for definitions).

## - Add as many target_include_directories as needed for all your include paths.
## - Use add_library(... STATIC ...) or add_library(... SHARED ...) as needed.
## - Use add_subdirectory for subprojects.
## - Use CPMAddPackage or FetchContent for GitHub/external CMake libraries.
## - Use find_library and target_link_libraries for prebuilt binaries.

## Why sometimes don't link external libraries?
## - Header-only libraries (like myheaderonly) don't need linking, just includes.
## - Some libraries (like fmt) provide CMake targets (e.g., fmt::fmt), so you link them by name.
## - Prebuilt libraries (like ${MYEXTLIB}) need both include and link steps.

## Use add_subdirectory when you have a subproject with its own CMakeLists.txt 

