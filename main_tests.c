#include <stdio.h>
#include "account.h"

static void test_transfer(struct Account *head, int from, int to, long amount) {
    if (transfer(find_account(head, from), find_account(head, to), amount) == 0) {
        printf("Transfer %d -> %d (%ld): success\n", from, to, amount);
    } else {
        printf("Transfer %d -> %d (%ld): failed\n", from, to, amount);
    }
    print_accounts(head);
}

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

    if (deposit(find_account(head, 1), 500) == 0) {
        printf("Deposit success\n");
    } else {
        printf("Deposit failed\n");
    }

    if (withdraw(find_account(head, 3), 1000) == 0) {
        printf("Withdraw success\n");

    } else {
        printf("Withdraw failed\n");
    }

    if (withdraw(find_account(head, 99), 10) == 0) {
        printf("Withdraw success\n");
    } else {
        printf("Withdraw failed\n");
    }

    if (deposit(find_account(head, 2), -50) == 0) {
        printf("Deposit success\n");
    } else {
        printf("Deposit failed\n");
    }

    test_transfer(head, 1, 3, 500);
    test_transfer(head, 2, 3, 5000);   
    test_transfer(head, 1, 1, 500);   
    test_transfer(head, 1, 99, 500); 

    deposit(find_account(head, 1), 500);
    transfer(find_account(head, 1), find_account(head, 3), 500);
    printf("Compte 1 :\n");
    print_history(find_account(head, 1));
    printf("Compte 3 :\n");
    print_history(find_account(head, 3));
    
    if (delete_account(&head, 2) == 0) {
        printf("Deleted 2\n");
    } else {
        printf("Delete 2 failed\n");
    }
    print_accounts(head);

    if (delete_account(&head, 1) == 0) {
        printf("Deleted 1\n");
    } else {
        printf("Delete 1 failed\n");
    }
    print_accounts(head);

    if (delete_account(&head, 99) == 0) {
        printf("Delete 99\n");
    } else {
        printf("Delete 99 failed\n");
    }
    print_accounts(head);
    
    if (save_accounts(head, "accounts.txt") != 0) {
        printf("Save failed\n");
    }
    struct Account *loaded = load_accounts("accounts.txt");
    print_accounts(loaded);

    free_accounts(loaded);
    free_accounts(head);

    return 0;
}