#pragma once
#include <string>

struct Transaction
{
    std::string description;
    double amount;
    std::string date;
    std::string category;
    int id = 0; // 0 means not set

    bool operator<(const Transaction& other) const
    { 
        return date < other.date;  // Orders by date, but allows duplicates
    }

    bool operator==(const Transaction& other) const
    {
        return description == other.description && amount == other.amount && date == other.date && category == other.category;
    }
};
