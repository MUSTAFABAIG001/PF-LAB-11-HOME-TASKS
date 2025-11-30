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
        printf("\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Details\n5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            printf("Enter Account Number: ");
            scanf("%d", &a[count].accNum);
            printf("Enter Name: ");
            scanf("%s", a[count].name);
            printf("Type (Savings/Current/Fixed): ");
            scanf("%s", a[count].type);
            
            while(1) {
                printf("Enter Initial Balance: ");
                scanf("%f", &a[count].balance);
                
                int valid = 0;
                
                if(strcmp(a[count].type, "Savings") == 0) {
                    if(a[count].balance >= 1000) {
                        valid = 1;
                    } else {
                        printf("Error: Savings needs minimum $1000\n");
                    }
                }
                else if(strcmp(a[count].type, "Current") == 0) {
                    if(a[count].balance >= 5000) {
                        valid = 1;
                    } else {
                        printf("Error: Current needs minimum $5000\n");
                    }
                }
                else if(strcmp(a[count].type, "Fixed") == 0) {
                    if(a[count].balance >= 10000) {
                        valid = 1;
                    } else {
                        printf("Error: Fixed Deposit needs minimum $10000\n");
                    }
                }
                else {
                    printf("Invalid Account Type entered. Setting valid to exit loop but check type again next time.\n");
                    valid = 1; 
                }

                if(valid == 1) break;
            }

            printf("Creation Date (dd/mm/yyyy): ");
            scanf("%s", a[count].createDate);
            strcpy(a[count].lastTransDate, a[count].createDate);
            a[count].transCount = 0;
            count++;
            printf("Account Created Successfully.\n");
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
                    
      
                    float remaining = a[i].balance - amt;
                    int canWithdraw = 1;

                    if(strcmp(a[i].type, "Savings") == 0 && remaining < 1000) canWithdraw = 0;
                    if(strcmp(a[i].type, "Current") == 0 && remaining < 5000) canWithdraw = 0;
                    if(strcmp(a[i].type, "Fixed") == 0 && remaining < 10000) canWithdraw = 0;

                    if(canWithdraw == 0) {
                        printf("Cannot withdraw. Balance will fall below minimum.\n");
                    } 
                    else if(remaining < 0) {
                        printf("Insufficient funds.\n");
                    } 
                    else {
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
