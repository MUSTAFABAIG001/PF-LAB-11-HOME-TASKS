#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int roll;
    float marks[3];
    float total;
    float per;
    char grade[3];
};

void main() {
    struct Student s[100];
    struct Student temp;
    int n, i, j, choice;
    int found = 0;
    float classTotal = 0, classAvg;
    char searchName[50];
    char searchGrade[3];
    int searchRoll;

    printf("Enter number of students: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Roll Number: ");
        scanf("%d", &s[i].roll);
        
        s[i].total = 0;
        for(j = 0; j < 3; j++) {
            do {
                printf("Enter marks for subject %d (0-100): ", j + 1);
                scanf("%f", &s[i].marks[j]);
                if(s[i].marks[j] < 0 || s[i].marks[j] > 100) {
                    printf("Invalid marks. Try again.\n");
                }
            } while(s[i].marks[j] < 0 || s[i].marks[j] > 100);
            s[i].total += s[i].marks[j];
        }

        s[i].per = s[i].total / 3.0;
        classTotal += s[i].per;

        if(s[i].per >= 90) strcpy(s[i].grade, "A+");
        else if(s[i].per >= 80) strcpy(s[i].grade, "A");
        else if(s[i].per >= 70) strcpy(s[i].grade, "B+");
        else if(s[i].per >= 60) strcpy(s[i].grade, "B");
        else if(s[i].per >= 50) strcpy(s[i].grade, "C");
        else strcpy(s[i].grade, "F");
    }

    
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(s[j].per < s[j+1].per) {
                temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    while(1) {
        printf("\n1. Display Rank List\n2. Search by Grade\n3. Class Average Info\n4. Search by Name/Roll\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            printf("\nRank\tName\tRoll\tPer\tGrade\n");
            for(i = 0; i < n; i++) {
                printf("%d\t%s\t%d\t%.2f\t%s\n", i+1, s[i].name, s[i].roll, s[i].per, s[i].grade);
            }
        }
        else if(choice == 2) {
            printf("Enter Grade to search: ");
            scanf("%s", searchGrade);
            found = 0;
            for(i = 0; i < n; i++) {
                if(strcmp(s[i].grade, searchGrade) == 0) {
                    printf("%s - %.2f%%\n", s[i].name, s[i].per);
                    found = 1;
                }
            }
            if(found == 0) printf("No students found.\n");
        }
        else if(choice == 3) {
            classAvg = classTotal / n;
            printf("Class Average: %.2f\n", classAvg);
            printf("Students Above Average:\n");
            for(i = 0; i < n; i++) {
                if(s[i].per > classAvg) printf("%s (%.2f)\n", s[i].name, s[i].per);
            }
            printf("Students Below Average:\n");
            for(i = 0; i < n; i++) {
                if(s[i].per < classAvg) printf("%s (%.2f)\n", s[i].name, s[i].per);
            }
        }
        else if(choice == 4) {
            printf("Search by 1.Name or 2.Roll? ");
            int sc;
            scanf("%d", &sc);
            found = 0;
            if(sc == 1) {
                printf("Enter Name: ");
                scanf("%s", searchName);
                for(i = 0; i < n; i++) {
                    if(strcmp(s[i].name, searchName) == 0) {
                        printf("Found: Roll %d, Grade %s\n", s[i].roll, s[i].grade);
                        found = 1;
                    }
                }
            } else {
                printf("Enter Roll: ");
                scanf("%d", &searchRoll);
                for(i = 0; i < n; i++) {
                    if(s[i].roll == searchRoll) {
                        printf("Found: %s, Grade %s\n", s[i].name, s[i].grade);
                        found = 1;
                    }
                }
            }
            if(found == 0) printf("Not Found.\n");
        }
        else if(choice == 5) {
            break;
        }
    }
}
