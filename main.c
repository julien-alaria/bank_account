#include <stdio.h>
#include "account.h"

static void empty_buffer(void) {
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
                if (scanf("%d %49s %ld", &number, owner, &balance) != 3) {
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
                int number;
                long amount;
                printf("Account number : ");
                if (scanf("%d", &number) != 1) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();
                struct Account *found = find_account(head, number);
                if (found == NULL) {
                    printf("Account not found\n");
                    break;
                }
                printf("Deposit amount (cents) : ");
                if (scanf("%ld", &amount) != 1) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();
                if (deposit(found, amount) == 0) {
                    printf("Deposit success\n");
                } else {
                    printf("Deposit failed\n");
                }
                break;
            };
                
            case 4:
                break;    
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