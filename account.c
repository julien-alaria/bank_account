#include <stdlib.h>
#include <string.h>
#include "account.h"

struct Account *create_account(int number, const char *owner, long initial_balance) {
    struct Account *account = malloc(sizeof(struct Account));
    if (account == NULL) {
        return NULL;
    }

    account->owner = malloc(sizeof(owner) +1);
    if (account->owner == NULL) {
        free(owner);
        return NULL;
    }

    strcpy(account->owner, owner);
    account->number = number;
    account->next = account->next;
    return account->next;
}

void free_account(struct Account *account) {
    if (account != NULL) {
        free(account->owner);
        free(account);
    }
}
