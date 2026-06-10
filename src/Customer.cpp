#include "../include/Customer.h"

#include <iostream>
#include <limits>

using namespace std;

// Constructor
Customer::Customer()
{
    customerId = 0;
    name = "";
    phoneNumber = "";
    pin = 0;
}

// Input Customer Details
void Customer::inputCustomer()
{
    cout << "Enter Customer Name: ";
    getline(cin, name);

    while(true)
    {
        
    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);

    bool valid = true;

    if(phoneNumber.length() != 10)
    {
        valid = false;
    }
    else if(phoneNumber[0] < '6' || phoneNumber[0] > '9')
    {
        valid = false;
    }

    for(char ch : phoneNumber)
    {
        if(!isdigit(ch))
        {
            valid = false;
            break;
        }
    }

    if(valid)
        break;

    cout << "Invalid Phone Number! "
         << "Enter exactly 10 digits.\n";
}


do
{
    cout << "Set 4-Digit PIN: ";
    cin >> pin;

    if(pin < 1000 || pin > 9999)
    {
        cout << "PIN must be 4 digits!\n";
    }

} while(pin < 1000 || pin > 9999);
}

// Get Customer ID
int Customer::getCustomerId() const
{
    return customerId;
}

// Get Customer Name
string Customer::getName() const
{
    return name;
}

// Get Phone Number
string Customer::getPhoneNumber() const
{
    return phoneNumber;
}

// Get PIN
int Customer::getPin() const
{
    return pin;
}