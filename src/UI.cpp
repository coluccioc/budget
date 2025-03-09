#pragma once
#include "../include/UI.hpp"

void UI::run(){
    int choice;
    do{
        displayMenu();
        std::cin >> choice;
        if(handleInput(choice))
        {
            break;
        }
    }while(choice != 0);
}

void UI::displayMenu(){
    std::cout << "+++ Budget Menu +++\n";
    std::cout << "1. Add expense\n";
    std::cout << "2. View expenses\n";
    std::cout << "0. Exit\n";
}

int UI::handleInput(int choice){
    switch(choice){
        case 1:
            addExpense();
            return 0;
        case 2:
            viewExpenses();
            return 0;
        case 0:
            return 1;
        default:
            std::cout << "Invalid selection, please try again\n";
            return 0;
    }
}

std::string validationResponse(ValidationResult result){
    switch(result){
        case ValidationResult::SUCCESS:
            return "";
        case ValidationResult::EMPTY:
            return "Cannot be empty";
        case ValidationResult::INVALID_DATE:
            return "Date must be in format YYYY/MM/DD";
        case ValidationResult::NEGATIVE:
            return "Cannot be negative";
        case ValidationResult::EXCEEDS:
            return "Exceeds limit";
        case ValidationResult::NONNUMERIC:
            return "Must be numeric";
        default:
            return "";
    }
}

void UI::addExpense(){
    ValidationResult result;
    std::string date;
    std::string description;
    std::string amountStr;
    double amount;
    std::string category;

    do{
        std::cout << "Enter expense date (YYYY/MM/DD): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, date);
        date = UI::trim(date);

        result = BudgetManager::validateDate(date);
        if(result != ValidationResult::SUCCESS){
            std::cout << "Invalid date: " << validationResponse(result) << "\n";
        }
    }while(result != ValidationResult::SUCCESS);


    do{
    std::cout << "Enter expense name: ";
    std::getline(std::cin, description);
    description = UI::trim(description);

    result = BudgetManager::validateString(description);
    if(result != ValidationResult::SUCCESS){
        std::cout << "Invalid name: " << validationResponse(result) << "\n";
    }
    }while(result != ValidationResult::SUCCESS);


    do{
        std::cout << "Enter expense amount: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, amountStr);
        amountStr = UI::trim(amountStr);

        result = BudgetManager::validateAmount((amountStr));
        if(result != ValidationResult::SUCCESS){
            std::cout << "Invalid amount: " << validationResponse(result) << "\n";
        }
        else {
            amount = std::stod(amountStr);
        }
    }while(result != ValidationResult::SUCCESS);

    std::cout << "Enter expense category: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, category);

    Transaction t{description, amount, date, category};

    bm.addExpense(t);

    std::cout << "Expense \" " << description << " \" added successfully. $" << amount << "\n";
}

void UI::viewExpenses(){
    std::cout << "Viewing expenses...\n";
    for(auto& t: bm.getTransactions()){
        std::cout << t.date << " " << t.description << " $" << t.amount << " " << t.category << "\n";
    }
}

std::string UI::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return ""; // All whitespace
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}
