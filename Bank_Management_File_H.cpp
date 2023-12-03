#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

class Account {
private:
    string accountNo;
    string password;
    int balance;

public:
    Account() : accountNo(""), password(""), balance(0) {}

    // Setter methods
    void setAccountNo(string id) {
        accountNo = id;
    }

    void setPassword(string pw) {
        password = pw;
    }

    void setBalance(int newBalance) {
        balance = newBalance;
    }

    // Getter methods
    string getAccountNo() const {
        return accountNo;
    }

    string getPassword() const {
        return password;
    }

    int getBalance() const {
        return balance;
    }
};

// Function to open a new account
void openAccount(Account& user) {
    system("cls");
    string id, pw;

    cout << "\tEnter Account No: ";
    cin >> id;
    user.setAccountNo(id);

    cout << "\tEnter A Strong Password: ";
    cin >> pw;
    user.setPassword(pw);

    user.setBalance(0);

    ofstream outFile("D:/Account.txt", ios::app);

    if (!outFile) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        outFile << "\t" << user.getAccountNo() << " : " << user.getPassword() << " : " << user.getBalance() << endl
                << endl;
        cout << "\tAccount Created Successfully!" << endl;
    }

    outFile.close();
    Sleep(5000);
}

// Function to add cash to an existing account
void addCash() {
    system("cls");
    string id;

    cout << "\tEnter Account No: ";
    cin >> id;

    ifstream inFile("D:/Account.txt");
    ofstream outFile("D:/Account Temp.txt");

    if (!inFile || !outFile) {
        cout << "\tError: File Can't Open!" << endl;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string userID, userPW;
        int userBalance;
        char delimiter;

        ss >> userID >> delimiter >> userPW >> delimiter >> userBalance;

        if (id == userID) {
            found = true;
            int cash;

            cout << "\tEnter Cash: ";
            cin >> cash;

            int newBalance = userBalance + cash;
            userBalance = newBalance;

            outFile << "\t" << userID << " : " << userPW << " : " << userBalance << endl;
            cout << "\tNew Balance Is: " << userBalance << endl;
        } else {
            outFile << line << endl;
        }
    }

    if (!found) {
        cout << "\tEnter Valid Account No!" << endl;
    }

    outFile.close();
    inFile.close();

    remove("D:/Account.txt");
    rename("D:/Account Temp.txt", "D:/Account.txt");
    Sleep(5000);
}

// Function to withdraw cash from an existing account
void withdraw() {
    system("cls");
    string id, pw;

    cout << "\tEnter Account No: ";
    cin >> id;

    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream inFile("D:/Account.txt");
    ofstream outFile("D:/Account Temp.txt");

    if (!inFile || !outFile) {
        cout << "\tError: File Can't Open!" << endl;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string userID, userPW;
        int userBalance;
        char delimiter;

        ss >> userID >> delimiter >> userPW >> delimiter >> userBalance;

        if (id == userID && pw == userPW) {
            found = true;
            int cash;

            cout << "\tEnter Cash: ";
            cin >> cash;

            if (cash <= userBalance) {
                int newBalance = userBalance - cash;
                userBalance = newBalance;

                outFile << "\t" << userID << " : " << userPW << " : " << userBalance << endl;
                cout << "\tTransaction Was Successful!" << endl;
                cout << "\tRemaining Balance: " << userBalance << endl;
            } else {
                cout << "\tLow Balance!" << endl;
                outFile << "\t" << userID << " : " << userPW << " : " << userBalance << endl;
            }
        } else {
            outFile << line << endl;
        }
    }

    if (!found) {
        cout << "\tInvalid Account No or Password!" << endl;
    }

    outFile.close();
    inFile.close();

    remove("D:/Account.txt");
    rename("D:/Account Temp.txt", "D:/Account.txt");
    Sleep(5000);
}

// Main menu function
void mainMenu() {
    Account user;

    bool exit = false;

    while (!exit) {
        system("cls");
        int choice;

        cout << "\tWelcome To Bank Account Management System" << endl;
        cout << "\t*****************************************" << endl;
        cout << "\t1. Open New Account." << endl;
        cout << "\t2. Add Cash." << endl;
        cout << "\t3. Withdraw Cash." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                openAccount(user);
                break;
            case 2:
                addCash();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                system("cls");
                exit = true;
                cout << "\tGood Luck!" << endl;
                Sleep(2000);
                break;
            default:
                cout << "\tInvalid Choice. Please try again." << endl;
                Sleep(3000);
        }
    }
}

int main() {
    mainMenu();
    return 0;
}

//Author: AT PM SP