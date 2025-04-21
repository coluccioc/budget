#pragma once


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>
#include <iostream>
#include <limits>
#include "Transaction.hpp"
#include <set>
#include "BudgetManager.hpp"  // Include budget manager class
#include <cmath> // for rounding
#include <thread>  // For sleep_for
#include <chrono>  // For time units
#include <cstdlib>


class UI /*: public QWidget */
{
public:
    void run();
    UI(std::unique_ptr<BudgetManager> bm);
    //Q_OBJECT

private:
    std::unique_ptr<BudgetManager> bm;
    void displayMenu();
    int handleInput(int choice);
    void addExpense();
    void viewExpenses();
    void runScript(const std::string& scriptPath);
    std::string trim(const std::string& str);
};
