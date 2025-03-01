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

void UI::addExpense(){
    std::string date;
    std::string name;
    double amount;
    std::string category;

    std::cout << "Enter expense date (YYYY/MM/DD): ";
    std::getline(std::cin, date);

    std::cout << "Enter expense name: ";
    std::getline(std::cin, name);

    std::cout << "Enter expense amount: ";
    while(!(std::cin >> amount) || amount < 0){
        std::cout << "Invalid input, please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter expense category: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, category);

    transactions.insert({name, amount, date, category});

    std::cout << "Expense \" " << name << " \" added successfully. $" << amount << "\n";
}

void UI::viewExpenses(){
    std::cout << "Viewing expenses...\n";
    for(auto& t: transactions){
        std::cout << t.date << " " << t.description << " $" << t.amount << " " << t.category << "\n";
    }
}