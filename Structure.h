#pragma once
#include <string>

using namespace std;

struct User{
    int id;
    string username;
    string password;
    double allowance;
    string role;
};

struct Item{
    int id;
    string name;
    double price;
};

struct Transaction
{
    int transactionId;
    int itemId;
    int userId;
    string status; // "paid" "complete" "cancelled"
};

struct Admin {
    int userId;      
    string storeName;
    string email;
    string phone;
};
