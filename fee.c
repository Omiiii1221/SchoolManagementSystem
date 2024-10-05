// fee.c
// this file contains Functions Related fee
// Aas follows
// payfees ,listFeeStatus

#include <stdio.h>
#include <stdlib.h>
#include "fee.h"
#include "student.h"
#include "getfunctions.h"
#include <windows.h> // for windows sleep
#include <unistd.h>  // for linux sleep

FILE *fp;

// in this function we are firstly geting student id from user to pay fee then we are comparing it with the records from student.txt
// after geting records we are fetching data of variable fee_due and printing to show user how many amount is due to from student
// then we geting amount which user is depositing and adding it to fees_paid in student.txt
void payFees()
{
    system("cls");

    // student_id to get id from user to compare with record id
    // found we will set it zero at start
    int student_id, found = 0;
    float amount;

    // to get current date
    void get_current_date(char *current_date);
    printf("\n\n\t\t\t\t\t\t\t\t<== Pay Fee ==>\n\n");

    printf("\n\t\t\t\t\t\t\tEnter Student ID: ");
    scanf("%d", &student_id);

    // opening file
    fp = fopen("C:\\SMS\\Student.txt", "rb");
    // checking if null then returning error
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\tRedirecting to add student...");
        sleep(5); // sleep will pause terminal for desired seconds

        addStudent(); // it will redirect user to add student
        return;
    }
    // while file is open we compare the previous student id we have taken from user and if we find record then we are printing due
    // amount from student.txt to
    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        if (S.student_id == student_id)
        {
            printf("\n\t\t\t\t\t\t\tAmount Due: %.2f\n", S.fees_due);
            break;
        }
    }
    // closing file
    fclose(fp);
    // getting deposit amount from user which student is depositing and storint it in variable amount
    printf("\n\t\t\t\t\t\t\tEnter Amount to Pay: ");
    scanf("%f", &amount);

    // new file pointer ft for temp file
    FILE *ft;
    // opening student.txt again for
    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\tRedirecting to add student...");
        sleep(5); // sleep will pause terminal for desired seconds

        addStudent(); // it will redirect user to add student
        return;
    }
    // opening temp  file
    ft = fopen("C:\\SMS\\temp.txt", "wb");
    if (ft == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening temporary file");
        fclose(fp);
        return;
    }
    // reading student.txt and checking user given student id and our records
    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        // if both id s are equal
        if (S.student_id == student_id)
        {
            found = 1;
            S.fees_paid += amount;
            S.fees_due -= amount;
        }
        // writing new fee paid amount in student.txt
        fwrite(&S, sizeof(S), 1, ft);
    }
    // closing student.txt and temp.txt
    fclose(fp);
    fclose(ft);

    // removing old student.txt file and renaming temp.txt as studenat.txt
    remove("C:\\SMS\\Student.txt");
    rename("C:\\SMS\\temp.txt", "C:\\SMS\\Student.txt");
    //
    if (found)
    {
        printf("\n\t\t\t\t\t\t\tFees Paid Successfully.\n");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tStudent ID Not Found.\n");
    }
}

// in this function we will make a list of students and students who have paid their fee
void listFeesStatus()
{
    // to cleare screen
    //%-10d prints 10 dash lines and then printing variable
    system("cls");
    printf("\n\t\t\t\t\t\t\t\t\t<== Fees Payment Status ==>\n\n");
    printf("\t\t\t\t\t\t%-10s  %-30s  %-10s\n", "Student ID", "Student Name", "Fees Due");
    printf("\t\t\t\t\t\t----------------------------------------------------------------\n");
    // opening file
    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\tRedirecting to add student...");
        sleep(5); // sleep will pause terminal for desired seconds

        addStudent(); // it will redirect user to add student

        return;
    }

    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        // id student have any amount due we are printing that students info
        if (S.fees_due > 0)
        {
            printf("\t\t\t\t\t\t%-10d  %-30s  %-10.2f\n", S.student_id, S.Studentname, S.fees_due);
        }
    }
    // closing the file
    fclose(fp);

    printf("\n\n\n\t\t\t\t\t\t\t\t|<== Students Who Have Paid Fees ==>\n\n");
    printf("\t\t\t\t\t\t%-10s  %-30s  %-10s  %-12s\n", "Student ID", "Student Name", "Fees Due", "Date Paid");
    printf("\t\t\t\t\t\t--------------------------------------------------------------------------\n");
    // opening student file again to get data and print name and id s of students who have paid thair fee
    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tError opening file");
        printf("\n\n\t\t\t\t\t\tRedirecting to add student...");
        sleep(5); // sleep will pause terminal for desired seconds

        addStudent(); // it will redirect user to add student
        return;
    }
    // if due amount is less than or equal to zero we print the sthudet id and name
    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        if (S.fees_due <= 0)
        {
            printf("\t\t\t\t\t\t%-10d  %-30s  %-10.2f  %-12s\n", S.student_id, S.Studentname, S.fees_due, S.date);
        }
    }
    // closing file
    fclose(fp);
    getchar();
}
