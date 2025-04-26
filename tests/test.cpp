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

void testDBInsert()
{
    DatabaseManager db("test.db");
    Transaction t{"Test", 100.00, "2023-10-01", "TestCategory"};
    expect(db.insertTransaction(t), "Database Insert Test");
}

void testDBFetch()
{
    DatabaseManager db("test.db");
    expect(db.fetchTransactions(), "Database Fetch Test");
}

void testDBDelete()
{
    DatabaseManager db("test.db");
    expect(db.deleteAllTransactions(), "Database Delete Test");
}

int main() 
{
    std::cout << "Running tests...\n";
    // Test DatabaseManager
    testDBCreate();
    testDBFetch();
    testDBDelete();
    testDBInsert();
}
