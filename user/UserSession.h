#pragma once
#include "../Structure.h"
#include <vector>

using namespace std;


class UserSession{
protected:
    User& currentUser;
    vector<Item>& storeItems;
    vector <Transaction>& transactions;
    vector<Admin>& allAdmins;

public:
    UserSession(User& user, vector<Item>& items, vector<Transaction>& allTranscations, vector<Admin>& admins);
    
    virtual ~UserSession() = default;
    virtual void run();
    
protected:
    virtual void showMenu();
    void browseStore();
    void buyItem();
    void bankingFunction();
    void upgradeToAdmin();
};