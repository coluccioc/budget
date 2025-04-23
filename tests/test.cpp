#pragma once
#include <cassert>
#include <iostream>
#include "../include/DatabaseManager.hpp"
#include "../include/BudgetManager.hpp"

void expect(bool condition, const std::string& testName)
{
    if(condition)
    {
        std::cout <<"[PASS]" << testName << "\n";
    }
    else
    {
        std::cout << "[FAIL]" << testName << "\n";
    }
}

void testDBCreate()
{
    DatabaseManager db("test.db");
    expect(db.isOpen(), "Database Creation Test");
}

int main() 
{
    std::cout << "Running tests...\n";
    // Test DatabaseManager
    testDBCreate();
}