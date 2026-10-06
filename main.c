#include <stdio.h>
#include "account.h"

int main(void) {
    struct Account *head = NULL;
    const char *names[3] = {"Alice", "Alexandrine", "Bob"};
    long balances[3] = {1000, 2500, 300};

    for (int i = 0; i < 3; i++) {
        struct Account *a = create_account(i + 1, names[i], balances[i]);
        if (a == NULL) {
            printf("malloc failed\n");
            return 1;
        }
        append_account(&head, a);
    }

    print_accounts(head);

    struct Account *found = find_account(head, 2);
    if (found != NULL) {
        printf("%s\n", found->owner);
    } else {
        printf("Not found\n");
    }

    found = find_account(head, 99);
    if (found != NULL) {
        printf("%s\n", found->owner);
    } else {
        printf("Not found\n");
    }

    struct Account *current = head;
    while (current != NULL) {
        struct Account *next = current->next;
        free_account(current);
        current = next;
    }
    return 0;
}