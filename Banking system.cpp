#include <iostream>
#include <string>

using namespace std;

class Account {
private:
    int acno;
    string name;
    double balance;

public:
    Account() : acno(0), name(""), balance(0.0) {}  // Default constructor

    Account(int accountNumber, const string& accountHolder, double initialBalance)
        : acno(accountNumber), name(accountHolder), balance(initialBalance) {}

    int getAccountNumber() const {
        return acno;
    }

    string getAccountHolder() const {
        return name;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient balance." << endl;
    }

    void displayAccount() const {
        cout << "Account Number: " << acno << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs" << balance << endl;
    }
};

class Bank {
private:
    Account* accounts;
    int capacity;
    int size;
    int accountNumberCounter;

public:
    Bank() : accounts(nullptr), capacity(0), size(0), accountNumberCounter(1) {}

    ~Bank() {
        delete[] accounts;
    }

    void createAccount() {
        int accountNumber;
        string accountHolder;
        double initialBalance;

        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, accountHolder);

        cout << "Enter initial balance: Rs";
        cin >> initialBalance;

        accountNumber = accountNumberCounter++;
        Account* newAccount = new Account(accountNumber, accountHolder, initialBalance);
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            Account* temp = new Account[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = accounts[i];
            }
            delete[] accounts;
            accounts = temp;
        }
        accounts[size++] = *newAccount;

        cout << "Account created with account number: " << accountNumber << endl;
    }

    void depositAmount(int accountNumber) {
        double amount;
        cout << "Enter amount to deposit: Rs";
        cin >> amount;

        Account* account = findAccount(accountNumber);
        if (account)
            account->deposit(amount);
        else
            cout << "Account not found." << endl;
    }

    void withdrawAmount(int accountNumber) {
        double amount;
        cout << "Enter amount to withdraw: Rs";
        cin >> amount;

        Account* account = findAccount(accountNumber);
        if (account)
            account->withdraw(amount);
        else
            cout << "Account not found." << endl;
    }

    void displayAccountDetails(int accountNumber) {
        Account* account = findAccount(accountNumber);
        if (account)
            account->displayAccount();
        else
            cout << "Account not found." << endl;
    }

private:
    Account* findAccount(int accountNumber) {
        for (int i = 0; i < size; i++) {
            if (accounts[i].getAccountNumber() == accountNumber)
                return &accounts[i];
        }
        return nullptr;
    }
};

int main() {
    Bank bank;
    int choice, accountNumber;

    do {
        cout << "\nMAIN MENU\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Amount\n";
        cout << "3. Withdraw Amount\n";
        cout << "4. Display Account Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.depositAmount(accountNumber);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.withdrawAmount(accountNumber);
                break;
            case 4:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.displayAccountDetails(accountNumber);
                break;
            case 5:
                cout << "Thank you for using the bank management system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
