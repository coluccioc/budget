#include "../include/DatabaseManager.hpp"

DatabaseManager::DatabaseManager(const std::string& dbPath)
    : db(nullptr), databasePath(dbPath)
{
    if (!openDatabase())
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        closeDatabase();
        db = nullptr;
    }
    else
    {
        std::cout << "Database opened successfully." << std::endl;
        initializeDatabase();
    }
}
DatabaseManager::~DatabaseManager() 
{
    closeDatabase();
}
bool DatabaseManager::initializeDatabase()
{
    const char* sql = "CREATE TABLE IF NOT EXISTS transactions ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "description TEXT NOT NULL,"
                      "amount REAL NOT NULL,"
                      "date TEXT NOT NULL,"
                      "category TEXT NOT NULL);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Failed to create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool DatabaseManager::openDatabase()
{
    if (sqlite3_open(databasePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase()
{
    if (db) {
        std::cout << "DB CLOSED!";
        sqlite3_close(db);
        db = nullptr;
    }
}
bool DatabaseManager::insertTransaction(const Transaction& transaction)
{
    std::cout << "Beginning";
    const char* sql = "INSERT INTO transactions (description, amount, date, category) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    std::cout << "preparing";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "Binding";
    sqlite3_bind_text(stmt, 1, transaction.description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, transaction.amount);
    sqlite3_bind_text(stmt, 3, transaction.date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, transaction.category.c_str(), -1, SQLITE_STATIC);

    std::cout << "Bound";
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to insert transaction: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    std::cout << "Inserted";
    sqlite3_finalize(stmt);
    return true;
}
bool DatabaseManager::fetchTransactions()
{
    const char* sql = "SELECT description, amount, date, category FROM transactions;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Transaction transaction;
        transaction.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        transaction.amount = sqlite3_column_double(stmt, 1);
        transaction.date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        transaction.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        transactions.insert(transaction);
    }

    sqlite3_finalize(stmt);
    return true;
}
const std::multiset<Transaction>& DatabaseManager::getTransactions(){
    return transactions;
}