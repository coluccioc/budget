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
//#include "BudgetManager.hpp"  // Include budget manager class


class UI /*: public QWidget */{
public:
    void run();
    //Q_OBJECT

private:
    void displayMenu();
    int handleInput(int choice);
    void addExpense();
    void viewExpenses();
    std::multiset<Transaction> transactions;
};
