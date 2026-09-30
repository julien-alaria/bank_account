#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Account {
    int number;
    char *owner;
    long balance;
    struct Account *next;
};

struct Account *create_account(int number, const char *owner, long initial_balance);
void free_account(struct Account *account);

#endif