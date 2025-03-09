#pragma once
#include "../include/BudgetManager.hpp"

void BudgetManager::addExpense(const Transaction& t){
    transactions.insert(t);
}

const std::multiset<Transaction>& BudgetManager::getTransactions() const{
    return transactions;
}

ValidationResult BudgetManager::validateDate(const std::string& date){
    if (date.empty()){
    }
    return ValidationResult::SUCCESS;
}

ValidationResult BudgetManager::validateAmount(const std::string& amount){
    //Do stuff
    return ValidationResult::SUCCESS;
}

ValidationResult BudgetManager::validateString(const std::string& str){
    //Do stuff
    return ValidationResult::SUCCESS;
}
