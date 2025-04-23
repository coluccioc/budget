#pragma once
#include "../SQLite/sqlite3.h"
#include <string>
#include <set>
#include "Transaction.hpp"
#include <iostream>

class DatabaseManager
{
    public:
        DatabaseManager(const std::string& dbPath);
        ~DatabaseManager();
        bool isOpen();
        bool fetchTransactions();
        bool insertTransaction(const Transaction& transaction);
        const std::multiset<Transaction>& getTransactions();
    private:
        bool initializeDatabase(); // sets up table
        bool openDatabase();
        void closeDatabase();
        sqlite3* db;
        std::string databasePath;
        std::multiset<Transaction> transactions; // Store transactions in memory
};
