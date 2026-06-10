#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
private:
    int customerId;
    std::string name;
    std::string phoneNumber;
    int pin;

public:
    Customer();

    void inputCustomer();

    int getCustomerId() const;
    int getPin() const;
    std::string getName() const;
    std::string getPhoneNumber() const;

    void setPin(int p);
};

#endif