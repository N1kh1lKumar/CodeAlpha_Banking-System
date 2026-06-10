#include "../include/Account.h"

#include <iostream>

using namespace std;

// Constructor
Account::Account()
{
    accountNumber = 0;
    customerId = 0;
    balance = 0.0;
}

// Input Account Details
void Account::inputAccount()
{
    cout << "Enter Customer ID: ";
    cin >> customerId;

    do
    {
        cout << "Enter Initial Balance: ";
        cin >> balance;

        if(balance < 0)
        {
            cout << "Balance cannot be negative!\n";
        }

    } while(balance < 0);
}


// Deposit Money
void Account::deposit(double amount)
{
    if(amount <= 0)
    {
         cout << "Invalid deposit amount!\n";
         return;
    }

    balance += amount;
}

// Withdraw Money
bool Account::withdraw(double amount)
{
    if(amount > balance || amount <= 0)
    {
        return false;
    }



    balance -= amount;
    return true;
}

// Getters
int Account::getAccountNumber() const
{
    return accountNumber;
}

int Account::getCustomerId() const
{
    return customerId;
}

double Account::getBalance() const
{
    return balance;
}


// Set Account Number
void Account::setAccountNumber(int accNo)
{
    accountNumber = accNo;
}