#include <stdio.h>
#include <string.h>

struct Transaction {
    char type[20];
    float amount;
    char date[15];
};

struct Account {
    int accNum;
    char name[50];
    char type[20]; 
    float balance;
    char createDate[15];
    char lastTransDate[15];
    struct Transaction history[50];
    int transCount;
};

void main() {
    struct Account a[50];
    int count = 0;
    int choice, i, accID, found;
    float amt;
    char date[15];

    while(1) {
        printf("\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Details & Interest\n5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            printf("Enter Account Number: ");
            scanf("%d", &a[count].accNum);
            printf("Enter Name: ");
            scanf("%s", a[count].name);
            printf("Type (Savings/Current/Fixed): ");
            scanf("%s", a[count].type);
            
            int ok = 0;
            do {
                printf("Initial Balance: ");
                scanf("%f", &a[count].balance);
                
                if(strcmp(a[count].type, "Savings") == 0 && a[count].balance >= 1000) ok = 1;
                else if(strcmp(a[count].type, "Current") == 0 && a[count].balance >= 5000) ok = 1;
                else if(strcmp(a[count].type, "Fixed") == 0 && a[count].balance >= 10000) ok = 1;
                else printf("Balance too low for account type.\n");
            } while(ok == 0);

            printf("Creation Date (dd/mm/yyyy): ");
            scanf("%s", a[count].createDate);
            strcpy(a[count].lastTransDate, a[count].createDate);
            a[count].transCount = 0;
            count++;
            printf("Account Created.\n");
        }
        else if(choice == 2) {
            printf("Enter Account Num: ");
            scanf("%d", &accID);
            found = 0;
            for(i = 0; i < count; i++) {
                if(a[i].accNum == accID) {
                    found = 1;
                    printf("Amount to deposit: ");
                    scanf("%f", &amt);
                    printf("Date: ");
                    scanf("%s", date);
                    
                    a[i].balance += amt;
                    strcpy(a[i].history[a[i].transCount].type, "Deposit");
                    a[i].history[a[i].transCount].amount = amt;
                    strcpy(a[i].history[a[i].transCount].date, date);
                    strcpy(a[i].lastTransDate, date);
                    a[i].transCount++;
                    printf("Deposited. New Balance: %.2f\n", a[i].balance);
                }
            }
            if(found == 0) printf("Account not found.\n");
        }
        else if(choice == 3) {
            printf("Enter Account Num: ");
            scanf("%d", &accID);
            found = 0;
            for(i = 0; i < count; i++) {
                if(a[i].accNum == accID) {
                    found = 1;
                    printf("Amount to withdraw: ");
                    scanf("%f", &amt);
                    if(a[i].balance - amt < 0) {
                        printf("Insufficient funds.\n");
                    } else {
                        printf("Date: ");
                        scanf("%s", date);
                        a[i].balance -= amt;
                        strcpy(a[i].history[a[i].transCount].type, "Withdrawal");
                        a[i].history[a[i].transCount].amount = amt;
                        strcpy(a[i].history[a[i].transCount].date, date);
                        strcpy(a[i].lastTransDate, date);
                        a[i].transCount++;
                        printf("Withdrawn. New Balance: %.2f\n", a[i].balance);
                    }
                }
            }
            if(found == 0) printf("Account not found.\n");
        }
        else if(choice == 4) {
             printf("Enter Account Num: ");
            scanf("%d", &accID);
            for(i = 0; i < count; i++) {
                if(a[i].accNum == accID) {
                    printf("Name: %s\nType: %s\nBalance: %.2f\n", a[i].name, a[i].type, a[i].balance);
                    float interest = 0;
                    if(strcmp(a[i].type, "Savings") == 0) interest = a[i].balance * 0.04;
                    if(strcmp(a[i].type, "Fixed") == 0) interest = a[i].balance * 0.07;
                    printf("Estimated Annual Interest: %.2f\n", interest);
                    printf("Last Trans Date: %s\n", a[i].lastTransDate);
                    
                    printf("History\n");
                    for(int k=0; k<a[i].transCount; k++) {
                        printf("%s: %.2f on %s\n", a[i].history[k].type, a[i].history[k].amount, a[i].history[k].date);
                    }
                }
            }
        }
        else if(choice == 5) break;
    }
}
