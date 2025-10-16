#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account{
private:
       int*accountID;
       string customerName;
       float balance;
public:
      Account();
     ~Account();
      Account(const Account& other);
      Account& operator=(const Account& other);

      //muttators
      void SetAccountID(int id);
      void SetCustomerName(const string& name);
      void SetBalance(float amount);

      //accessors
     int GetAccountID()const;
     string GetCustomerName()const;
     float GetBalance()const;

     //Operations
     void deposit(float amount);
     bool withdraw(float amount);
     Account& operator+=(Account& src);


};

#endif
