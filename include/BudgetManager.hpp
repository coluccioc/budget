#pragma once
#include <set>
#include <Transaction.hpp>

enum class ValidationResult{
    SUCCESS,
    EMPTY,
    INVALID_DATE,
    NEGATIVE,
    NONNUMERIC,
    EXCEEDS
};

class BudgetManager{
public:
    void addExpense(const Transaction& t);
    const std::multiset<Transaction>& getTransactions() const;
    static ValidationResult validateDate(const std::string& date);
    static ValidationResult validateAmount(const std::string& amount);
    static ValidationResult validateString(const std::string& str);


private:
    std::multiset<Transaction> transactions;
};
