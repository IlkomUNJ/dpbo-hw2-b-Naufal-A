#include "userSession.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <string>


using namespace std;

UserSession::UserSession(User& user, vector<Item>& items, vector<Transaction>& allTranscations, vector<Admin>& admins)
    : currentUser(user), storeItems(items), transactions(allTranscations), allAdmins(admins) {}

void UserSession::run() {
    int choice;
    do{
        showMenu();
        cin >> choice;
        while (cin.fail())
        {
        cout << "Input invalid. please using number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1: browseStore(); break;
        case 2: buyItem(); break;
        case 3: bankingFunction(); break;
        case 4: upgradeToAdmin(); choice=5;
        case 5: cout << "Logging out...\n"; break;
        default: cout << "ïnvlaid Choice \n"; break;
        }
    }while (choice !=5);

}

void UserSession::showMenu() {
    cout 
    <<"\n----- User Menu -----\n"
    <<"1. Browse Store\n"
    <<"2. Buy Item\n"
    <<"3. Banking functions\n"
    <<"4. Upgrade to Admin\n"
    <<"5. Logout\n"
    <<"---------------------\n";
}

void UserSession::browseStore() {
    cout << "--------- Store Items ---------\n";
    for (const auto& item : storeItems) {
        cout << "ID: " << item.id 
             << " | Name: " << item.name 
             << " | Price: Rp." << item.price << '\n';
    }cout << "-------------------------------\n";
}


void UserSession::buyItem() {
    browseStore();
    int itemId;
    cout<< " enter the ID of the item you wish to purchase: ";
    cin>> itemId;

    auto it = find_if(storeItems.begin(), storeItems.end(), [itemId](const Item& item){
        return item.id == itemId;
    });

    if (it != storeItems.end()) {
        if (currentUser.allowance >= it->price) {
            currentUser.allowance -= it->price;
            
            int nextTransactionId = transactions.empty() ? 1 : transactions.back().transactionId + 1;
            transactions.push_back({nextTransactionId, it->id, currentUser.id, "PAID"});
            
            cout << "Pembelian '" << it->name << "' berhasil! Saldo tersisa: Rp " << currentUser.allowance << endl;
        } else {
            cout << "Pembelian gagal. Saldo tidak mencukupi.\n";
        }
    } else {
        cout << "Item dengan ID tersebut tidak ditemukan.\n";
    }
}

void UserSession::bankingFunction() {
    int choice;
    do{
    cout 
    <<"\n----- Bank Menu -----\n"
    <<"1. Check balance\n"
    <<"2. Top Up Balnace\n"
    <<"3. Withdraw Money\n"
    <<"4. back\n"
    <<"---------------------\n";
        cin >> choice;
        while (cin.fail())
        {
        cout << "Input invalid. please using number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1: cout << "Your current balance is: Rp " << currentUser.allowance << endl;break;
        case 2:
            double topUpAmount;
            cout << "Enter amount to top up: Rp ";
            cin >> topUpAmount;
            if (topUpAmount>0) {
                currentUser.allowance += topUpAmount; 
                cout << "Top up successful! New balance: Rp " << currentUser.allowance << endl;
            }else{
                cout << "Invalid amount. Top up failed.\n";
            
            }break;
        case 3:
            double withdrawAmount;
            cout<< "Enter amount to withdraw: Rp ";
            cin >> withdrawAmount;
            if (withdrawAmount>0) {
                currentUser.allowance -= withdrawAmount;
                cout<< "Withdrwa successful! New balance: Rp " << currentUser.allowance << endl;
            }else{
                cout << "Invalid amount. your balance is insuficient.\n";

            }break;
        case 4: cout<<"back to main menu \n"; break;
        default: cout << "ïnvlaid Choice \n"; break;
        }  
    }while (choice !=4); 
}

void UserSession::upgradeToAdmin() {
    if (currentUser.role == "admin") {
        cout << "\nYour Account Already A Seller\n";
        return;
    }

    cout << "\n--- Upgrade TO Seller ---\n";
    cout << "Please input the following data to be a seller.\n";
    
    Admin dataAdminBaru;
    dataAdminBaru.userId = currentUser.id; 

    cout << "Enter your store name: ";
    getline(cin, dataAdminBaru.storeName);
    cout << "Enter your Email: ";
    getline(cin, dataAdminBaru.email);
    cout << "Enter your phone number: ";
    getline(cin, dataAdminBaru.phone);

    // 1. Tambahkan data admin baru ke daftar utama
    allAdmins.push_back(dataAdminBaru);
    
    // 2. Ubah peran user saat ini menjadi 'admin'
    currentUser.role = "admin";

    cout << "\nSelamat! Akun Anda telah berhasil di-upgrade menjadi Admin.\n";
    cout << "Peran baru Anda akan aktif pada sesi login berikutnya.\n";
}