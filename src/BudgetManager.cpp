#pragma once
#include "BudgetManager.hpp"

/*
    VALIDATION RESULT OPTIONS:
    SUCCESS,
    EMPTY,
    INVALID_DATE,
    NEGATIVE,
    NONNUMERIC,
    EXCEEDS
*/
BudgetManager::BudgetManager(std::unique_ptr<DatabaseManager> db) : 
    db(std::move(db)) {}; // Initialize the databse manager

// addExpense expects a validated transaction object
void BudgetManager::addExpense(const Transaction& t)
{
    db->insertTransaction(t);
}

void BudgetManager::addExpenseList(const std::vector<Transaction>& transactions)
{
    for (const auto& transaction : transactions)
    {
        db->insertTransaction(transaction);
    }
}

const std::vector<Transaction>& BudgetManager::getTransactions()
{
    db->fetchTransactions();
    return db->getTransactions();
}

void BudgetManager::deleteAllTransactions()
{
    db->deleteAllTransactions();
    transactions.clear(); // Clear the in-memory transactions as well
}
