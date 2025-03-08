#pragma once
#include <set>
#include <Transaction.hpp>

class BudgetManager{
public:
    void addExpense(const Transaction& t);
    void viewExpenses();
    void validateDate(const std::string& date);
    void validateAmount(double amount);

private:
    std::multiset<Transaction> transactions;
};
