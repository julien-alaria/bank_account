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
    return account;
}

void free_account(struct Account *account) {
    if (account != NULL) {
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

