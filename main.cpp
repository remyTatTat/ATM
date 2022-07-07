#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Transaction {
    private:
        string date;
        string type;
        double amount;
    public:
        Transaction(){}
        Transaction(string newDate, string newType, int newAmount) {
            newDate.erase(std::remove(newDate.begin(), newDate.end(), '\n'), newDate.cend());
            date = newDate;
            type = newType;
            amount = newAmount;
        }

        void printTransaction() {
            cout << date << " | " << type << "\t| " << amount << endl;
        }
};

class Account {
    private:
        std::vector<Transaction> transactions; 
        int accountNo;
        string password;
        double balance = 5000;
    public:
        Account(){}
        Account(int accountNoIn, string passwordIn) : accountNo(accountNoIn), password(passwordIn) {

        };

        bool loginCredentialCheck(int accountNoAttempt, string passwordAttempt) {
            if (accountNo == accountNoAttempt &&
                password == passwordAttempt) {
                return true;
            } else {
                return false;
            }
        }

        void showBalance() {
            cout << "Main Window -> Show Balance" << endl;
            cout << "=================================================" << endl;
            cout << "Your current balance is: $" << balance << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "Press enter to go back to the main window." << endl;
            cin.ignore(); cin.ignore();
        }

        void desposit() {
            double depositAmount;
            bool validDeposit = false;

            cout << "Main Window -> Deposit (Enter the following information)"<<endl;
            cout << "=================================================" << endl;
            while (!validDeposit) {
                cout << "The amount you want to deposit: ";
                cin >> depositAmount;
                cout << "-------------------------------------------------" << endl;
                if (depositAmount <= 0) {
                    cout << "Invalid deposit amount. Please try again." << endl;
                    validDeposit = false;
                } else {
                    time_t now = time(0);
                    string dt = ctime(&now);
                    Transaction transaction(dt, "deposit", depositAmount);
                    transactions.push_back(transaction);
                    balance += depositAmount;
                    cout << "Well done. This was added to your balance successfully....\nPress enter to go back to the main window." << endl;
                    validDeposit = true;
                }
            } cin.ignore(); cin.ignore();
        }

        void withdraw() {
            double withdrawAmount;
            bool validWithdraw = false;
            cout << "Main Window -> Deposit (Enter the following information)"<<endl;
            cout << "=================================================" << endl;
            while (!validWithdraw) {
                cout << "The amount you want to withdraw: ";
                cin >> withdrawAmount;
                cout << "-------------------------------------------------" << endl;
                if (withdrawAmount <= 0) {
                    cout << "Invalid withdraw amount. Please try again." << endl;
                    validWithdraw = false;
                } else if (withdrawAmount > balance) {
                    cout << "Withdraw amount exceeds balance. Please enter a new amount." << endl;
                    validWithdraw = false;
                } else {
                    time_t now = time(0);
                    string dt = ctime(&now);
                    Transaction transaction(dt, "withdraw", withdrawAmount);
                    transactions.push_back(transaction);
                    balance -= withdrawAmount;
                    cout << "Please take your money then....\nPress enter to go back to the main window." << endl;
                    validWithdraw = true;
                }
            } cin.ignore(); cin.ignore();
        }

        void showAllTransactions() {
            cout << "Main Window -> Show All Transactions"<<endl;
            cout << "=================================================" << endl;
            cout << "Account No: " << accountNo << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "Date \t\t\t | Type \t | Amount" << endl;
            cout << "-------------------------------------------------" << endl;
            for (int i = 0; i < transactions.size(); i++) {
                transactions[i].printTransaction();
            }
            cout << "-------------------------------------------------" << endl;
            cout << "Press enter to go back to the main window." << endl;
            cin.ignore(); cin.ignore();
        }

};

void mainMenu(Account account) {
    int userChoice;
    cout << "Main Window" << endl;
    cout << "==============================" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "(1) Show Balance" << endl;
    cout << "(2) Deposit" << endl;
    cout << "(3) Withdraw" << endl;
    cout << "(4) Show all transactions" << endl;
    cout << "(5) Exit" << endl;
    cout << "Enter your choice: ";
    cin >> userChoice;

    switch (userChoice)
    {
    case 1:
        account.showBalance();
        mainMenu(account);
        break;
    
    case 2:
        account.desposit();
        mainMenu(account);
        break;

    case 3:
        account.withdraw();
        mainMenu(account);
        break;

    case 4:
        account.showAllTransactions();
        mainMenu(account);
        break;
    
    case 5:
        break;
    
    default:
        cout << "Invalid input. Please try again." << endl;
        mainMenu(account);
        break;
    }
}

Account loginMenu(Account accounts[]) {
    int accountNum;
    string password;
    bool validAccountNo = false;

    cout << "Login Window: " << endl;
    cout << "==============================" << endl;
    cout << "Enter your Account #: ";
    cin >> accountNum;
    while (cin.fail()) {
        cout << "Invlaid Account No, please try again: " << endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> accountNum;
    }
    cout << "Enter your password: ";
    cin >> password;

    for (int i = 0; i < 10; i++) {
        // cout << "user: " << accountNum << "| pass: " << password << endl;
        // cout << "user: " << accounts[i].accountNo << "| pass: " << accounts[i].password << endl;
        if (accounts[i].loginCredentialCheck(accountNum, password)) {
            cout << "\n" << endl;
            return accounts[i];
        }
    }
    cout << "Incorrect Username and Passowrd combination, please try again.\n" << endl;
    loginMenu(accounts);
}

int main() {

    Account accounts[10] = {Account(1, "eins"), Account(2, "zwei"), Account(3, "drei"), Account(4, "vier"), Account(5, "funf"), Account(6, "sechs"), Account(7, "sieben"), Account(8, "acht"), Account(9, "neun"), Account(0, "zehn")};

    mainMenu(loginMenu(accounts));

    return 0;
}