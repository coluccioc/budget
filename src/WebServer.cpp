#include "../include/WebServer.hpp"

void WebServer::run()
{
    crow::SimpleApp app;

    // Define your routes here
    CROW_ROUTE(app, "/transactions")
    ([this]() {
        auto transactions = budgetManager->getTransactions();
        nlohmann::json response;
        for (const auto& transaction : transactions) {
            response.push_back(transaction);
        }
        return crow::response{response.dump()};
    });

    // Start the server
    app.port(18080).multithreaded().run();
}