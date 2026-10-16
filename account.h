#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Operation {
    char type;
    long amount;
    struct Operation *next;
};

struct Account {
    int number;
    char *owner;
    long balance;
    struct Account *next;
    struct Operation *history;
};

struct Account *create_account(int number, const char *owner, long initial_balance);
void free_account(struct Account *account);
void append_account(struct Account **head, struct Account *new_account);
void print_accounts(const struct Account *head);
struct Account *find_account(struct Account *head, int number);
int deposit(struct Account *account, long amount);
int withdraw(struct Account *account, long amount);
int transfer(struct Account *from, struct Account *to, long amount);
int add_operation(struct Account *account, char type, long amount);
void print_history(const struct Account *account);

#endif