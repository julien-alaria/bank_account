#include <stdio.h>
#include "account.h"

static empty_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    struct Account *head = NULL;
    int choice;

    do {
        printf("...menu...\n");
        if (scanf("%d", &choice) != 1) { 
            empty_buffer();
            choice = -1;
        }
        empty_buffer();

        switch (choice) {
            case 1: {
                int number;
                char owner[50];
                long balance;
                printf("Number, titular, solde (in cents) : ");
                if (scanf("%d %49s %ld", &number, owner, &balance) != 1) {
                    empty_buffer();
                    printf("Saisie invalide\n");
                    break;
                }
                empty_buffer();
                struct Account *a = create_account(number, owner, balance);
                if (a == NULL) {
                    printf("malloc failed\n");
                    break;
                }
                append_account(&head, a);
                break;
            };

            case 2:
                print_accounts(head);
                break;

            case 3: {
                int account_number;
                int deposit_amount;
                scanf("Account number : ", &account_number);
                struct Account *found = find_account(head, account_number);
                if (found != NULL) {
                    printf("%s\n", found->owner);
                } else {
                    printf("Account not found\n");
                }
                scanf("Deposit amount : ", &deposit_amount);
                if (deposit(find_account(head, account_number), deposit_amount) == 0) {
                    printf("Deposit success\n");
                } else {
                    printf("Deposit failed\n");
                }
                break;
            };
                
            case 4: {
                int account_number;
                int withdraw_amount;
                scanf("Account number : ", &account_number);
                struct Account *found = find_account(head, account_number);
                if (found != NULL) {
                    printf("%s\n", found->owner);
                } else {
                    printf("Account not found\n");
                }
                scanf("Deposit amount : ", &withdraw_amount);
                if (withdraw(find_account(head, account_number), withdraw_amount) == 0) {
                    printf("Withdraw success\n");

                } else {
                    printf("Withdraw failed\n");
                }
                break;
            };
                  
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 0:
                break;
            default:
                printf("Choix invalide\n");

        }
    } while (choice != 0);

    free_accounts(head);
    return 0;

}