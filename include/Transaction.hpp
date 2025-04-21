#pragma once
#include <string>

struct Transaction
{
    std::string description;
    double amount;
    std::string date;
    std::string category;

    bool operator<(const Transaction& other) const
    { 
        return date < other.date;  // Orders by date, but allows duplicates
    }
};
