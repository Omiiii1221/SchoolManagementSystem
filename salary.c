// salary.c
// This file contains functions related to salary
// as follows: pay salary, list salary

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salary.h"
#include "employee.h"
#include <windows.h> // for Windows sleep
#include <unistd.h>  // for Linux sleep

FILE *fp;
struct Employee E;

void paySalary() {
        system("cls");

    int employee_id, found = 0;
    float amount;
    char date[12];
    printf("\n\n\t\t\t\t\t\t\t\t<== Pay  Salary ==>\n\n");

    printf("\n\n\t\t\t\t\t\t\tEnter Employee ID: ");
    scanf("%d", &employee_id);
    printf("\n\n\t\t\t\t\t\t\tEnter date : ");
    scanf("%f", &date);
    printf("\n\n\t\t\t\t\t\t\tEnter Amount to Pay: ");
    scanf("%f", &amount);

    fp = fopen("C:\\SMS\\Employee.txt", "rb");
    if (fp == NULL) {
        perror("\n\n\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\t\tRedirecting to add employee...");
        sleep(5); // sleep will pause terminal for desired seconds

        addEmployee(); // it will redirect user to add employee
        return;
    }

    FILE *ft = fopen("C:\\SMS\\temp.txt", "wb");
    if (ft == NULL) {
        perror("\n\n\t\t\t\t\t\t\tError opening temporary file");
        fclose(fp);
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1) {
        if (E.employee_id == employee_id) {
            found = 1;
            E.salary_paid += amount;
        }
        fwrite(&E, sizeof(E), 1, ft);
    }

    fclose(fp);
    fclose(ft);

    if (found) {
        remove("C:\\SMS\\Employee.txt");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\Employee.txt");
        printf("\n\n\t\t\t\t\t\t\tSalary Paid Successfully.\n");
    } else {
        remove("C:\\SMS\\temp.txt");
        printf("\n\n\t\t\t\t\t\t\tEmployee ID Not Found.\n");
    }
}

void listSalaryStatus() {
    system("cls");
    printf("\n\n\t\t\t\t\t\t\t\t<== Salary Payment Status ==>\n\n");
    printf("\t\t\t\t\t\t\t%-10s  %-30s  %-10s\n", "Employee_id", "Employee Name", "Salary Paid");
    printf("\t\t\t\t\t\t\t--------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Employee.txt", "rb");
    if (fp == NULL) {
        perror("\n\n\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\t\tRedirecting to add employee...");
        sleep(5); // sleep will pause terminal for desired seconds

        addEmployee(); // it will redirect user to add employee
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1) {
        if (E.salary_paid > 0) {
            printf("\t\t\t\t\t\t\t%-10d  %-30s  %-10.2f\n", E.employee_id, E.name, E.salary_paid);
        }
    }
    fclose(fp);

    printf("\n\n\n\n\t\t\t\t\t\t\tEmployees who have not been paid or have salary due:\n\n");
    printf("\t\t\t\t\t\t\t%-10s  %-30s  %-10s\n", "Employee_id", "Employee Name", "Salary Due");
    printf("\t\t\t\t\t\t\t------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Employee.txt", "rb");
    if (fp == NULL) {
        perror("\n\n\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\t\tRedirecting to add employee...");
        sleep(5); // sleep will pause terminal for desired seconds

        addEmployee(); // it will redirect user to add employee
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1) {
        if (E.salary_paid < E.salary) {
            float salary_due = E.salary - E.salary_paid;
            printf("\t\t\t\t\t\t\t%-10d  %-30s  %-10.2f\n", E.employee_id, E.name, salary_due);
        }
    }
    fclose(fp);
    getchar();
}
