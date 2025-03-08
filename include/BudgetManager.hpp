#pragma once
#include <set>
#include <Transaction.hpp>

enum class ValidationResult{
    SUCCESS,
    EMPTY,
    INVALID,
    NEGATIVE,
    EXCEEDS
};

class BudgetManager{
public:
    void addExpense(const Transaction& t);
    const std::multiset<Transaction>& getTransactions() const;
    static ValidationResult validateDate(const std::string& date);
    static ValidationResult validateAmount(double amount);
    static ValidationResult validateString(const std::string& str);


private:
    std::multiset<Transaction> transactions;
};
