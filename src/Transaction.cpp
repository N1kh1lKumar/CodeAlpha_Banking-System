#include "../include/Transaction.h"

using namespace std;

// Constructor
Transaction::Transaction()
{
    transactionId = 0;
    accountNumber = 0;
    type = "";
    amount = 0.0;
}

// Set Transaction
void Transaction::setTransaction(
    int tId,
    int accNo,
    string tType,
    double amt)
{
    transactionId = tId;
    accountNumber = accNo;
    type = tType;
    amount = amt;
}

// Getters
int Transaction::getTransactionId() const
{
    return transactionId;
}

int Transaction::getAccountNumber() const
{
    return accountNumber;
}

string Transaction::getType() const
{
    return type;
}

double Transaction::getAmount() const
{
    return amount;
}