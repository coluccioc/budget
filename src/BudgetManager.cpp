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
}

ValidationResult BudgetManager::validateAmount(double amount){
    //Do stuff
}

ValidationResult BudgetManager::validateString(const std::string& str){
    //Do stuff
}
