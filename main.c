#include <stdio.h>
#include "account.h"

static void empty_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_int(const char *prompt, int *out) {
    printf("%s", prompt);
    if (scanf("%d", out) != 1) {
        empty_buffer();
        printf("Invalid input\n");
        return -1;
    }
    empty_buffer();
    return 0;
}

static int read_long(const char *prompt, long *out) {
    printf("%s", prompt);
    if (scanf("%ld", out) != 1) {
        empty_buffer();
        printf("Invalid input\n");
        return -1;
    }
    empty_buffer();
    return 0;
}

int main(void) {
    struct Account *head = NULL;
    int choice;

    do {
        printf("Menu\n");
        printf("1. Add account\n");
        printf("2. Show accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Transfer\n");
        printf("6. History\n");
        printf("7. Delete account\n");
        printf("8. Save\n");
        printf("9. Load\n");
        printf("0. Quit\n");
        printf("Enter your choice : ");
        if (scanf("%d", &choice) != 1) { 
            empty_buffer();
            choice = -1;
        } else {
            empty_buffer();
        }

        switch (choice) {
            case 1: {
                int number;
                char owner[50];
                long balance;
                printf("Number, owner, balance (in cents) : ");
                if (scanf("%d %49s %ld", &number, owner, &balance) != 3) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();
                if (balance < 0) {
                    printf("Invalid balance\n");
                    break;
                }
                if (find_account(head, number) != NULL) {
                    printf("Account number already exists\n");
                    break;
                }
                struct Account *a = create_account(number, owner, balance);
                if (a == NULL) {
                    printf("malloc failed\n");
                    break;
                }
                append_account(&head, a);
                break;
            }

            case 2:
                print_accounts(head);
                break;

            case 3: {
                int number;
                long amount;
                if (read_int("Account number : ", &number) != 0) {
                    break;
                }
                struct Account *found = find_account(head, number);
                if (found == NULL) {
                    printf("Account not found\n");
                    break;
                }
                if (read_long("Deposit amount (cents) : ", &amount) != 0) {
                    break;
                }
                if (deposit(found, amount) == 0) {
                    printf("Deposit success\n");
                } else {
                    printf("Deposit failed\n");
                }
                break;
            }

            case 4: {
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
                printf("Withdraw amount (cents) : ");
                if (scanf("%ld", &amount) != 1) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();
                if (withdraw(found, amount) == 0) {
                    printf("Withdraw success\n");
                } else {
                    printf("Withdraw failed\n");
                }
                break;
            }

            case 5: {
                int from_number;
                int to_number;
                long amount;
                printf("From account : ");
                if (scanf("%d", &from_number) != 1) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();
                printf("To account : ");
                if (scanf("%d", &to_number) != 1) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();

                printf("Amount (cents) : ");
                if (scanf("%ld", &amount) != 1) {
                    empty_buffer();
                    printf("Invalid input\n");
                    break;
                }
                empty_buffer();

                struct Account *from = find_account(head, from_number);
                struct Account *to = find_account(head, to_number);
                if (from == NULL || to == NULL) {
                    printf("Account not found\n");
                    break;
                }
                if (transfer(from, to, amount) == 0) {
                    printf("Transfer success\n");
                } else {
                    printf("Transfer failed\n");
                }
                break;
            }

            case 6: {
                int number;
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
                print_history(found);
                break;
            }

            case 7: {
                int number;
                if (read_int("Account number : ", &number) != 0) {
                    break;
                }
                if (delete_account(&head, number) == 0) {
                    printf("Deleted\n");
                } else {
                    printf("Account not found\n");
                }
                break;
            }

            case 8:
                if (save_accounts(head, "accounts.txt") == 0) {
                    printf("Saved\n");
                } else {
                    printf("Save failed\n");
                }
                break;

            case 9: {
                struct Account *loaded = load_accounts("accounts.txt");
                if (loaded == NULL) {
                    printf("Load failed or file empty\n");
                    break;
                }
                free_accounts(head);
                head = loaded;
                printf("Loaded\n");
                break;
            }

            case 0:
                break;
            default:
                printf("Invalid choice\n");

        }
    } while (choice != 0);

    free_accounts(head);
    return 0;

}