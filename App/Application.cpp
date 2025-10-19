#include "Application.h"
#include "../user/UserSession.h"
#include "../admin/AdminSession.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <memory> 
#include <algorithm>
#include <iostream>

using namespace std;


AplikasiToko::AplikasiToko(const string& userFile, const string& itemFile, const string& transactionFile)
    : filePengguna(userFile), fileItem(itemFile), fileTransaksi(transactionFile) {
    muatSemuaData();
}

void AplikasiToko::jalankan() {
    int pilihan;
    do {
        tampilkanMenuUtama();
        cin >> pilihan;
        while (cin.fail()) {
            cout << "Input invalid. please using number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> pilihan;
            }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (pilihan) {
            case 1: registrasi(); break;
            case 2: login(); break;
            case 3: break;
            default: cout << "invalid choice!\n"; break;
        }
    } while (pilihan != 3);
    simpanSemuaData();
    cout << "Application Close.\n";
}

void AplikasiToko::login() {
    string username, password;
    cout << "\n------ Login ------\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    for (auto& user : daftarPengguna) {
        if (user.username == username && user.password == password) {
            cout << "Login Success! Wellcome, " << user.username << ".\n";
            
            unique_ptr<UserSession> session; 
            if (user.role == "admin") {
                session = std::make_unique<AdminSession>(user, daftarItem, daftarTransaksi, daftarAdmin);
            } else {
                session = std::make_unique<UserSession>(user, daftarItem, daftarTransaksi, daftarAdmin);
            }
            session->run();
            return;
        }
    }
    cout << "Login failed. Username or password wrong.\n";
}

void AplikasiToko::muatSemuaData() {
    // 1. Muat data pengguna dari users.csv
    ifstream userFile(filePengguna);
    if (userFile.is_open()) {
        daftarPengguna.clear();
        string baris;
        int maxId = 0;
        while (getline(userFile, baris)) {
            stringstream ss(baris);
            string idStr, username, password, allowanceStr, role;
            getline(ss, idStr, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, allowanceStr, ',');
            getline(ss, role, ',');
            try {
                int id = stoi(idStr);
                daftarPengguna.push_back({id, username, password, stod(allowanceStr), role});
                if (id > maxId) maxId = id; 
            } catch (const exception&) {}
        }
        nextUserId = maxId + 1; 
        userFile.close();
    }

    // 2. Muat data item dari items.csv
    ifstream itemFile(fileItem);
    if (itemFile.is_open()) {
        daftarItem.clear();
        string baris;
        while (getline(itemFile, baris)) {
            stringstream ss(baris);
            string idStr, name, priceStr;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, priceStr, ',');
            try {
                daftarItem.push_back({stoi(idStr), name, stod(priceStr)});
            } catch (const exception&) {}
        }
        itemFile.close();
    }

    // 3. Muat data transaksi dari transactions.csv
    ifstream transFile(fileTransaksi);
    if (transFile.is_open()) {
        daftarTransaksi.clear();
        string baris;
        while (getline(transFile, baris)) {
            stringstream ss(baris);
            string transIdStr, itemIdStr, userIdStr, status;
            getline(ss, transIdStr, ',');
            getline(ss, itemIdStr, ',');
            getline(ss, userIdStr, ',');
            getline(ss, status, ',');
            try {
                daftarTransaksi.push_back({stoi(transIdStr), stoi(itemIdStr), stoi(userIdStr), status});
            } catch (const exception&) {}
        }
        transFile.close();
    }
}

void AplikasiToko::simpanSemuaData() {
    // 1. Simpan data pengguna ke users.csv
    ofstream userFile(filePengguna);
    for (const auto& user : daftarPengguna) {
        userFile << user.id << "," << user.username << "," << user.password 
        << "," << user.allowance << "," << user.role << endl;
    }
    userFile.close();

    // 2. Simpan data item ke items.csv
    ofstream itemFile(fileItem);
    for (const auto& item : daftarItem) {
        itemFile << item.id << "," << item.name << "," << item.price << endl;
    }
    itemFile.close();

    // 3. Simpan data transaksi ke transactions.csv
    ofstream transFile(fileTransaksi);
    for (const auto& t : daftarTransaksi) {
        transFile << t.transactionId << "," << t.itemId << "," << t.userId << "," << t.status << endl;
    }
    transFile.close();
}

void AplikasiToko::registrasi() {
    User penggunaBaru;
    cout << "\n------ Registration Account ------\n";
    cout << "inset username: ";
    getline(cin, penggunaBaru.username);


    for(const auto& user : daftarPengguna) {
        if (user.username == penggunaBaru.username) {
            cout << "Username '" << penggunaBaru.username << "' already registerd. try other username.\n";
            return;
        }
    }

    cout << "insert password: ";
    getline(cin, penggunaBaru.password);
    
    // Atur atribut default untuk pengguna baru
    penggunaBaru.id = nextUserId++; // Berikan ID unik, lalu increment counter
    penggunaBaru.allowance = 100000; // Saldo awal default
    penggunaBaru.role = "user"; // Peran default adalah "user"

    daftarPengguna.push_back(penggunaBaru);
    cout << "registration succeed! yuor balance is Rp 100000.\n";
}

void AplikasiToko::tampilkanMenuUtama() {
    cout << "\n---- SELAMAT DATANG ----\n";
    cout << "1. Register New Account\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "-------------------------\n";
}
