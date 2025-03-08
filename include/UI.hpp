#pragma once


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>
#include <vector>
#include <iostream>
#include <limits>
#include "../include/Transaction.hpp"
#include <set>
#include "../include/BudgetManager.hpp"  // Include budget manager class


class UI /*: public QWidget */{
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
