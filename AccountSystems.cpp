#include "AccountSystems.h"
#include "Account.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

static inline void money() { cout << fixed << setprecision(2); }
static inline void clearBad() { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

AccountSystems::AccountSystems() {}

void AccountSystems::addAccount() {
    int id; string name; float initial;

    cout << "Enter account id: ";
    if (!(cin >> id)) { clearBad(); cout << "\n"; return; }
    clearBad();

    cout << "Enter customer account name: ";
    getline(cin, name);

    cout << "Enter initial deposit amount: $ ";
    if (!(cin >> initial)) { clearBad(); cout << "\n"; return; }

    if (accts.find(id) != -1) {
        cout << "Error: account with id " << id << " already exists.\n\n";
        return;
    }

    Account a;
    a.SetAccountID(id);
    a.SetCustomerName(name);
    a.SetBalance(initial);

    if (!accts.add(a)) {
        cout << "Error: Unable to add account.\n\n";
        return;
    }

    money();
    cout << "Added new account id " << a.GetAccountID()
         << " with initial balance $" << a.GetBalance() << "\n\n";
}

void AccountSystems::deposit() {
    if (accts.size() == 0) { cout << "Empty account list.\n\n"; return; }

    int id; float amount;
    cout << "Enter account id: ";
    if (!(cin >> id)) { clearBad(); cout << "\n"; return; }

    int idx = accts.find(id);
    if (idx == -1) {
        cout << "Error: account with id " << id << " not found.\n\n";
        return;
    }

    cout << "Enter the deposit amount: $ ";
    if (!(cin >> amount)) { clearBad(); cout << "\n"; return; }

    Account& acc = accts.at(idx);
    acc.deposit(amount);

    money();
    cout << "Deposited $" << amount << " into account id " << acc.GetAccountID() << "\n\n";
}

void AccountSystems::withdraw() {
    if (accts.size() == 0) { cout << "Empty account list.\n\n"; return; }

    int id; float amount;
    cout << "Enter account id: ";
    if (!(cin >> id)) { clearBad(); cout << "\n"; return; }

    int idx = accts.find(id);
    if (idx == -1) {
        cout << "Error: account with id " << id << " not found.\n\n";
        return;
    }

    cout << "Enter the withdraw amount: $ ";
    if (!(cin >> amount)) { clearBad(); cout << "\n"; return; }

    Account& acc = accts.at(idx);
    money();
    if (!acc.withdraw(amount)) {
        cout << "Error: failed to withdraw $" << amount << " from account id " << acc.GetAccountID() << "\n\n";
        return;
    }

    cout << "Withdrawn $" << amount << " from account id " << acc.GetAccountID() << "\n\n";
}

void AccountSystems::transfer() {
    if (accts.size() == 0) { cout << "Empty account list.\n\n"; return; }

    int srcId, dstId; float amount;
    cout << "Enter source account id: ";
    if (!(cin >> srcId)) { clearBad(); cout << "\n"; return; }
    cout << "Enter destination account id: ";
    if (!(cin >> dstId)) { clearBad(); cout << "\n"; return; }

    int si = accts.find(srcId);
    int di = accts.find(dstId);
    if (si == -1 || di == -1) {
        cout << "Error: Source or destination account number not found. Operation \n";
        cout << "failed.\n\n";
        return;
    }

    cout << "Enter the transfer amount: $ ";
    if (!(cin >> amount)) { clearBad(); cout << "\n"; return; }

    Account& src = accts.at(si);
    Account& dst = accts.at(di);
    money();
    if (src.GetBalance() < amount) {
        cout << "Error: Insufficient balance. Source account has only $"
             << src.GetBalance() << " in the balance.\n\n";
        return;
    }

    src.withdraw(amount);
    dst.deposit(amount);

    cout << "Successfully transferred amount $" << amount
         << " from source account id " << src.GetAccountID() << "\n";
    cout << "to destination account id " << dst.GetAccountID() << "\n\n";
}

static inline void printLine() {
    cout << "+--------------------------------------------------------+\n";
}

void AccountSystems::printAll() const {
    if (accts.size() == 0) { cout << "Empty account list.\n\n"; return; }

    printLine();
    cout << "| Acct | Customer Account Name          | Balance        |\n";
    printLine();

    for (int i = 0; i < accts.size(); ++i) {
        const Account& acc = accts.at(i);
        cout << "| " << setw(4) << acc.GetAccountID() << " | "
             << left << setw(30) << acc.GetCustomerName().substr(0, 30)
             << right << " | $ " << setw(12) << fixed << setprecision(2) << acc.GetBalance() << " |\n";
        printLine();
    }
    cout << "\n";
}
