# Banking Management System

A console-based Banking Management System developed in C++ using Object-Oriented Programming (OOP) and File Handling concepts.

The project allows users to create customers and accounts, perform banking operations, maintain transaction records, and securely access features using Customer ID and PIN authentication.

---

# Features

## Customer Management

* Create new customers
* Auto-generate unique Customer IDs
* Mobile number validation
* Secure 4-digit PIN setup


## Account Management

* Create bank accounts
* Auto-generate unique Account Numbers
* Link accounts with customers
* Validate initial account balance

## Banking Operations

* Deposit money
* Withdraw money
* Transfer money between accounts
* View account details
* View transaction history

## Security

* Customer authentication using Customer ID and PIN
* Authentication required before withdrawals
* Authentication required before money transfers
* Account ownership verification during transactions

## Transaction Tracking

* Record deposits
* Record withdrawals
* Record transfers
* Maintain transaction history in a separate file



## Data Persistence

All records are stored using text files:

* customers.txt
* accounts.txt
* transactions.txt

Data remains available after the application is closed.

---

# Technologies Used

* C++
* Object-Oriented Programming (OOP)
* File Handling
* Standard Template Library (STL)

---

# Project Structure

```text
Banking System/
│
├── include/
│   ├── Customer.h
│   ├── Account.h
│   ├── Transaction.h
│   └── BankSystem.h
│
├── src/
│   ├── Customer.cpp
│   ├── Account.cpp
│   ├── Transaction.cpp
│   ├── BankSystem.cpp
│   └── main.cpp
│
├── data/
│   ├── customers.txt
│   ├── accounts.txt
│   └── transactions.txt
│
└── README.md
```

---

# How to Compile

```bash
g++ src/*.cpp -Iinclude -o bank
```

# How to Run

```bash
./bank
```

---

# Menu Options

```text
1. Create Customer
2. Create Account
3. Deposit Money
4. Withdraw Money
5. View Account
6. Transfer Money
7. View Transactions
8. Exit
```

---

# Concepts Demonstrated

* Classes and Objects
* Encapsulation
* Modular Programming
* File Handling
* Authentication System
* Data Validation
* Banking Transaction Management
* Persistent Data Storage

---


# Author

Nikhil Kumar

C++ programming Project 
