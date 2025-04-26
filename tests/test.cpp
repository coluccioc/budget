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

void testDBOpen()
{
    DatabaseManager db("SQLite/test.db");

}

void testDBCreate()
{
    DatabaseManager db("SQLite/test.db");
    expect(db.isOpen(), "Database Creation Test");
}

void testDBInsert()
{
    DatabaseManager db("SQLite/test.db");
    Transaction t{"Test", 100.00, "2023-10-01", "TestCategory"};
    expect(db.insertTransaction(t), "Database Insert Test");
}

void testDBFetch()
{
    DatabaseManager db("SQLite/test.db");
    expect(db.fetchTransactions(), "Database Fetch Test");
}

void testDBDelete()
{
    DatabaseManager db("SQLite/test.db");
    expect(db.deleteAllTransactions(), "Database Delete Test");
}

void testDBInsertAndRetrieve()
{
    DatabaseManager db("SQLite/test.db");
    Transaction t{"Test", 100.00, "2023-10-01", "TestCategory"};
    Transaction t2;
    db.deleteAllTransactions(); // Clear any existing transactions
    db.insertTransaction(t);
    db.fetchTransactions();
    const auto& transactions = db.getTransactions();
    t2 = *transactions.begin(); //Get first transaction
    // Checking to see if the transaction matches and is the only one in the database
    expect(t == t2 && transactions.size() == 1, "Database Insert and Retrieve Test");
}

int main() 
{
    std::cout << "Running tests...\n";
    // Test DatabaseManager
    testDBCreate();
    testDBFetch();
    testDBInsert();
    testDBDelete();
    testDBInsertAndRetrieve();
}
