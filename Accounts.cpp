#include "Accounts.h"
#include "Account.h"

Accounts::Accounts() : data(new Account[maxsize]), count(0) {}

Accounts::~Accounts() {
    delete[] data;
    data = nullptr;
    count = 0;
}

int Accounts::size() const {
    return count;
}


bool Accounts::add(Account& acct) {
    if (count >= maxsize) return false;
    int id = acct.GetAccountID();
    for (int i = 0; i < count; ++i) {
        if (data[i].GetAccountID() == id) return false;
    }
    data[count] = acct;
    ++count;
    return true;
}

int Accounts::find(int accountId) const {
    for (int i = 0; i < count; ++i) {
        if (data[i].GetAccountID() == accountId) return i;
    }
    return -1;
}

Account& Accounts::at(const int i) const {
    return data[i];
}
