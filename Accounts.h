#ifndef ACCOUNTS_H
#define ACCOUNTS_H
 

class Account;

class Accounts{
private:
       static const int maxsize = 1000;
       Account* data;
       int count;

public:

     Accounts();
    ~Accounts();

    bool add(Account& acct);
    int find (int accountId)const;
    Account& at(const int i)const;

   int size()const;



};
#endif 
