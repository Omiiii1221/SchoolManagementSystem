// Department.c
// this file contains Functions Related Department
// Aas follows
// Add department , List department ,Delete Department
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Department.h"
#include <conio.h>
#include <windows.h> // for windows sleep
#include <unistd.h>  // for linux sleep
struct Department D;

FILE *fp;

void addDepartment()
{
    system("cls");

    fp = fopen("C:\\SMS\\Department.txt", "ab");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening file");
        return;
    }
    //%s is a format specifier for a string and -10 means it should be left aligned and more than 10 char else it will print 10 spapces
    printf("\n\n\n\t\t\t\t\t\t\t\t<== ADD DEPARTMENT ==>\n\n");
    printf("\n\n\t\t\t\t\t\t\tEnter New Department ID: ");
    scanf("%d", &D.id);
    printf("\n\n\t\t\t\t\t\t\tEnter Department Name: ");
    getchar();
    fgets(D.name, sizeof(D.name), stdin);
    D.name[strcspn(D.name, "\n")] = '\0';

    fwrite(&D, sizeof(D), 1, fp);
    fclose(fp);
    printf("\n\n\t\t\t\t\t\t\tDepartment Added Successfully\n");
}

void Departmentlist()
{

    system("cls");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t<== Department List ==>\n\n");
    printf("\t\t\t\t\t\t\t%-15s  %-30s\n", "Department ID", "Department Name");
    printf("\n\t\t\t\t\t\t\t------------------------------------------\n");
    fp = fopen("C:\\SMS\\Department.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\n\t\t\t\t\t\t\twait for 2 sec Redirecting to add department...\n\n");

        sleep(5); // sleep will pause terminal for desired seconds

        addDepartment(); // if there are no departments to list it will redirect user to add department

        return;
    }

    while (fread(&D, sizeof(D), 1, fp) == 1)
    {
        printf("\t\t\t\t\t\t\t%-10d  %-30s\n", D.id, D.name);
    }
    printf("\t\t\t\t\t\t\t------------------------------------------\n");
    fclose(fp);
    getchar();
    // printf("press Enter key to continue....");
    // getchar();
}

void DeleteDepartment()
{
    int department_id, found = 0;
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t<== Delete Department ==>\n\n");
    printf("\n\t\t\t\t\t\t\tEnter Department ID to Delete: ");
    scanf("%d", &department_id);

    FILE *temp;
    fp = fopen("C:\\SMS\\Department.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening file");
        return;
    }

    temp = fopen("C:\\SMS\\temp.txt", "wb");
    if (temp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening temporary file");
        fclose(fp);
        return;
    }

    while (fread(&D, sizeof(D), 1, fp) == 1)
    {
        if (department_id == D.id)
        {
            found = 1;
        }
        else
        {
            fwrite(&D, sizeof(D), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp); // closing both files

    remove("C:\\SMS\\Department.txt");
    rename("C:\\SMS\\temp.txt", "C:\\SMS\\Department.txt");

    if (found)
    {
        printf("\n\n\t\t\t\t\t\t\tDepartment Deleted Successfully.\n");
    }
    else
    {
        printf("\n\n\t\t\t\t\t\t\tRecord Not Found!\n");
    }
}
