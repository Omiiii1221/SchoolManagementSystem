// getfunction.c
//  this file contain all the functions which will give us total counts of each table
//
#include <windows.h> // for windows sleep
#include <unistd.h>  // for linux sleep
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "getfunctions.h"
#include "attendance.h"
#include "student.h"
#include "employee.h"
#include "class.h"

// to make a folder in c drive
#include <errno.h>
#include <direct.h>
#include <sys/stat.h>

// this will make a new file in c drive when user first time runc exe/program and after words that it will
// be used to store data
void makefolder()
{
    if (_mkdir("C:\\SMS") == -1)
    {
        printf("error");
    }
}

// Function to get current date
void get_current_date(char *current_date)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(current_date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Function to count attendance for the current date
void count_attendance(const char *attendance_filename, int *total_present, int *total_absent)
{
    FILE *fp_attendance;
    struct Attendance A;
    char current_date[12];

    get_current_date(current_date);

    *total_present = 0;
    *total_absent = 0;

    fp_attendance = fopen(attendance_filename, "rb");
    if (fp_attendance == NULL)
    {
        // printf("Error opening attendance file");
        return;
    }

    while (fread(&A, sizeof(struct Attendance), 1, fp_attendance) == 1)
    {
        if (strcmp(A.date, current_date) == 0)
        {
            if (A.status == 'P' || A.status == 'p')
            {
                (*total_present)++;
            }
            else if (A.status == 'A' || A.status == 'a')
            {
                (*total_absent)++;
            }
        }
    }

    fclose(fp_attendance);
}

// Function to get the count of total students
int get_total_students(const char *filename)
{
    FILE *fp;
    struct Student S;
    int count = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // printf("Error opening student file");
        return -1;
    }

    while (fread(&S, sizeof(struct Student), 1, fp) == 1)
    {
        count++;
    }

    fclose(fp);
    return count;
}

// Function to get the count of total employees
int get_total_employees(const char *filename)
{
    FILE *fp;
    struct Employee E;
    int count = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // printf("Error opening employee file");
        return -1;
    }

    while (fread(&E, sizeof(struct Employee), 1, fp) == 1)
    {
        count++;
    }

    fclose(fp);
    return count;
}

// Function to get the total number of paid employees
int get_total_paid_employees(const char *filename)
{
    FILE *fp;
    struct Employee E;
    int count = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // printf("Error opening employee file");
        return -1;
    }

    while (fread(&E, sizeof(struct Employee), 1, fp) == 1)
    {
        if (E.salary_paid > 0)
        {
            count++;
        }
    }

    fclose(fp);
    return count;
}

// Function to get the total number of unpaid employees
int get_total_unpaid_employees(const char *filename)
{
    FILE *fp;
    struct Employee E;
    int count = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // printf("Error opening employee file");
        return -1;
    }

    while (fread(&E, sizeof(struct Employee), 1, fp) == 1)
    {
        if (E.salary_paid <= 0)
        {
            count++;
        }
    }

    fclose(fp);
    return count;
}

