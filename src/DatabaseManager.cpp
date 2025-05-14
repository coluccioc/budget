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
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool DatabaseManager::openDatabase()
{
    if (sqlite3_open(databasePath.c_str(), &db) != SQLITE_OK)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::isOpen()
{
    if (db)
    {
        return true;
    }
    return false;
}

bool DatabaseManager::insertTransaction(const Transaction& transaction)
{
    const char* sql = "INSERT INTO transactions (description, amount, date, category) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    // Bind parameters to prepared statement
    sqlite3_bind_text(stmt, 1, transaction.description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, transaction.amount);
    sqlite3_bind_text(stmt, 3, transaction.date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, transaction.category.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to insert transaction: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool DatabaseManager::fetchTransactions(const std::string& startDate, const std::string& endDate)
{
    // Conditional date filtering
    std::string sql = "SELECT id, description, amount, date, category FROM transactions ";
    bool hasStart = !startDate.empty();
    bool hasEnd = !endDate.empty();

    // Structure SQL query based on provided date arguments
    if (hasStart && hasEnd)
    {
        sql += "WHERE date BETWEEN ? AND ? ";
    }
    else if (hasStart)
    {
        sql += "WHERE date >= ? ";
    }
    else if (hasEnd)
    {
        sql += "WHERE date <= ? ";
    }
    sql += "ORDER BY date DESC;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    transactions.clear(); // Clear previous transactions

    // Bind parameters to prepared statement conditionally
    int bindIndex = 1;
    if (hasStart)
    {
        sqlite3_bind_text(stmt, bindIndex, startDate.c_str(), -1, SQLITE_STATIC);
        bindIndex++;
    }
    if (hasEnd)
    {
        sqlite3_bind_text(stmt, bindIndex, endDate.c_str(), -1, SQLITE_STATIC);
        bindIndex++;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Transaction transaction;
        transaction.id = sqlite3_column_int(stmt, 0);
        transaction.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        transaction.amount = sqlite3_column_double(stmt, 2);
        transaction.date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        transaction.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        transactions.push_back(transaction);
    }

    sqlite3_finalize(stmt);
    return true;
}

const std::vector<Transaction>& DatabaseManager::getTransactions()
{
    return transactions;
}

bool DatabaseManager::deleteAllTransactions()
{
    const char* sql = "DELETE FROM transactions;";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to clear transactions: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
