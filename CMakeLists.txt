cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "C:/VCPkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(BudgetApp)

set(CMAKE_CXX_STANDARD 17)

# Windows API version
add_definitions(-D_WIN32_WINNT=0x0601)

# Find Qt and date
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(date CONFIG REQUIRED)
find_package(Threads REQUIRED)

# SQLite library
add_library(sqlite3 STATIC SQLite/sqlite3.c)
target_include_directories(sqlite3 PRIVATE SQLite/)

# Main executable
add_executable(BudgetApp
    src/main.cpp
    src/BudgetManager.cpp
    src/DatabaseManager.cpp
    src/WebServer.cpp
    src/Util.cpp
    src/Validation.cpp
)

# Test executable

# add_executable(BudgetAppTests
#     tests/test.cpp
#     src/BudgetManager.cpp
#     src/DatabaseManager.cpp
#     src/WebServer.cpp
#     src/Util.cpp
#     src/Validation.cpp
# )

# Include paths
target_include_directories(BudgetApp PRIVATE
    include
    SQLite/
    C:/Boost/boost_1_89_0
    libs/Crow/include
    libs/json/include
)

target_include_directories(BudgetAppTests PRIVATE
    include
    SQLite/
    libs/Crow/include
    libs/json/include
    C:/Boost/boost_1_89_0
)

# Link libraries
target_link_libraries(BudgetApp PRIVATE
    Qt5::Widgets
    sqlite3
    date::date
    Threads::Threads
)

target_link_libraries(BudgetAppTests PRIVATE
    Qt5::Widgets
    sqlite3
    date::date
    Threads::Threads
)