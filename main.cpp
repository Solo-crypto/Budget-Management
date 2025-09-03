#include "BudgetManager.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getTodayDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now); // safer, thread-safe version
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << 1900 + ltm.tm_year << '-'
        << std::setw(2) << std::setfill('0') << 1 + ltm.tm_mon << '-'
        << std::setw(2) << std::setfill('0') << ltm.tm_mday;
    return oss.str();
}

int main() {
    BudgetManager manager("budget.txt");

    int choice;                         
    do {
        // Menü ausgeben
        std::cout << "\n--- Budgetverwaltung ---\n";
		std::cout << "1. Einnahme hinzufuegen\n";
        std::cout << "2. Ausgabe hinzufuegen\n";
        std::cout << "3. Kontostand anzeigen\n";
        std::cout << "4. Alle Transaktionen anzeigen\n";
        std::cout << "5. Speichern & Beenden\n";
        std::cout << "Bitte waelen";
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            double amount;
            std::string desc, date;

            std::cout << "Betrag eingeben: ";
            std::cin >> amount;
            std::cin.ignore(); 

            std::cout << "Beschreibung eingeben: ";
            getline(std::cin, desc);  

			std::cout << "Datum eingeben (JJJJ-MM-TT) oder Enter fuer heute:";
            getline(std::cin, date); 

            if (date.empty()) {   
                date = getTodayDate();
            }

    
            if (choice == 1)
                manager.addIncome(amount, desc, date);
            else
                manager.addExpense(amount, desc, date);
        }

        else if (choice == 3) {
            std::cout << "Aktueller Kontostand: " << manager.getBalance() << " €\n";
        }
  
        else if (choice == 4) {
            manager.showTransactions();
        }

    } while (choice != 5);

    manager.saveToFile();
    std::cout << "Daten gespeichert. Auf Wiedersehen!\n";
}
