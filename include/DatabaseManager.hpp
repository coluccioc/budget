#pragma once
#include "../SQLite/sqlite3.h"
#include <string>
#include <vector>
#include "Transaction.hpp"
#include <iostream>

class DatabaseManager
{
    public:
        DatabaseManager(const std::string& dbPath);
        ~DatabaseManager();
        bool isOpen();
        bool fetchTransactions(const std::string& startDate = "", const std::string& endDate = "");
        bool insertTransaction(const Transaction& transaction);
        const std::vector<Transaction>& getTransactions();
        bool deleteAllTransactions();
    private:
        bool initializeDatabase(); // sets up table
        bool openDatabase();
        void closeDatabase();
        sqlite3* db;
        std::string databasePath;
        std::vector<Transaction> transactions; // Store transactions in memory
};
