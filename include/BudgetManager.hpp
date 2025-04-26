#pragma once
#include <set>
#include <Transaction.hpp>
#include "date/date.h"
#include <sstream>
#include <vector>
#include "DatabaseManager.hpp"

enum class ValidationResult
{
    SUCCESS,
    EMPTY,
    INVALID_DATE,
    NEGATIVE,
    NONNUMERIC,
    EXCEEDS
};

struct normalDateStatus
{
    ValidationResult status;
    std::string normalDate;
};

class BudgetManager
{
public:
    BudgetManager(std::unique_ptr<DatabaseManager> db);
    void addExpense(const Transaction& t);
    const std::multiset<Transaction>& getTransactions();
    void deleteAllTransactions();
    static normalDateStatus validateAndNormalizeDate(const std::string& date);
    static ValidationResult validateAmount(const std::string& amount);
    static ValidationResult validateString(const std::string& str);


private:
    std::multiset<Transaction> transactions;
    std::unique_ptr<DatabaseManager> db;
};
