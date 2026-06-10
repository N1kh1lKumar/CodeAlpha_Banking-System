#include "../include/BankSystem.h"

#include <iomanip>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

void saveTransaction(int accountNumber, string type, double amount)
{
    static int transactionId = 1;

    ofstream file( "data/transactions.txt", ios::app );

    file << transactionId++ << "," << accountNumber << "," << type << "," << amount << endl;

    file.close();
}


// Check if Customer Exists
bool BankSystem::customerExists(int customerId)
{
    ifstream file("data/customers.txt");

    if(!file)
        return false;

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string id;

        getline(ss, id, ',');

        try
        {
            if(stoi(id) == customerId)
            {
                file.close();
                return true;
            }
        }
        catch(...)
        {
            cout << "Skipping corrupted customer record: "
                 << line << endl;
        }
    }

    file.close();
    return false;
}


// Check if Account Exists
bool BankSystem::accountExists(int accountNumber)
{
    ifstream file("data/accounts.txt");

    if(!file)
        return false;

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo;

        getline(ss, accNo, ',');

        try
        {
            if(stoi(accNo) == accountNumber)
            {
                file.close();
                return true;
            }
        }
        catch(...)
        {
            cout << "Skipping corrupted account record: "
                 << line << endl;
        }
    }

    file.close();
    return false;
}


// Generate Unique Customer ID
int BankSystem::generateCustomerId()
{
    ifstream file("data/customers.txt");

    string line;

    int lastId = 1000;

    while(getline(file, line))
    {
        stringstream ss(line);

        string id;

        getline(ss, id, ',');

        try
        {
            lastId = stoi(id);
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();

    return lastId + 1;
}


// Generate Unique Account Number
int BankSystem::generateAccountNumber()
{
    ifstream file("data/accounts.txt");

    string line;

    int lastAccount = 5000;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo;

        getline(ss, accNo, ',');

        try
        {
            lastAccount = stoi(accNo);
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();

    return lastAccount + 1;
}


// Create Customer
void BankSystem::createCustomer()
{
    Customer customer;

    int customerId = generateCustomerId();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    customer.inputCustomer();   // Name + Phone only

    ofstream file("data/customers.txt", ios::app);

    file << customerId << ","  << customer.getName() << ","  << customer.getPhoneNumber() << "," << customer.getPin() << endl;

    file.close();

    cout << "\nCustomer Created Successfully!\n";
    cout << "Generated Customer ID: "  << customerId << endl;
}

// Create Account
void BankSystem::createAccount()
{
    Account account;

    account.inputAccount();

    if(!customerExists(account.getCustomerId()))
    {
        cout << "\nCustomer ID does not exist!\n";
        return;
    }

    int accountNumber = generateAccountNumber();

    account.setAccountNumber(accountNumber);

    ofstream file("data/accounts.txt", ios::app);

    file << account.getAccountNumber() << ","  << account.getCustomerId() << ","  << fixed << setprecision(2)  << account.getBalance()  << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
    cout << "Generated Account Number: "   << accountNumber << endl;

}




//Deposit Money
void BankSystem::depositMoney()
{
    int accountNumber;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    if(!accountExists(accountNumber))
    {
        cout << "\nAccount Not Found!\n";
        return;
    }

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    if(amount <= 0)
    {
        cout << "\nInvalid Amount!\n";
        return;
    }

    ifstream file("data/accounts.txt");
    ofstream temp("data/temp.txt");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo, custId, balance;

        getline(ss, accNo, ',');
        getline(ss, custId, ',');
        getline(ss, balance);

        if(balance.empty())
        {
            continue;
        }

        double currentBalance = stod(balance);

        if(stoi(accNo) == accountNumber)
        {
            currentBalance += amount;
        }

        temp << accNo << ","
             << custId << ","
             << fixed << setprecision(2)
             << currentBalance
             << endl;
    }

    file.close();
    temp.close();

    remove("data/accounts.txt");
    rename("data/temp.txt", "data/accounts.txt");

    saveTransaction( accountNumber, "Deposit", amount);

    cout << "\nDeposit Successful!\n";
}


//withdraw Money
void BankSystem::withdrawMoney()
{

    int customerId;
    int pin;

    cout << "\nCustomer ID: ";
    cin >> customerId;

    cout << "PIN: ";
    cin >> pin;

    if(!authenticateCustomer(customerId, pin))
    {
        cout << "\nAuthentication Failed!\n";
        return;
    }

    int accountNumber;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    if(!accountExists(accountNumber))
    {
        cout << "\nAccount Not Found!\n";
        return;
    }

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    if(amount <= 0)
    {
        cout << "\nInvalid Amount!\n";
        return;
    }

    ifstream file("data/accounts.txt");
    ofstream temp("data/temp.txt");

    string line;

    bool success = false;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo, custId, balance;

        getline(ss, accNo, ',');
        getline(ss, custId, ',');
        getline(ss, balance);
        if(balance.empty())
        {
            continue;
        }
        double currentBalance = stod(balance);

        if(stoi(accNo) == accountNumber)
        {
            if(currentBalance >= amount)
            {
                currentBalance -= amount;
                success = true;
            }
        }

        temp << accNo << ","
             << custId << ","
             << fixed << setprecision(2)
             << currentBalance
             << endl;
    }

    file.close();
    temp.close();

    remove("data/accounts.txt");
    rename("data/temp.txt",  "data/accounts.txt");

    if(success){ 
        saveTransaction( accountNumber, "Withdrawal", amount);
        cout << "\nWithdrawal Successful!\n";
    }
    else
        cout << "\nInsufficient Balance!\n";
}


//view Account

void BankSystem::viewAccount()
{
    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    ifstream file("data/accounts.txt");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo, custId, balance;

        getline(ss, accNo, ',');
        getline(ss, custId, ',');
        getline(ss, balance);

        if(stoi(accNo) == accountNumber)
        {
            cout << "\n=============================\n";
            cout << "ACCOUNT DETAILS\n";
            cout << "=============================\n";

            cout << "Account Number : "
                 << accNo
                 << endl;

            cout << "Customer ID    : "
                 << custId
                 << endl;

            cout << "Balance        : "
                 << balance
                 << endl;

            file.close();
            return;
        }
    }

    file.close();

    cout << "\nAccount Not Found!\n";
}



