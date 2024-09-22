#include <iostream>
#include <cmath>  
using namespace std;

class Account {
protected:
    double balance;

public:
    Account(double initialBalance = 0) : balance(initialBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
            return true;
        } else {
            cout << "Invalid or insufficient balance!" << endl;
            return false;
        }
    }

    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public Account {
    static const double minBalance;     
    static const double annualRate;      
    static const int compoundingPeriods; 
    static const double requiredDeposit;  

public:
    SavingsAccount(double initialBalance = 0) : Account(initialBalance) {}

    void deposit(double amount) {
        Account::deposit(amount);
        if (balance >= requiredDeposit && amount > 0) {
            applyInterest();
        }
    }

    bool withdraw(double amount) {
        if (balance - amount < minBalance) {
            cout << "Cannot withdraw! Minimum balance of " << minBalance << " required." << endl;
            return false;
        }
        return Account::withdraw(amount);
    }

    void applyInterest() {
        balance += balance * annualRate; 
        cout << "Interest applied. Current balance: " << balance << endl;
    }
};

const double SavingsAccount::minBalance = 1000.0;
const double SavingsAccount::annualRate = 0.04;  
const int SavingsAccount::compoundingPeriods = 1; 
const double SavingsAccount::requiredDeposit = 200000.0; 

class CurrentAccount : public Account {
public:
    CurrentAccount(double initialBalance = 0) : Account(initialBalance) {}

    bool withdraw(double amount) {
        return Account::withdraw(amount);
    }
};

void savingsMenu(SavingsAccount &savings) {
    int choice;
    double amount;
    bool exitSavings = false;

    while (!exitSavings) {
        cout << "\n--- Savings Account ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Back\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            savings.deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            savings.withdraw(amount);
            break;
        case 3:
            cout << "Current balance: " << savings.getBalance() << endl;
            break;
        case 4:
            exitSavings = true; // Exit the Savings Account menu
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    }
}

void currentMenu(CurrentAccount &current) {
    int choice;
    double amount;
    bool exitCurrent = false;

    while (!exitCurrent) {
        cout << "\n--- Current Account ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Back\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            current.deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            current.withdraw(amount);
            break;
        case 3:
            cout << "Current balance: " << current.getBalance() << endl;
            break;
        case 4:
            exitCurrent = true; 
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    }
}

bool mainMenu(SavingsAccount &savings, CurrentAccount &current) {
    int choice;
    bool exitMain = false;

    while (!exitMain) {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Savings Account\n";
        cout << "2. Current Account\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            savingsMenu(savings); 
            break;
        case 2:
            currentMenu(current); 
            break;
        case 3:
            exitMain = true; 
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    }

    return exitMain;
}

int main() {
    SavingsAccount savings(2000); 
    CurrentAccount current(500);    

    mainMenu(savings, current);     

    return 0;
}
