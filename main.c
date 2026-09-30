#include <stdio.h>
#include "account.h"

int main() {
    struct Account *a = create_account(1, "Alice", 1000);
    if (a == NULL) {
        printf("create_account returns NULL\n");
        return 1;
    }
    printf("Compte cree\n");
    free_account(a);
    return 0;
}