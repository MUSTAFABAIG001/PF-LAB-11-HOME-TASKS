#include <stdio.h>
#include <string.h>
#include<stdlib.h>
struct Date {
    int d, m, y;
};

struct Employee {
    int id;
    char name[50];
    char dept[20];
    char desig[20];
    float salary;
    struct Date doj;
    char phone[15];
    char email[50];
    int exp;
};

int main() {
    struct Employee e[100];
    int n = 0, i, choice, currentYear;
    char searchStr[50];

    printf("Enter current year: ");
    scanf("%d", &currentYear);

    while (1) {
        printf("\n1. Add Employee\n2. Dept Statistics\n3. Appraisal\n4. Check Promotions\n5. Search\n6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("ID: ");
            scanf("%d", &e[n].id);

            printf("Name: ");
            scanf(" %[^\n]", e[n].name);

            printf("Dept (IT/HR/Finance/Marketing/Operations): ");
            scanf(" %[^\n]", e[n].dept);

            printf("Designation (Intern/Junior/Senior/Manager/Director): ");
            scanf(" %[^\n]", e[n].desig);

            printf("Salary: ");
            scanf("%f", &e[n].salary);

            printf("Date of Joining (d m y): ");
            scanf("%d %d %d", &e[n].doj.d, &e[n].doj.m, &e[n].doj.y);

            printf("Phone: ");
            scanf(" %[^\n]", e[n].phone);

            printf("Email: ");
            scanf(" %[^\n]", e[n].email);

            e[n].exp = currentYear - e[n].doj.y;
            n++;
        }

        else if (choice == 2) {
            float it = 0, hr = 0, fin = 0, mar = 0, op = 0;

            for (i = 0; i < n; i++) {
                if (strcmp(e[i].dept, "IT") == 0) it += e[i].salary;
                else if (strcmp(e[i].dept, "HR") == 0) hr += e[i].salary;
                else if (strcmp(e[i].dept, "Finance") == 0) fin += e[i].salary;
                else if (strcmp(e[i].dept, "Marketing") == 0) mar += e[i].salary;
                else if (strcmp(e[i].dept, "Operations") == 0) op += e[i].salary;
            }

            printf("\nDepartment Salary Totals:\n");
            printf("IT: %.2f\nHR: %.2f\nFinance: %.2f\nMarketing: %.2f\nOperations: %.2f\n",
                   it, hr, fin, mar, op);
        }

        else if (choice == 3) {
            int eid;
            float inc;

            printf("Enter employee ID: ");
            scanf("%d", &eid);

            for (i = 0; i < n; i++) {
                if (e[i].id == eid) {
                    printf("Current Salary: %.2f\n", e[i].salary);
                    printf("Increment percentage (5-15): ");
                    scanf("%f", &inc);

                    e[i].salary += e[i].salary * (inc / 100);
                    printf("New Salary: %.2f\n", e[i].salary);
                    break;
                }
            }
        }

        else if (choice == 4) {
            printf("\nEmployees eligible for promotion (>3 years):\n");
            for (i = 0; i < n; i++) {
                if (e[i].exp > 3) {
                    printf("%s | %s | Experience: %d years\n",
                        e[i].name, e[i].desig, e[i].exp);
                }
            }
        }

        else if (choice == 5) {
            printf("Search by department/designation/experience: ");
            scanf(" %[^\n]", searchStr);

            for (i = 0; i < n; i++) {
                if (strcmp(e[i].dept, searchStr) == 0 ||
                    strcmp(e[i].desig, searchStr) == 0 ||
                    e[i].exp == atoi(searchStr)) 
                {
                    printf("%s | %s | %s | Exp: %d\n",
                        e[i].name, e[i].dept, e[i].desig, e[i].exp);
                }
            }
        }

        else if (choice == 6) {
            break;
        }
    }

    return 0;
}
