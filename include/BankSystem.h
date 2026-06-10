#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Customer.h"
#include "Account.h"
#include "Transaction.h"

class BankSystem
{
public:
    void createCustomer();

    int generateCustomerId();

    int generateAccountNumber();

    void createAccount();

    void depositMoney();

    void withdrawMoney();

    void viewAccount();

    void transferMoney();

    void viewTransactions();

    bool customerExists(int customerId);

    bool accountExists(int accountNumber);

    bool authenticateCustomer(int customerId, int pin);

    bool accountBelongsToCustomer(int accountNumber, int customerId);

};

#endif