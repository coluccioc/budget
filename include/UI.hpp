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


class UI /*: public QWidget */
{
public:
    void run();
    //Q_OBJECT

private:
    //Probably making this static once I have a DB running. For now we instantiate
    BudgetManager bm;
    void displayMenu();
    int handleInput(int choice);
    void addExpense();
    void viewExpenses();
    std::string trim(const std::string& str);
};
