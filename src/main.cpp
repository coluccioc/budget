#pragma once
#include "WebServer.hpp"

int main()
{
    auto db = std::make_unique<DatabaseManager>("SQLite/transactions.db");
    auto bm = std::make_unique<BudgetManager>(std::move(db));
    WebServer server(std::move(bm));
    server.run();
    return 0;
}
