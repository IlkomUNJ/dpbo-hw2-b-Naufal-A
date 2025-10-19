#include "AdminSession.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

AdminSession::AdminSession(User& user, vector<Item>& items, vector<Transaction>& allTransactions, vector<Admin>& admins)
    : UserSession(user, items, allTransactions, admins) {}
    
void AdminSession::run() {
    int choice;
    do{
        showMenu();
        cin >> choice;
        while (cin.fail()){
            cout << "Input invalid. please using number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1: browseStore(); break;
            case 2: buyItem(); break;
            case 3: bankingFunction(); break;
            case 4: listItemandSetPrice(); break;
            case 5: checkTransactionStatus(); break;
            case 6: cout << "Logging out..." << endl; break; 
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
    }while (choice != 6);
}

void AdminSession::showMenu() {
    cout 
    << "\n----- Admin Menu -----\n"
    << "1. Browse Store\n"
    << "2. Buy Item\n"
    << "3. Banking functions\n"
    << "4. Manage Store Items\n"
    << "5. Check Transaction\n"
    << "6. Logout\n"
    << "-----------------------\n";
}

void AdminSession::listItemandSetPrice() {
    cout << "------ Manage Store Items ------\n";
    string name;
    double price;
    cout << "Masukkan nama item baru: ";
    getline(cin, name);
    cout << "Masukkan harga item: ";
    cin >> price;

    int nextItemId = storeItems.empty() ? 1 : storeItems.back().id + 1;
    storeItems.push_back({nextItemId, name, price});
    cout << "Item '" << name << "' berhasil ditambahkan.\n";
}

void AdminSession::checkTransactionStatus() {
    cout << "\n--- Semua Transaksi Pengguna ---\n";
    if (transactions.empty()) {
        cout << "Belum ada transaksi.\n";
        return;
    }
    for (const auto& t : transactions) {
        cout << "ID Trans: " << t.transactionId 
                  << " | ID Item: " << t.itemId
                  << " | ID User: " << t.userId
                  << " | Status: " << t.status <<endl;
    }
}