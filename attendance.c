// attendence.c
// this file contsins functions related to attendence
//  mark attendence (add), attendence list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attendance.h"
#include "student.h"
#include <windows.h>// for windows sleep
#include <unistd.h>// for linux sleep


FILE *fp;

// in this function we mark attendence of students  for doing that ge are going to get students id
// and  name from student.txt
void markAttendance()
{
        system("cls");

    struct Student students[100];
    struct Attendance A;
    char date[12];
    char status;
    int student_count = 0;
  printf("\n\n\n\t\t\t\t\t\t\t<== MARK/ADD ATTENDANCE ==>\n\n");
    // Takeing input for date from user
    printf("\n\t\t\t\t\t\t\tEnter date for Attendance (DD/MM/YYYY): ");
    scanf("%s", date);
    getchar();

    // Reading student records from file
    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening Student.txt");
        printf("\n\n\t\t\t\t\t\t\tRedirecting to add student...");
        sleep(5);//sleep will pause terminal for desired seconds

        addStudent(); // it will redirect user to add student
        return;
    }
    // reading student record
    while (fread(&students[student_count], sizeof(struct Student), 1, fp) == 1)
    {
        student_count++;
    }
    // closing file
    fclose(fp);

    // Opening attendance.txt file to append
    fp = fopen("C:\\SMS\\Attendance.txt", "ab");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening Attendance.txt");
        return;
    }

    // marking attendance for each student
    // from start to no of students in file we are starting a loop
    for (int i = 0; i < student_count; i++)
    {
        printf("\n\t\t\t\t\t\t\tEnter attendance for %d : %s (P/A): ", students[i].student_id, students[i].Studentname);
        scanf(" %c", &status);

        A.student_id = students[i].student_id;
        strcpy(A.date, date); // coping date that we got from user in attendence
        //
        A.status = (status == 'P' || status == 'p') ? 'P' : 'A';
        // writing attendace data into file
        fwrite(&A, sizeof(struct Attendance), 1, fp);
    }
    // closing file
    fclose(fp);

    printf("\n\t\t\t\t\t\t\tRecords Added Successfully for date: %s\n", date);
}

// in this function we are going to print attendance list
void AttendanceList()
{
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t\t<== Attendance Register ==>\n\n");

    FILE *fp_attendance, *fp_students; //
    struct Attendance A;               //
    struct Student S;
    char current_date[12] = "";
    int date_header_printed = 0;

    // opening attendance.txt
    fp_attendance = fopen("C:\\SMS\\Attendance.txt", "rb");
    if (fp_attendance == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening Attendance.txt");
        printf("\n\n\t\t\t\t\t\t\tRedirecting to add attendence...");
        sleep(5);//sleep will pause terminal for desired seconds

        markAttendance(); // it will redirect user to add attendence
        return;
    }
    // opening student.txt
    fp_students = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp_students == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening Student.txt");
        fclose(fp_attendance); // if we cant able to open student.txt then we will be closing attendence.txt
        return;
    }

    printf("\n\t\t\t\t\t\t\t%-10s %-20s %-15s %-10s\n", "Student ID", "Student Name", "Date", "Status");
    printf("\t\t\t\t\t\t\t------------------------------------------------------------\n");

    while (fread(&A, sizeof(struct Attendance), 1, fp_attendance) == 1)
    {
        // Reading student's information
        fseek(fp_students, 0, SEEK_SET);
        while (fread(&S, sizeof(struct Student), 1, fp_students) == 1)
        {
            if (A.student_id == S.student_id)
            {
                break;
            }
        }
        // comparing
        if (strcmp(A.date, current_date) != 0)
        {
            if (date_header_printed)
            {
                printf("\n\t\t\t\t\t\t\t------------------------------------------------------------\n");
            }
            printf("\n\t\t\t\t\t\t\tDate: %s\n", A.date);
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------\n");
            strcpy(current_date, A.date);
            date_header_printed = 1;
        }

        printf("\t\t\t\t\t\t\t%-10d %-20s %-15s %-10c\n", A.student_id, S.Studentname, A.date, A.status);
    }

    fclose(fp_attendance);
    fclose(fp_students);
}

/* fseek() is used to move the file pointer associated with a given file to a specific position.
SEEK_END: It denotes the end of the file.
SEEK_SET: It denotes starting of the file.
SEEK_CUR: It denotes the file pointer’s current position. */