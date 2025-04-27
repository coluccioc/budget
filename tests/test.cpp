#pragma once
#include <cassert>
#include <iostream>
#include "../include/DatabaseManager.hpp"
#include "../include/BudgetManager.hpp"

void expect(bool condition, const std::string& testName, bool reportPassed = true)
{
    if(condition && reportPassed) std::cout <<"[PASS]" << testName << "\n";
    else if(!condition) std::cout << "[FAIL]" << testName << "\n";

}

void testDBOpen(bool reportPassed)
{
    DatabaseManager db("SQLite/test.db");
    expect(db.isOpen(), "Database Open Test", reportPassed);
}

void testDBCreate(bool reportPassed)
{
    DatabaseManager db("SQLite/test.db");
    expect(db.isOpen(), "Database Creation Test", reportPassed);
}

void testDBInsert(bool reportPassed)
{
    DatabaseManager db("SQLite/test.db");
    Transaction t{"Test", 100.00, "2023-10-01", "TestCategory"};
    expect(db.insertTransaction(t), "Database Insert Test", reportPassed);
}

void testDBFetch(bool reportPassed)
{
    DatabaseManager db("SQLite/test.db");
    expect(db.fetchTransactions(), "Database Fetch Test", reportPassed);
}

void testDBDelete(bool reportPassed)
{
    DatabaseManager db("SQLite/test.db");
    expect(db.deleteAllTransactions(), "Database Delete Test", reportPassed);
}

void testDBInsertAndRetrieve(bool reportPassed)
{
    DatabaseManager db("SQLite/test.db");
    Transaction t{"Test", 100.00, "2023-10-01", "TestCategory"};
    db.deleteAllTransactions(); // Clear any existing transactions
    db.insertTransaction(t);
    db.fetchTransactions();
    const auto& transactions = db.getTransactions();
    // Checking to see if the transaction matches and is the only one in the database
    expect(t == *transactions.begin() && transactions.size() == 1, "Database Insert and Retrieve Test", reportPassed);
}

//Test BudgetManager
void testBudgetManagerGetEmptyTransactions(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    bm.deleteAllTransactions();
    const auto& transactions = bm.getTransactions();
    expect(transactions.empty(), "BudgetManager Get Empty Transactions Test", reportPassed);
}

void testBudgetManagerAddExpenseGetTransaction(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    bm.deleteAllTransactions(); // Clear any existing transactions
    Transaction t{"Test", 150.00, "2024-10-01", "TestCategory"};
    bm.addExpense(t);
    const auto& transactions = bm.getTransactions();
    expect(t == *transactions.begin() && transactions.size() == 1, "BudgetManager Add Expense Test", reportPassed);
}

void testBudgetManagerValidateAndNormalizeDate(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAndNormalizeDate("10/01/2023");
    expect(result.status == ValidationResult::SUCCESS && result.normalDate == "2023-10-01", 
        "BudgetManager Validate and Normalize Date Test", reportPassed);
}

void testBudgetManagerValidateAndNormalizeDateInvalid(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAndNormalizeDate("2024-15-01");
    expect(result.status == ValidationResult::INVALID_DATE, "BudgetManager Validate and Normalize Date Invalid Test", reportPassed);
}

void testBudgetManagerValidateAndNormalizeDateEmpty(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAndNormalizeDate("");
    expect(result.status == ValidationResult::EMPTY, "BudgetManager Validate and Normalize Date Empty Test", reportPassed);
}

void testBudgetManagerValidateAmount(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("100.00");
    expect(result == ValidationResult::SUCCESS, "BudgetManager Validate Amount Test", reportPassed);
}

void testBudgetManagerValidateAmountNegative(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("-100.00");
    expect(result == ValidationResult::NEGATIVE, "BudgetManager Validate Amount Negative Test", reportPassed);
}

void testBudgetManagerValidateAmountNonNumeric(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("abc");
    expect(result == ValidationResult::NONNUMERIC, "BudgetManager Validate Amount Non-Numeric Test", reportPassed);
}

void testBudgetManagerValidateAmountExceeds(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateAmount("1000000000.00"); // Assuming this exceeds the limit
    expect(result == ValidationResult::EXCEEDS, "BudgetManager Validate Amount Exceeds Test", reportPassed);
}

void testBudgetManagerValidateString(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateString("TestCategory");
    expect(result == ValidationResult::SUCCESS, "BudgetManager Validate String Test", reportPassed);
}

void testBudgetManagerValidateStringEmpty(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateString("");
    expect(result == ValidationResult::EMPTY, "BudgetManager Validate String Empty Test", reportPassed);
}

void testBudgetManagerValidateStringExceeds(bool reportPassed)
{
    auto db = std::make_unique<DatabaseManager>("SQLite/test.db");
    BudgetManager bm(std::move(db));
    auto result = bm.validateString("This is a very long string that exceeds the maximum length allowed for a category name.");
    expect(result == ValidationResult::EXCEEDS, "BudgetManager Validate String Exceeds Test", reportPassed);
}

void runTests(bool reportPassed = true)
{
    std::cout << "Running database tests...\n";
    // Test DatabaseManager
    testDBCreate(reportPassed);
    testDBFetch(reportPassed);
    testDBInsert(reportPassed);
    testDBDelete(reportPassed);
    testDBInsertAndRetrieve(reportPassed);

    testDBDelete(false); // Clean up the database after tests

    // Test BudgetManager
    std::cout << "Running budget manager tests...\n";
    testBudgetManagerAddExpenseGetTransaction(reportPassed);
    testBudgetManagerValidateAndNormalizeDate(reportPassed);
    testBudgetManagerValidateAndNormalizeDateInvalid(reportPassed);
    testBudgetManagerValidateAndNormalizeDateEmpty(reportPassed);
    testBudgetManagerValidateAmount(reportPassed);
    testBudgetManagerValidateAmountNegative(reportPassed);
    testBudgetManagerValidateAmountNonNumeric(reportPassed);
    testBudgetManagerValidateAmountExceeds(reportPassed);
    testBudgetManagerValidateString(reportPassed);
    testBudgetManagerValidateStringEmpty(reportPassed);
    testBudgetManagerValidateStringExceeds(reportPassed);
}

void reportFailedTests()
{
    runTests(false); // Run tests with reportPassed set to false
}

int main()
{
    std::cout << "Select:\n"
            "1. Run all tests\n"
            "2. Report failed tests only\n"
            "3. Exit\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    switch(choice)
    {
        case 1:
            runTests();
            break;
        case 2:
            reportFailedTests();
            break;
        case 3:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Exiting...\n";
            return 1;
    }
}
