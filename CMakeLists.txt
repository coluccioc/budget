# cmake_minimum_required(VERSION 3.16)
# project(BudgetApp)

# set(CMAKE_CXX_STANDARD 17)

# # Find Qt
# find_package(Qt5 COMPONENTS Widgets REQUIRED)

# add_executable(BudgetApp src/main.cpp src/UI.cpp src/BudgetManager.cpp)
# target_include_directories(BudgetApp PRIVATE include)
# target_link_libraries(BudgetApp Qt5::Widgets)

# # Add SQLite
# add_library(sqlite3 STATIC SQLite/sqlite3.c)
# include_directories(SQLite/)
# target_link_libraries(BudgetApp sqlite3)

# #Find date
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# find_package(date CONFIG REQUIRED)

# target_link_libraries(BudgetApp PRIVATE date::date)

# cmake_minimum_required(VERSION 3.16)

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
)

# Include headers
target_include_directories(BudgetApp PRIVATE include SQLite/)

# Link libraries
target_link_libraries(BudgetApp
    Qt5::Widgets
    sqlite3
    date::date
)