#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define CRE_FILE "credentials.txt"

char currentUser[50];
char currentRole[20];

int login()
{
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];

    printf("USERNAME: ");
    scanf("%s", inUser);

    printf("PASSWORD: ");
    scanf("%s", inPass);

    FILE *fp = fopen(CRE_FILE, "r");

    while (fscanf(fp, "%49s %49s %19s", u, p, r) == 3)
    {
        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0)
        {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent()
{
    char roll[20];
    char name[50];
    float mark;

    printf("Roll: ");
    scanf("%s", roll);

    printf("Name: ");
    scanf(" %[^\n]", name);

    printf("Mark: ");
    scanf("%f", &mark);

    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%s|%s|%.2f\n", roll, name, mark);
    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents()
{
    FILE *fp = fopen(STUD_FILE, "r");
    char roll[20], name[50];
    float mark;

    printf("\n%-15s %-20s %-10s\n", "Roll", "Name", "Marks");
    printf("-----------------------------------------------------\n");

    while (fscanf(fp, "%19[^|]|%49[^|]|%f\n", roll, name, &mark) == 3)
    {
        printf("%-15s %-20s %.2f\n", roll, name, mark);
    }

    fclose(fp);
}

void searchStudent()
{
    char find[20], roll[20], name[50];
    float mark;

    printf("Enter roll to search: ");
    scanf("%s", find);

    FILE *fp = fopen(STUD_FILE, "r");

    while (fscanf(fp, "%19[^|]|%49[^|]|%f\n", roll, name, &mark) == 3)
    {
        if (strcmp(find, roll) == 0)
        {
            printf("Found: %s | %s | %.2f\n", roll, name, mark);
            fclose(fp);
            return;
        }
    }

    printf("Student not found!\n");
    fclose(fp);
}

void deleteStudent()
{
    char delRoll[20], roll[20], name[50];
    float mark;
    int found = 0;

    printf("Enter roll to delete: ");
    scanf("%s", delRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%19[^|]|%49[^|]|%f\n", roll, name, &mark) == 3)
    {
        if (strcmp(roll, delRoll) != 0)
            fprintf(temp, "%s|%s|%.2f\n", roll, name, mark);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found)
        printf("Student deleted!\n");
    else
        printf("Roll not found!\n");
}

void updateStudent()
{
    char updRoll[20], roll[20], name[50], newName[50];
    float mark, newMark;
    int found = 0;

    printf("Enter roll to update: ");
    scanf("%s", updRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%19[^|]|%49[^|]|%f\n", roll, name, &mark) == 3)
    {
        if (strcmp(roll, updRoll) == 0)
        {
            found = 1;
            printf("New Name: ");
            scanf(" %[^\n]", newName);
            printf("New Mark: ");
            scanf("%f", &newMark);
            fprintf(temp, "%s|%s|%.2f\n", roll, newName, newMark);
        }
        else
        {
            fprintf(temp, "%s|%s|%.2f\n", roll, name, mark);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found)
        printf("Student updated!\n");
    else
        printf("Roll not found!\n");
}

void adminMenu()
{
    int c;
    while (1)
    {
        printf("\nADMIN MENU\n");
        printf("1. Add Student\n2. Display\n3. Search\n4. Update\n5. Delete\n6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &c);

        if (c == 1)
            addStudent();
        else if (c == 2)
            displayStudents();
        else if (c == 3)
            searchStudent();
        else if (c == 4)
            updateStudent();
        else if (c == 5)
            deleteStudent();
        else
            return;
    }
}

void staffMenu()
{
    int c;
    while (1)
    {
        printf("\nSTAFF MENU\n");
        printf("1. Add\n2. Display\n3. Search\n4. Update\n5. Logout\n");
        scanf("%d", &c);

        if (c == 1)
            addStudent();
        else if (c == 2)
            displayStudents();
        else if (c == 3)
            searchStudent();
        else if (c == 4)
            updateStudent();
        else
            return;
    }
}

void guestMenu()
{
    int c;
    while (1)
    {
        printf("\nGUEST MENU\n");
        printf("1. Display\n2. Search\n3. Logout\n");
        scanf("%d", &c);

        if (c == 1)
            displayStudents();
        else if (c == 2)
            searchStudent();
        else
            return;
    }
}

int main()
{
    if (!login())
    {
        printf("Invalid login!\n");
        return 0;
    }

    printf("Logged in as: %s\n", currentRole);

    if (strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "staff") == 0)
        staffMenu();
    else
        guestMenu();

    return 0;
}