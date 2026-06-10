#include "../include/BankSystem.h"

#include <iostream>

using namespace std;

int main()
{
    BankSystem bank;

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "BANKING MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. View Account\n";
        cout << "6. Transfer Money\n";
        cout << "7. View Transactions\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";

        while(!(cin >> choice))
        {
            cout << "Invalid input! Enter a number: ";

            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch(choice)
        {
            case 1:
                bank.createCustomer();
                break;

            case 2:
                bank.createAccount();
                break;

            case 3:
                bank.depositMoney();
                break;

            case 4:
                bank.withdrawMoney();
                break;

            case 5:
                bank.viewAccount();
                break;

            case 6:
                bank.transferMoney();
                break;

            case 7:
                bank.viewTransactions();
                break;

            case 8:
                cout << "\nExiting System...\n";
                break;
            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 8);

    return 0;
}