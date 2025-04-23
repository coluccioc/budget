# Created by Chris on 2025-03-01
# VCPKG must be set before the project() command
cmake_minimum_required(VERSION 3.16)

# Must be BEFORE project()
set(CMAKE_TOOLCHAIN_FILE "C:/VCPkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(BudgetApp)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(date CONFIG REQUIRED)

# Add SQLite static library first so we can link to it later
add_library(sqlite3 STATIC SQLite/sqlite3.c)
target_include_directories(sqlite3 PRIVATE SQLite/)

# Add the main executable
add_executable(BudgetApp
    src/main.cpp
    src/UI.cpp
    src/BudgetManager.cpp
    src/DatabaseManager.cpp
)

# Add the test executable
add_executable(BudgetAppTests
    tests/test.cpp
    src/BudgetManager.cpp
    src/DatabaseManager.cpp
)

# Include headers
target_include_directories(BudgetApp PRIVATE include SQLite/)
# Include headers for tests
target_include_directories(BudgetAppTests PRIVATE include SQLite/)

# Link libraries
target_link_libraries(BudgetApp
    Qt5::Widgets
    sqlite3
    date::date
)
# Link libraries for tests
target_link_libraries(BudgetAppTests
    Qt5::Widgets
    sqlite3
    date::date
)