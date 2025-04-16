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

void BudgetManager::addExpense(const Transaction& t)
{
    transactions.insert(t);
}

const std::multiset<Transaction>& BudgetManager::getTransactions() const
{
    return transactions;
}

normalDateStatus BudgetManager::validateAndNormalizeDate(const std::string& dateStr)
{
    const std::vector<std::string> formats = {
        "%m/%d/%Y", // MM/DD/YYYY
        "%m-%d-%Y", // MM-DD-YYYY
        "%Y/%m/%d", // YYYY/MM/DD
        "%Y-%m-%d", // YYYY-MM-DD
        "%Y%m%d",   // YYYYMMDD
        "%m%d%Y"    // MMDDYYYY
    };
    normalDateStatus result;
    if (dateStr.empty())
    {
        result.status = ValidationResult::EMPTY;
        result.normalDate = "";
        return result;
    }

    for (const auto& format : formats)
    {
        std::istringstream input(dateStr);
        date::sys_days parsedDate;

        input >> date::parse(format, parsedDate);
        if (!input.fail())
        {
            result.status = ValidationResult::SUCCESS;
            result.normalDate = date::format("%Y-%m-%d", parsedDate); //Normalized to YYYY-MM-DD
            return result;
        }
    }

    result.status = ValidationResult::INVALID_DATE;
    result.normalDate = dateStr; // Return the original string if parsing fails
    return result;
}

ValidationResult BudgetManager::validateAmount(const std::string& amount)
{
    //Do stuff
    if (amount.empty())
    {
        return ValidationResult::EMPTY;
    }
    if (amount.find_first_not_of("0123456789.") != std::string::npos)
    {
        return ValidationResult::NONNUMERIC;
    }
    if (amount.find_first_of("-") != std::string::npos)
    {
        return ValidationResult::NEGATIVE;
    }
    if (std::stod(amount) > 9999999999999999.99)
    {
        return ValidationResult::EXCEEDS;
    }
    return ValidationResult::SUCCESS;
}

ValidationResult BudgetManager::validateString(const std::string& str)
{
    //Do stuff
    if (str.empty())
    {
        return ValidationResult::EMPTY;
    }
    if (str.length() > 50)
    {
        return ValidationResult::EXCEEDS;
    }
    return ValidationResult::SUCCESS;
}
