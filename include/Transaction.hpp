#pragma once
#include <string>
#include <nlohmann/json.hpp>

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

inline void to_json(nlohmann::json& j, const Transaction& t)
{
    j = nlohmann::json{
        {"id", t.id},
        {"description", t.description},
        {"amount", t.amount},
        {"date", t.date},
        {"category", t.category}
    };
};