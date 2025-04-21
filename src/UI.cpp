#include "../include/UI.hpp"

UI::UI(std::unique_ptr<BudgetManager> bm) : bm(std::move(bm)) {};

void UI::run()
{
    std::string choiceStr;
    int choice;
    do
    {
        displayMenu();
        std::getline(std::cin, choiceStr);
        try{
            choice = std::stoi(choiceStr);
        }
        catch(...){
            choice = -1;
        }
        if(handleInput(choice))
        {
            break;
        }
    }
    while(choice != 0);
}

void UI::displayMenu()
{
    std::cout << "+++ Budget Menu +++\n";
    std::cout << "1. Add expense\n";
    std::cout << "2. View expenses\n";
    std::cout << "3. Run script\n";
    std::cout << "0. Exit\n";
}

int UI::handleInput(int choice)
{
    switch(choice)
    {
        case 1:
            addExpense();
            return 0;
        case 2:
            viewExpenses();
            return 0;
        case 3:
            runScript("python src\\script.py");
            return 0;
        case 0:
            return 1;
        default:
            std::cout << "Invalid selection, please try again\n";
            return 0;
    }
}

std::string validationResponse(ValidationResult result)
{
    switch(result)
    {
        case ValidationResult::SUCCESS:
            return "";
        case ValidationResult::EMPTY:
            return "Cannot be empty";
        case ValidationResult::INVALID_DATE:
            return "Date must be in format MM/DD/YYYY";
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

void UI::addExpense()
{
    ValidationResult result;
    std::string date;
    std::string description;
    std::string amountStr;
    double amount;
    std::string category;

    do
    {
        std::cout << "Enter expense date (MM/DD/YYYY): ";
        std::getline(std::cin, date);
        date = UI::trim(date);

        auto normalizedDateStatus = BudgetManager::validateAndNormalizeDate(date);
        result = normalizedDateStatus.status;
        if(result != ValidationResult::SUCCESS)
        {
            std::cout << "Invalid date: " << validationResponse(result) << "\n";
        }
        else
        {
            date = normalizedDateStatus.normalDate;
        }
    }
    while(result != ValidationResult::SUCCESS);


    do
    {
    std::cout << "Enter expense name: ";
    std::getline(std::cin, description);
    description = UI::trim(description);

    result = BudgetManager::validateString(description);
    if(result != ValidationResult::SUCCESS){
        std::cout << "Invalid name: " << validationResponse(result) << "\n";
    }
    }
    while(result != ValidationResult::SUCCESS);


    do
    {
        std::cout << "Enter expense amount: ";
        std::getline(std::cin, amountStr);
        amountStr = UI::trim(amountStr);

        result = BudgetManager::validateAmount((amountStr));
        if(result != ValidationResult::SUCCESS){
            std::cout << "Invalid amount: " << validationResponse(result) << "\n";
        }
        else {
            amount = std::round(std::stod(amountStr) * 100) / 100; //rounding to nearest 100th
        }
    }
    while(result != ValidationResult::SUCCESS);

    
    do
    {
        std::cout << "Enter expense category: ";
        std::getline(std::cin, category);
        category = UI::trim(category);

        result = BudgetManager::validateString(category);
        if (result != ValidationResult::SUCCESS){
            std::cout << "Invalid category: " << validationResponse(result) << "\n";
        }
    }
    while(result != ValidationResult::SUCCESS);

    Transaction t{description, amount, date, category};

    bm->addExpense(t);

    std::cout << "Expense \" " << description << " \" added successfully. $" << amount << "\n";
}

void UI::viewExpenses()
{
    std::cout << "Viewing expenses...\n";
    for(auto& t: bm->getTransactions())
    {
        std::cout << t.date << " " << t.description << " $" << t.amount << " " << t.category << "\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void UI::runScript(const std::string& scriptPath)
{
    system(scriptPath.c_str());
}

std::string UI::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return ""; // All whitespace
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}
