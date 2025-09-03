#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <string>
#include <vector>

struct Transaction {
    std::string type;     
    double amount;        
    std::string description;
    std::string date;      
};;

class BudgetManager {
private:
    std::vector<Transaction> transactions; 
    std::string filename;                 
    void sortTransactionsByDate();
public:
    BudgetManager(const std::string& file);

    void addIncome(double amount, const std::string& description, const std::string& date);

    void addExpense(double amount, const std::string& description, const std::string& date);

    double getBalance() const;

    void showTransactions();

    void saveToFile() const;

    void loadFromFile();
};

#endif