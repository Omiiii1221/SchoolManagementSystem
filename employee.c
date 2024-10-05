// this file contains functions of employee
// add employee,list employee,delete employee
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include <windows.h>// for windows sleep
#include <unistd.h>// for linux sleep

struct Employee E;

FILE *fp;

void addEmployee() {
    system("cls");
    fp = fopen("C:\\SMS\\Employee.txt", "ab");
    if (fp == NULL) {
        printf("\n\t\t\t\t\t\t\tError opening file");
        return;
    }
 printf("\n\n\t\t\t\t\t\t\t\t<== Add Employee ==>\n\n");
    printf("\n\n\t\t\t\t\t\t\tEnter Employee id: ");
    scanf("%d", &E.employee_id);

    printf("\n\t\t\t\t\t\t\tEnter Employee name: ");
    getchar(); 
    fgets(E.name, sizeof(E.name), stdin);
    E.name[strcspn(E.name, "\n")] = '\0'; 

    printf("\n\t\t\t\t\t\t\tEnter Employee position: ");
    fgets(E.position, sizeof(E.position), stdin);
    E.position[strcspn(E.position, "\n")] = '\0'; 

    printf("\n\t\t\t\t\t\t\tEnter Employee salary: ");
    scanf("%f", &E.salary);
    E.salary_paid = 0.0;

    printf("\n\n\t\t\t\t\t\t\tEmployee Added Successfully\n");
    fwrite(&E, sizeof(E), 1, fp);
    fclose(fp);
}

void EmployeeList() {
    system("cls"); // This is not portable
    printf("\n\t\t\t\t\t\t\t\t<== Employee List ==>\n\n");
    printf("\t\t\t\t\t%-10s  %-30s %-30s %-10s %-10s\n", "Employee_id", "Employee Name", "Position", "Salary", "Salary Paid");
    printf("\t\t\t\t\t---------------------------------------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Employee.txt", "rb");
    if (fp == NULL) {
        printf("\n\t\t\t\t\t\t\tError opening file");
          printf("\n\n\t\t\t\t\t\t\tRedirecting to add employee...");
        sleep(5);//sleep will pause terminal for desired seconds

            addEmployee(); // it will redirect user to add class
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1) {
        printf("\t\t\t\t\t%-10d  %-30s %-30s %-10.2f %-10.2f\n", E.employee_id, E.name, E.position, E.salary, E.salary_paid);
    }
    fclose(fp);
    getchar();
}

void DeleteEmployee() {
    int employee_id, found = 0;
    system("cls"); // This is not portable
    printf("\n\t\t\t\t\t\t\t\t<== Delete Employee ==>\n\n");
    printf("\n\t\t\t\t\t\t\tEnter Employee id to Delete: ");
    scanf("%d", &employee_id);

    FILE *ft;
    fp = fopen("C:\\SMS\\Employee.txt", "rb");
    if (fp == NULL) {
        printf("\n\t\t\t\t\t\t\tError opening file");
        return;
    }

    ft = fopen("C:\\SMS\\temp.txt", "wb");
    if (ft == NULL) {
        printf("\n\t\t\t\t\t\t\tError opening temporary file");
        fclose(fp);
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1) {
        if (employee_id == E.employee_id) {
            found = 1;
        } else {
            fwrite(&E, sizeof(E), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("C:\\SMS\\Employee.txt");
    rename("C:\\SMS\\temp.txt", "C:\\SMS\\Employee.txt");

    if (found) {
        printf("\n\n\n\t\t\t\t\t\t\tEmployee Deleted Successfully.\n");
    } else {
        printf("\n\n\n\t\t\t\t\t\t\tRecord Not Found!\n");
    }
}
