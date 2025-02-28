cmake_minimum_required(VERSION 3.16)
project(BudgetApp)

set(CMAKE_CXX_STANDARD 17)

# Find Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BudgetApp src/main.cpp src/UI.cpp)
target_include_directories(BudgetApp PRIVATE include)
target_link_libraries(BudgetApp Qt5::Widgets)