//Transfer Money
void BankSystem::transferMoney()
{
    int customerId;
    int pin;

    cout << "\nCustomer ID: ";
    cin >> customerId;

    cout << "PIN: ";
    cin >> pin;

    if(!authenticateCustomer(customerId, pin))
    {
        cout << "\nAuthentication Failed!\n";
        return;
    }

    int fromAccount;
    int toAccount;
    double amount;

    cout << "\nFrom Account: ";
    cin >> fromAccount;

    cout << "To Account: ";
    cin >> toAccount;

    if(!accountExists(fromAccount) ||!accountExists(toAccount))
    {
        cout << "\nOne or both accounts not found!\n";
        return;
    }

    if(!accountBelongsToCustomer(fromAccount, customerId))
    {
        cout << "\nThis account does not belong to you!\n";
        return;
    }

    cout << "Amount: ";
    cin >> amount;

    if(amount <= 0)
    {
        cout << "\nInvalid Amount!\n";
        return;
    }

    ifstream file("data/accounts.txt");
    ofstream temp("data/temp.txt");

    string line;

    bool transferSuccess = false;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo, custId, balance;

        getline(ss, accNo, ',');
        getline(ss, custId, ',');
        getline(ss, balance);

        double currentBalance = stod(balance);

        if(stoi(accNo) == fromAccount)
        {
            if(currentBalance >= amount)
            {
                currentBalance -= amount;
                transferSuccess = true;
            }
        }

        temp << accNo << "," << custId << "," << fixed << setprecision(2) << currentBalance << endl;
    }

    file.close();
    temp.close();

    remove("data/accounts.txt");
    rename("data/temp.txt","data/accounts.txt");

    if(!transferSuccess)
    {
        cout << "\nInsufficient Balance!\n";
        return;
    }

    ifstream file2("data/accounts.txt");
    ofstream temp2("data/temp.txt");

    while(getline(file2, line))
    {
        stringstream ss(line);

        string accNo, custId, balance;

        getline(ss, accNo, ',');
        getline(ss, custId, ',');
        getline(ss, balance);

        double currentBalance = stod(balance);

        if(stoi(accNo) == toAccount)
        {
            currentBalance += amount;
        }

        temp2 << accNo << "," << custId << "," << fixed << setprecision(2) << currentBalance << endl;
    }

    file2.close();
    temp2.close();

    remove("data/accounts.txt");
    rename("data/temp.txt", "data/accounts.txt");

    saveTransaction(fromAccount, "Transfer To " + to_string(toAccount), amount);

    cout << "\nTransfer Successful!\n";
}


//view Transactions
void BankSystem::viewTransactions()
{
    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    ifstream file("data/transactions.txt");

    if(!file)
    {
        cout << "\nNo Transactions Found!\n";
        return;
    }

    string line;

    bool found = false;

    cout << "-------------  ACCOUNT STATEMENT  --------------------\n";

    cout << left << setw(10) << "ID" << setw(15) << "Account" << setw(25) << "Type" << setw(20) << "Amount" << endl;

    cout << "------------------------------------------------------\n";

    while(getline(file, line))
    {
        stringstream ss(line);

        string id, accNo, type, amount;

        getline(ss, id, ',');
        getline(ss, accNo, ',');
        getline(ss, type, ',');
        getline(ss, amount);

        try
        {
            if(stoi(accNo) == accountNumber)
            {
                found = true;

                cout << left << setw(10) << id << setw(15) << accNo << setw(25) << type << setw(20) << amount << endl;
            }
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nNo Transactions Found For This Account!\n";
    }
}

// Check if Account Belongs to Customer
bool BankSystem::accountBelongsToCustomer(int accountNumber, int customerId)
{
    ifstream file("data/accounts.txt");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string accNo, custId, balance;

        getline(ss, accNo, ',');
        getline(ss, custId, ',');
        getline(ss, balance);

        try
        {
            if(stoi(accNo) == accountNumber &&
               stoi(custId) == customerId)
            {
                return true;
            }
        }
        catch(...)
        {
            continue;
        }
    }

    return false;
}


// Authenticate Customer
bool BankSystem::authenticateCustomer( int customerId, int pin)
{
    ifstream file("data/customers.txt");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string id, name, phone, storedPin;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, storedPin);

        try
        {
            if(stoi(id) == customerId &&
               stoi(storedPin) == pin)
            {
                return true;
            }
        }
        catch(...)
        {
            continue;
        }
    }

    return false;
}