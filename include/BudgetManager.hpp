#pragma once
#include "Validation.hpp"
#include "Transaction.hpp"
#include "DatabaseManager.hpp"
#include "Util.hpp"


class BudgetManager
{
public:
    BudgetManager(std::unique_ptr<DatabaseManager> db);
    void addExpense(const Transaction& t);
    void addExpenseList(const std::vector<Transaction>& transactions);
    const std::vector<Transaction>& getTransactions();
    void deleteAllTransactions();

private:
    std::vector<Transaction> transactions;
    std::unique_ptr<DatabaseManager> db;
};
