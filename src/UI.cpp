#include "include/UI.hpp"

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

void displayMenu(){
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
