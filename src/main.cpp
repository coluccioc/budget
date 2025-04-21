#pragma once
#include "../include/UI.hpp"
#include "sqlite3.h"
#include "DatabaseManager.hpp"

int main()
{
    auto db = std::make_unique<DatabaseManager>("transactions.db");
    auto bm = std::make_unique<BudgetManager>(std::move(db));
    UI appUI(std::move(bm));
    appUI.run();
    return 0;
}
