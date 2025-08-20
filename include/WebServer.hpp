#pragma once

#define CROW_USE_BOOST
#include <boost/asio.hpp>
#include "crow.h"

#include "BudgetManager.hpp"
#include <nlohmann/json.hpp>
#include <memory>

class WebServer {
    public:
        WebServer(std::unique_ptr<BudgetManager> budgetManager)
            : budgetManager(std::move(budgetManager)) {
            }
        void run();
    private:
        std::unique_ptr<BudgetManager> budgetManager;
};