// to get totel student in a class
void get_total_students_enrolled_in_Class()
{
    struct Student student;
    struct Class C;
    char class_name[50];
    int i;
    char capital[50];
    int found_class = 0;
    int found_students = 0;

    printf("\n\t\t\t\t\t\t\tEnter Class Name To List Enrolled Students: ");
    fgets(class_name, sizeof(class_name), stdin);
    class_name[strcspn(class_name, "\n")] = '\0';

    // Convert class to upper case
    for (i = 0; class_name[i] != '\0'; i++)
    {
        capital[i] = toupper(class_name[i]);
    }
    capital[i] = '\0';
    strcpy(class_name, capital);

    FILE *classFile = fopen("C:\\SMS\\Class.txt", "rb");
    if (classFile == NULL)
    {
        printf("\n\t\t\t\t\t\t\tUnable to open class file.\n");
        return;
    }

    // Searching for the class in the class file by comparing user given class name and file saved class name
    while (fread(&C, sizeof(struct Class), 1, classFile) == 1)
    {
        if (strcmp(C.class_name, class_name) == 0)
        {
            found_class = 1;
            break;
        }
    }
    fclose(classFile);

    if (!found_class)
    {
        printf("\n\t\t\t\t\t\t\tClass not found.\n");
        return;
    }

    FILE *studentFile = fopen("C:\\SMS\\Student.txt", "rb");
    if (studentFile == NULL)
    {
        printf("\n\t\t\t\t\t\t\tUnable to open student file.\n");
        return;
    }

    printf("\n\n\t\t\t\t\t\t\t\t<== Students Enrolled in Class: %s ==>\n\n", class_name);
    printf("\t\t\t\t\t\t\t%-10s  %-30s\n", "Student ID", "Student Name");
    printf("\t\t\t\t\t\t\t-------------------------------------------------\n");

    // Searching for students who have Enrolled in the class
    while (fread(&student, sizeof(struct Student), 1, studentFile))
    {
        if (strcmp(student.Studentclass, class_name) == 0)
        {
            printf("\t\t\t\t\t\t\t%-10d  %-30s\n", student.student_id, student.Studentname);
            found_students = 1;
        }
    }

    if (!found_students)
    {
        printf("\t\t\t\t\t\t\tNo students found.\n");
    }

    fclose(studentFile);
}

// get total revenue in this function we will gather data of students who have paid fee
//  we willn access this data from student.txt
// and reduce sallaery paid to employees from employee.txt
int get_total_Revenue(const char *filename) {
    FILE *fp;
    FILE *fe;
    struct Student S;
    struct Employee E;
    float total = 0;

    // Opening the student file 
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening student file\n");
        return -1;
    }

    // Adding fees deposited by student to the total
    while (fread(&S, sizeof(struct Student), 1, fp) == 1) {
        if (S.fees_paid > 0) {
            total += S.fees_paid;
        }
    }
    fclose(fp);

    fe = fopen("C:\\SMS\\Employee.txt", "rb");
    if (fe == NULL) {
        printf("Error opening employee file\n");
        return -1;
    }

    // reducing salaries paid to employees from the total amount
    while (fread(&E, sizeof(struct Employee), 1, fe) == 1) {
        if (E.salary_paid > 0) {
            total -= E.salary_paid;
        }
    }
    fclose(fe);

    return total;
}
// ***************** revenue report
// 1 - 1 get current date use code from fees list
// 2  make a list of each student who have paid in half or full their due amount  and toten revenue
// 3 use refference from get attendance get totel students get revenue

void list_students_and_total_revenue(const char *filename)
{
    system("cls");
    FILE *fp;
    struct Student S;
    // initilizing totel revenue as 0 at start
    float total_revenue = 0;

    printf("\t\t\t\t\t\t\t\t<== Students Who Have Paid Fees ==>\n\n");
    printf("\t\t\t\t\t\t\t%-20s  %-30s  %-20s  %-20s\n", "Student ID", "Student Name", "Fees Paid", "Fees Due");
    printf("\t\t\t\t\t\t\t------------------------------------------------------------------------------------------\n");

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // printf("Error opening file");
        return;
    }

    while (fread(&S, sizeof(struct Student), 1, fp) == 1)
    {
        if (S.fees_paid > 0)
        {
            printf("\t\t\t\t\t\t\t%-20d  %-30s  %-20.2f  %-20.2f\n", S.student_id, S.Studentname, S.fees_paid, S.fees_due);
            total_revenue = total_revenue + S.fees_paid;
            // totel
        }
    }

    fclose(fp);

    printf("\n\t\t\t\t\t\t\tTotal Revenue: %.2f\n", total_revenue);
}

// int main()
// {
//       const char *filename = "Student.txt";
//     list_students_and_total_revenue(filename);
//     return 0;
// }
