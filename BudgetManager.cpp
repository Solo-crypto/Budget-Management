#include "BudgetManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm> // for std::sort

BudgetManager::BudgetManager(const std::string& file) : filename(file) {
    loadFromFile();
}

// add income transaction
void BudgetManager::addIncome(double amount, const std::string& description, const std::string& date) {
    transactions.push_back({ "Income", amount, description, date });
}

void BudgetManager::addExpense(double amount, const std::string& description, const std::string& date) {
    transactions.push_back({ "Expense", amount, description, date });
}

double BudgetManager::getBalance() const {
    double balance = 0;
    for (const auto& t : transactions) {
        if (t.type == "Income")
            balance += t.amount;
        else
            balance -= t.amount;
    }
    return balance;
}

// sort transactions by date
void BudgetManager::sortTransactionsByDate() {
    std::sort(transactions.begin(), transactions.end(),
        [](const Transaction& a, const Transaction& b) {
            return a.date < b.date;
        });
}

// show the transactions sorted by date
void BudgetManager::showTransactions() {
    sortTransactionsByDate();
    std::cout << "\n-- - Transaktionen(nach Datum sortiert) -- - \n";
    for (const auto& t : transactions) {
        std::cout << t.date << " | " << t.type << ": "
            << std::fixed << std::setprecision(2)
            << t.amount << " EUR - " << t.description << "\n";
    }
}

void BudgetManager::saveToFile() const {
    std::ofstream file(filename);
    for (const auto& t : transactions) {
        file << t.type << "," << t.amount << "," << t.description << "," << t.date << "\n";
    }
}

void BudgetManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file) return;

    Transaction t;
    std::string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        t.type = line.substr(0, pos1);
        t.amount = std::stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        t.description = line.substr(pos2 + 1, pos3 - pos2 - 1);
        t.date = line.substr(pos3 + 1);

        transactions.push_back(t);
    }
}
