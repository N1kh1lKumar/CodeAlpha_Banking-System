#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction
{
private:
    int transactionId;
    int accountNumber;
    std::string type;
    double amount;

public:
    Transaction();

    void setTransaction(
        int tId,
        int accNo,
        std::string tType,
        double amt
    );

    int getTransactionId() const;
    int getAccountNumber() const;
    std::string getType() const;
    double getAmount() const;
};

#endif