#pragma once
#include "../user/UserSession.h"

using namespace std;

class AdminSession : public UserSession{
public:
    AdminSession(User& user, std::vector<Item>& items, std::vector<Transaction>& allTransactions, std::vector<Admin>& admins);
    void run() override;
private:
    void showMenu() override;
    void listItemandSetPrice();
    void checkTransactionStatus();
};


