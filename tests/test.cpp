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

//Test BudgetManager
void testBudgetManagerAddExpenseGetTransaction()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    Transaction t{"Test", 150.00, "2024-10-01", "TestCategory"};
    bm.addExpense(t);
    const auto& transactions = bm.getTransactions();
    Transaction t2 = *transactions.begin();
    expect(t == t2 && transactions.size() == 1, "BudgetManager Add Expense Test");
}

void testBudgetManagerValidateAndNormalizeDate()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAndNormalizeDate("10/01/2023");
    expect(result.status == ValidationResult::SUCCESS && result.normalDate == "2023-10-01", "BudgetManager Validate and Normalize Date Test");
}

void testBudgetManagerValidateAndNormalizeDateInvalid()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAndNormalizeDate("2024-15-01");
    expect(result.status == ValidationResult::INVALID_DATE, "BudgetManager Validate and Normalize Date Invalid Test");
}

void testBudgetManagerValidateAndNormalizeDateEmpty()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAndNormalizeDate("");
    expect(result.status == ValidationResult::EMPTY, "BudgetManager Validate and Normalize Date Empty Test");
}

void testBudgetManagerValidateAmount()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("100.00");
    expect(result == ValidationResult::SUCCESS, "BudgetManager Validate Amount Test");
}

void testBudgetManagerValidateAmountNegative()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("-100.00");
    expect(result == ValidationResult::NEGATIVE, "BudgetManager Validate Amount Negative Test");
}

void testBudgetManagerValidateAmountNonNumeric()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("abc");
    expect(result == ValidationResult::NONNUMERIC, "BudgetManager Validate Amount Non-Numeric Test");
}

void testBudgetManagerValidateAmountExceeds()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("1000000000.00"); // Assuming this exceeds the limit
    expect(result == ValidationResult::EXCEEDS, "BudgetManager Validate Amount Exceeds Test");
}

void testBudgetManagerValidateString()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateString("TestCategory");
    expect(result == ValidationResult::SUCCESS, "BudgetManager Validate String Test");
}

void testBudgetManagerValidateStringEmpty()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateString("");
    expect(result == ValidationResult::EMPTY, "BudgetManager Validate String Empty Test");
}

void testBudgetManagerValidateStringExceeds()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateString("This is a very long string that exceeds the maximum length allowed for a category name.");
    expect(result == ValidationResult::EXCEEDS, "BudgetManager Validate String Exceeds Test");
}

int main()
{
    std::cout << "Running database tests...\n";
    // Test DatabaseManager
    testDBCreate();
    testDBFetch();
    testDBInsert();
    testDBDelete();
    testDBInsertAndRetrieve();

    testDBDelete(); // Clean up the database after tests

    // Test BudgetManager
    std::cout << "Running budget manager tests...\n";
    testBudgetManagerAddExpenseGetTransaction();
    testBudgetManagerValidateAndNormalizeDate();
    testBudgetManagerValidateAndNormalizeDateInvalid();
    testBudgetManagerValidateAndNormalizeDateEmpty();
    testBudgetManagerValidateAmount();
    testBudgetManagerValidateAmountNegative();
    testBudgetManagerValidateAmountNonNumeric();
    testBudgetManagerValidateAmountExceeds();
    testBudgetManagerValidateString();
    testBudgetManagerValidateStringEmpty();
    testBudgetManagerValidateStringExceeds();
    
}
