#pragma once
#include "../Structure.h"
#include <vector>
#include <string>

using namespace std;

class AplikasiToko {
public:
    AplikasiToko(const string& userFile, const string& itemFile, const string& transactionFile);
    void jalankan();

private:
    vector<User> daftarPengguna;
    vector<Item> daftarItem;
    vector<Transaction> daftarTransaksi;
    vector<Admin> daftarAdmin;
    

    string filePengguna;
    string fileItem;
    string fileTransaksi;
    
    int nextUserId = 1;


    void muatSemuaData();
    void simpanSemuaData();
    void registrasi();
    void login();
    void tampilkanMenuUtama();
};