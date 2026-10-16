#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

struct Account *create_account(int number, const char *owner, long initial_balance) {
    struct Account *account = malloc(sizeof(struct Account));
    if (account == NULL) {
        return NULL;
    }

    account->owner = malloc(strlen(owner) +1);
    if (account->owner == NULL) {
        free(account);
        return NULL;
    }

    strcpy(account->owner, owner);
    account->number = number;
    account->balance = initial_balance;
    account->next = NULL;
    account->history = NULL;
    return account;
}

void free_account(struct Account *account) {
    if (account != NULL) {
        struct Operation *current = account->history;
        while (current != NULL) {
            struct Operation *next = current->next;
            free(current);
            current = next;
        }
        free(account->owner);
        free(account);
    }
}

void append_account(struct Account **head, struct Account *new_account) {
    if (*head == NULL) {
        *head = new_account;
        return;
    }

    struct Account *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_account;
}

struct Account *find_account(struct Account *head, int number) {
    struct Account *current = head;
    while (current != NULL) {
        if (current->number == number) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_accounts(const struct Account *head) {
    const struct Account *current = head;
    while (current != NULL) {
        printf("%d %s %ld\n", current->number, current->owner, current->balance);
        current = current->next;
    }
}

int deposit(struct Account *account, long amount) {
    if (account == NULL || amount <= 0) {
        return -1;
    }
    account->balance += amount;
    return 0;
}

int withdraw(struct Account *account, long amount) {
    if (account == NULL || amount <= 0) {
        return -1;
    }

    if (account->balance < amount) {
        return -1;
    }

    account->balance -= amount;
    return 0;
}

int transfer(struct Account *from, struct Account *to, long amount) {
    if (from == NULL || to == NULL) {
        return -1;
    }

    if (from == to) {
        return -1;
    }

    if (withdraw(from, amount) != 0) {
        return -1;
    }

    if (deposit(to, amount) != 0) {
        deposit(from, amount);
        return -1;
    }
    return 0;
}

int add_operation(struct Account *account, char type, long amount) {
    if (account == NULL) {
        return -1;
    }
    struct Operation *op = malloc(sizeof(struct Operation));
    if (op == NULL) {
        return -1;
    }
    op->type = type;
    op->amount = amount;
    op->next = account->history;
    account->history = op;
    return 0;
}

void print_history(const struct Account *account) {
    if (account == NULL) {
        return;
    }
    const struct Operation *current = account->history;
    while (current != NULL) {
        printf("%c %ld\n", current->type, current->amount);
        current = current->next;
    }
}