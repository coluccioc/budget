#pragma once
#include "../include/BudgetManager.hpp"

/*
    VALIDATION RESULT OPTIONS:
    SUCCESS,
    EMPTY,
    INVALID_DATE,
    NEGATIVE,
    NONNUMERIC,
    EXCEEDS
*/

void BudgetManager::addExpense(const Transaction& t){
    transactions.insert(t);
}

const std::multiset<Transaction>& BudgetManager::getTransactions() const{
    return transactions;
}

ValidationResult BudgetManager::validateDate(const std::string& dateStr){
    if (dateStr.empty()){
        return ValidationResult::EMPTY;
    }
    std::istringstream in1(dateStr);
    std::istringstream in2(dateStr);
    date::sys_days date;

    //Try MM/DD/YYYY first
    in1 >> date::parse("%m/%d/%Y", date);
    if (!in1.fail() && in1.eof()) {
        return ValidationResult::SUCCESS;
    }

    // Try M/D/YY
    in2 >> date::parse("%m/%d/%y", date);
    if (!in2.fail() && in2.eof()) {
        return ValidationResult::SUCCESS;
    }

    return ValidationResult::INVALID_DATE;
}

ValidationResult BudgetManager::validateAmount(const std::string& amount){
    //Do stuff
    if (amount.empty()){
        return ValidationResult::EMPTY;
    }
    if (amount.find_first_not_of("0123456789.") != std::string::npos){
        return ValidationResult::NONNUMERIC;
    }
    if (amount.find_first_of("-") != std::string::npos){
        return ValidationResult::NEGATIVE;
    }
    if (std::stod(amount) > 9999999999999999.99){
        return ValidationResult::EXCEEDS;
    }
    return ValidationResult::SUCCESS;
}

ValidationResult BudgetManager::validateString(const std::string& str){
    //Do stuff
    if (str.empty()){
        return ValidationResult::EMPTY;
    }
    if (str.length() > 50){
        return ValidationResult::EXCEEDS;
    }
    return ValidationResult::SUCCESS;
}
