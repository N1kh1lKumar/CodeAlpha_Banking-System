#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
private:
    int accountNumber;
    int customerId;
    double balance;

public:
    Account();

    void inputAccount();

    void deposit(double amount);

    bool withdraw(double amount);

    int getAccountNumber() const;
    int getCustomerId() const;
    double getBalance() const;


    void setAccountNumber(int accNo);
};

#endif