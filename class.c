// class.c
// This file contains functions related to class operations such as add class, delete class, and list class.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // for Windows sleep
#include <unistd.h>  // for Linux sleep
#include <ctype.h>

#include "subjects.h"
#include "class.h"
#include "getfunctions.h"
#include "generateReport.h"
#include "employee.h"

struct Class C;
FILE *fp;
char capital[50];
void addClass()
{
    system("cls");
    struct Class C;
    FILE *fp;

    fp = fopen("C:\\SMS\\Class.txt", "ab");
    if (fp == NULL)
    {
        printf("\n\n\t\t\t\t\t\tError opening file\n");
        return;
    }

    printf("\n\n\t\t\t\t\t\t\t\t<== Add Class ==>\n\n");

    printf("\n\n\t\t\t\t\t\t\tEnter Class ID: ");
    scanf("%d", &C.class_id);
    getchar();

    printf("\n\n\t\t\t\t\t\t\tEnter Class Name: ");
    fgets(C.class_name, sizeof(C.class_name), stdin);
    C.class_name[strcspn(C.class_name, "\n")] = '\0';
    // Convert class to upper case
    int i;
    for (i = 0; C.class_name[i] != '\0'; i++)
    {
        capital[i] = toupper(C.class_name[i]);
    }
    capital[i] = '\0';
    strcpy(C.class_name, capital);

    printf("\n\n\t\t\t\t\t\t\tEnter Tuition Fee: ");
    scanf("%f", &C.tuitionfee);
    getchar();

    printf("\n\n\t\t\t\t\t\t\tEnter Teacher ID for this Class: ");
    scanf("%d", &C.teacher_id);
    getchar();

    // Check if the teacher ID exists in Employee.txt
    FILE *employeeFile = fopen("C:\\SMS\\Employee.txt", "rb");
    if (employeeFile == NULL)
    {
        printf("\n\n\t\t\t\t\t\t\tError opening employee file\n");
        printf("\n\n\t\t\t\t\t\t\tWait for 2 seconds! Redirecting to add Employee...");
        sleep(4); // SLEEP SCREEN FOr 4 seconds
        fclose(fp);
        // addEmployee(); // Redirecting user to add Employee
        return;
    }
    fclose(employeeFile);

    fwrite(&C, sizeof(struct Class), 1, fp);
    fclose(fp);

    printf("\n\n\t\t\t\t\t\t\tClass Added Successfully\n");
}

void Classlist()
{
    struct Class C;
    FILE *fp;

    system("cls");
    printf("\n\n\t\t\t\t\t\t\t\t\t\t<== Class List ==>\n\n");
    printf("\n\n\t\t\t\t\t\t%-10s  %-30s %-20s %-30s\n", "Class ID", "Class Name", "Tuition Fee", "Teacher ID");
    printf("\n\t\t\t\t\t\t--------------------------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Class.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\n\t\t\t\t\t\tError opening file\n");
        printf("\n\n\t\t\t\t\t\tRedirecting to add class...");
        sleep(5);   // Pause for 5 seconds
        addClass(); // Redirect user to add class
        return;
    }

    while (fread(&C, sizeof(struct Class), 1, fp) == 1)
    {
        printf("\t\t\t\t\t\t%-10d  %-30s %-20.2f %-30d\n", C.class_id, C.class_name, C.tuitionfee, C.teacher_id);
    }
    printf("\n\t\t\t\t\t\t-------------------------------------------------------------------------------------\n\n");

    fclose(fp);
    getchar();
}

void DeleteClass()
{
    system("cls");
    int class_id, found = 0;
    printf("\n\n\t\t\t\t\t\t\t\t<== Delete Class ==>\n\n");
    printf("\n\n\t\t\t\t\t\t\tEnter Class ID to Delete: ");
    scanf("%d", &class_id);
    getchar();

    fp = fopen("C:\\SMS\\Class.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\n\t\t\t\t\t\t\tError opening file\n");
        return;
    }

    FILE *ft = fopen("C:\\SMS\\temp.txt", "wb");
    if (ft == NULL)
    {
        printf("\n\n\t\t\t\t\t\t\tError opening temporary file\n");
        fclose(fp);
        return;
    }

    while (fread(&C, sizeof(struct Class), 1, fp) == 1)
    {
        if (class_id == C.class_id)
        {
            found = 1;
        }
        else
        {
            fwrite(&C, sizeof(struct Class), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    if (found)
    {
        remove("C:\\SMS\\Class.txt");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\Class.txt");
        printf("\n\n\t\t\t\t\t\t\tClass Deleted Successfully.\n");
    }
    else
    {
        remove("C:\\SMS\\temp.txt");
        printf("\n\n\t\t\t\t\t\t\tRecord Not Found!\n");
    }
}

//
void classes_with_Subjects() {
    FILE *Subjectfile = fopen("C:\\SMS\\Subject.txt", "r");

    if (!Subjectfile) {
        printf("\n\n\t\t\t\t\t\t\tUnable to open Subject file for reading subjects.\n");
        return;
    }

    struct Class C;
    Subject Sub;
    char buffer[256];

    printf("\n\n\t\t\t\t\t\t\t\t\t<== Subjects With Class ==>\n\n");
    printf("\n\n\t\t\t\t\t\t\tEnter Class Name To View Subjects: ");
    fgets(C.class_name, sizeof(C.class_name), stdin);
    C.class_name[strcspn(C.class_name, "\n")] = '\0';
    toUpperCase(C.class_name);

    int found = 0;
    printf("\t\t\t\t\t\t\t----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t%-10s      %-30s\n", "Subject ID", "Subject Name");
    printf("\t\t\t\t\t\t\t----------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), Subjectfile)) {
        // Parse each line as a Subject
        sscanf(buffer, "%d,%49[^,],%49[^,],%d,%d",
               &Sub.subject_id, Sub.class_name, Sub.subject_name,
               &Sub.teacher_id, &Sub.Totel_sub_marks);

        toUpperCase(Sub.class_name);  // Convert to uppercase for comparison consistency

        if (strcmp(Sub.class_name, C.class_name) == 0) {
            printf("\t\t\t\t\t\t\t\t%-10d      %-30s\n", Sub.subject_id, Sub.subject_name);
            found = 1;
        }
    }

    if (!found) {
        printf("\n\n\t\t\t\t\t\t\tNo subjects found for class %s.\n", C.class_name);
    }
    printf("\t\t\t\t\t\t\t----------------------------------------------\n");

    fclose(Subjectfile);
}


// int main()
// {
//     classes_with_Subjects();
// }