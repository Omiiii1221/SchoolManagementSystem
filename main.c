// this is the main.c file our program will start from here

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <unistd.h> // for linux sleep
#include "student.h"
#include "Department.h"
#include "employee.h"
#include "class.h"
#include "subjects.h"
#include "getfunctions.h"
#include "fee.h"
#include "salary.h"
#include "marks.h"
#include "generateReport.h"
#include "authentication.h"
#include "exams.h"
#include "menus.h"

void markAttendance();
void AttendanceList();
void payFees();
void listFeesStatus();
void paySalary();
void listSalaryStatus();
void addMarks();
void updateMarks();
void deleteMarks();
void displayMarksBystudent_id();
void generateReport();

void loadingBar()
{
    system("color 0F");
    printf("* NOTE : Please Open In Full Screen For Better Experience......");
    // Initializeing char for printing loading bar
    char a = 177, b = 219; // extended ascii char
    int barLength = 60;

    printf("\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\t\t\t\t\t"
           "Loading...\n\n");
    printf("\t\t\t\t\t\t");

    // Printing initial loading bar
    for (int i = 0; i < barLength; i++)
        printf("%c", a);

    // by using r we can Set the cursor again to the starting point of the loading bar
    printf("\r");
    printf("\t\t\t\t\t\t");

    // Printing loading bar progress
    for (int i = 0; i < barLength; i++)
    {
        printf("%c", b);
        Sleep(70); // Sleep for 80 milliseconds

        // Printing percentage
        int percentage = (i + 1) * 100 / barLength;
        printf("\r\t\t\t\t\t"); // to Move cursor to the start of the bar
        for (int j = 0; j <= i; j++)
            printf("%c", b);
        printf(" %d%%", percentage);
    }
    printf("\n");
}

int main()
{
    int ch;
    char role[20];
    const char *filename = "C:\\SMS\\Student.txt"; // to get totel revenue list
    loadingBar();
    makefolder();
    while (1)
    {
    landingPage: // lable
        landingPage();
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            exit(0);
            break;

        case 1:
            strcpy(role, "Admin");
            login(role); //////// fix login
            while (1)
            {

            admin:
                Adminmenu();
                printf("\n\n\t\t\tEnter your choice: ");
                scanf("%d", &ch);

                switch (ch)
                {
                case 0:
                    goto landingPage; // goto
                    break;
                case 1:
                    Departmentlist();
                    addDepartment();
                    break;
                case 2:
                    Departmentlist();
                    break;
                case 3:
                    DeleteDepartment();
                    break;
                case 4:
                    addStudent();
                    break;
                case 5:
                    Studentlist();
                    break;
                case 6:
                    DeleteStudent();
                    break;
                case 7:
                    updateStudent();
                    break;
                case 8:
                    markAttendance();
                    break;
                case 9:
                    AttendanceList();
                    break;
                case 10:
                    Subjectlist();
                    addSubject();
                    break;
                case 11:
                    Subjectlist();
                    break;
                case 12:
                    DeleteSubject();
                    break;
                case 13:
                    Classlist();
                    addClass();
                    break;
                case 14:
                    Classlist();
                    classes_with_Subjects();
                    get_total_students_enrolled_in_Class();
                    break;
                case 15:
                    DeleteClass();
                    break;
                case 16:
                    addEmployee();
                    break;
                case 17:
                    EmployeeList();
                    break;
                case 18:
                    DeleteEmployee();
                    break;
                case 19:
                    payFees();
                    break;
                case 20:
                    listFeesStatus();
                    break;
                case 21:
                    system("cls");
                    printf("Exam Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go back.\n\n");
                    printf("\n\n\t\t\t\t\t\t\t=========================================\n");
                    printf("\t\t\t\t\t\t\t  ADD /UPDATE / DELETE EXAM Details\n");
                    printf("\t\t\t\t\t\t\t=========================================\n");
                    printf("\n\n\t\t\t\t\t\t\t 1. Add New Examination\n");
                    printf("\n\t\t\t\t\t\t\t 2.Update Examination\n");
                    printf("\n\t\t\t\t\t\t\t 3. Delete Examination\n");
                    printf("\n\t\t\t\t\t\t\tEnter your choice: ");
                    scanf("%d", &ch);
                    switch (ch)
                    {
                    case 0:
                        goto admin;
                        break;
                    case 1:
                        addExam();
                        break;
                    case 2:
                        updateExam();
                        break;
                    case 3:
                        deleteExam();
                        break;
                    default:
                        printf("\n\t\t\t\tInvalid Choice...\n\n");
                    }
                    getchar();
                    getchar();
                    break;
                case 22:
                    examlist();
                    break;
                case 23:
                    addMarks();
                    break;
                case 24:
                    updateMarks();
                    break;
                case 25:
                    deleteMarks();
                    break;
                case 26:
                    displayMarksBystudent_id();
                    break;
                case 27:
                    system("cls");
                    printf("Report Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go back.\n\n");
                    printf("\n\n\t\t\t\t\t\t\t=========================================\n");
                    printf("\t\t\t\t\t\t\t Generate Student / Class report\n");
                    printf("\t\t\t\t\t\t\t=========================================\n");
                    printf("\n\n\t\t\t\t\t\t\t 1. Generate Student Report\n");
                    printf("\n\t\t\t\t\t\t\t 2.Generate Class Report\n");
                    printf("\n\t\t\t\t\t\t\tEnter your choice: ");
                    scanf("%d", &ch);
                    switch (ch)
                    {
                    case 0:
                        goto admin;
                        break;
                    case 1:
                        generateReport();
                        break;
                    case 2:
                        generateClassReport();
                        break;
                    default:
                        printf("\n\t\t\t\tInvalid Choice...\n\n");
                    }
                    getchar();
                    getchar();
                    break;
                case 28:
                    listSalaryStatus();
                    paySalary();
                    break;
                case 29:
                    listSalaryStatus();
                    break;
                case 30:
                    list_students_and_total_revenue(filename);
                    break;
                default:
                    printf("\n\t\tInvalid Choice...\n\n");
                }
                getchar();
                printf("\n\n\n\t\t\t\t\t\t\tPress Any Key To Continue...");
                getchar();
            }
            break;

        case 2:
            while (1)
            {
                system("cls");
                printf("Employee menu...\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");
                printf("\n\n\t\t\t\t\t\t<------------------------------------------------------------->\n");
                printf("\t\t\t\t\t\t\t\t<== School Management System ==> \n");
                printf("\t\t\t\t\t\t<------------------------------------------------------------->\n");
                printf("\n\n\t\t\t\t\t\t\t\t\tI Am\n");
                printf("\n\n\n\n\t\t\t\t\t\t1. Principle \t\t2. Accountant \t\t3. Teacher\n");
                printf("\n\t\t\t\t\t\tEnter your choice: ");
                scanf("%d", &ch);

                switch (ch)
                {
                case 0:
                    goto landingPage; /// using goto
                    break;
                case 1:
                    while (1)
                    {
                        strcpy(role, "Principal");
                        login(role); // Principal login
                        principlemenu();
                        printf("\n\t\t\t\t\t\t your choice: ");
                        scanf("%d", &ch);

                        switch (ch)
                        {
                        case 0:
                            goto landingPage; /// using goto
                            break;
                        case 1:
                            addDepartment();
                            break;
                        case 2:
                            Departmentlist();
                            break;
                        case 3:
                            DeleteDepartment();
                            break;
                        case 4:
                            addStudent();
                            break;
                        case 5:
                            Studentlist();
                            break;
                        case 6:
                            DeleteStudent();
                            break;
                        case 7:
                            printf("Report Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go back.\n\n");
                            printf("\n\n\t\t\t\t\t\t\t=========================================\n");
                            printf("\t\t\t\t\t\t\t Generate Student / Class report\n");
                            printf("\t\t\t\t\t\t\t=========================================\n");
                            printf("\n\n\t\t\t\t\t\t\t 1. Generate Student Report\n");
                            printf("\n\t\t\t\t\t\t\t 2.Generate Class Report\n");
                            printf("\n\t\t\t\t\t\t\tEnter your choice: ");
                            scanf("%d", &ch);
                            switch (ch)
                            {
                            case 0:
                                goto admin;
                                break;
                            case 1:
                                generateReport();
                                break;
                            case 2:
                                generateClassReport();
                                break;
                            default:
                                printf("\n\t\t\t\tInvalid Choice...\n\n");
                            }
                            getchar();
                            getchar();
                            break;
                        case 8:
                            markAttendance();
                            break;
                        case 9:
                            AttendanceList();
                            break;
                        case 10:
                            addSubject();
                            break;
                        case 11:
                            Subjectlist();
                            break;
                        case 12:
                            DeleteSubject();
                            break;
                        case 13:
                            addClass();
                            break;
                        case 14:
                            Classlist();
                            break;
                        case 15:
                            EmployeeList();
                            break;
                        case 16:
                            payFees();
                            break;
                        case 17:
                            listFeesStatus();
                            break;
                        case 18:
                            printf("Report Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go back.\n\n");
                            printf("\n\n\t\t\t\t\t\t\t=========================================\n");
                            printf("\t\t\t\t\t\t\t Generate Student / Class report\n");
                            printf("\t\t\t\t\t\t\t=========================================\n");
                            printf("\n\n\t\t\t\t\t\t\t 1. Pay Sallary \n");
                            printf("\n\t\t\t\t\t\t\t 2. List Sallary Report\n");
                            printf("\n\t\t\t\t\t\t\tEnter your choice: ");
                            scanf("%d", &ch);
                            switch (ch)
                            {
                            case 0:
                                goto admin;
                                break;
                            case 1:
                                paySalary();
                                break;
                            case 2:
                                listSalaryStatus();
                                break;
                            default:
                                printf("\n\t\t\t\tInvalid Choice...\n\n");
                            }
                            getchar();
                            getchar();
                            break;
                        default:
                            printf("\n\t\tInvalid Choice...\n\n");
                        }
                        getchar();
                        printf("\n\n\t\t\t\t\t\t\tPress Any Key To Continue...");
                        getchar();
                        break;
                    }
                    break;

                case 2:
                    while (1)
                    {
                         strcpy(role, "Accountant");
                         login(role);
                        accountantmenu();
                        printf("\n\t\t\t\t\t\tEnter your choice: ");
                        scanf("%d", &ch);

                        switch (ch)
                        {
                        case 0:
                            goto landingPage; /// using goto
                            break;
                        case 1:
                            Departmentlist();
                            break;
                        case 2:
                            addStudent();
                            break;
                        case 3:
                            Studentlist();
                            break;
                        case 4:
                            DeleteStudent();
                            break;
                        case 5:
                            payFees();
                            break;
                        case 6:
                            listFeesStatus();
                            break;
                        case 7:
                            AttendanceList();
                            break;
                        case 8:
                            Subjectlist();
                            break;
                        case 9:
                            Classlist();
                            break;
                        case 10:
                            EmployeeList();
                            break;
                        case 11:
                            generateReport();
                            break;
                        case 12:
                            list_students_and_total_revenue(filename);
                            break;
                        default:
                            printf("\n\t\tInvalid Choice...\n\n");
                        }
                        getchar();
                        printf("\n\n\t\t\t\t\t\t\tPress Any Key To Continue...");
                        getchar();

                        break;
                    }
                    break;

                case 3:
                    while (1)
                    {
                         strcpy(role, "Teacher");
                          login(role);
                        teachermenu();
                        printf("\n\t\t\t\t\t\tEnter your choice: ");
                        scanf("%d", &ch);

                        switch (ch)
                        {
                        case 0:
                            goto landingPage; /// using goto
                            break;
                        case 1:
                            Departmentlist();
                            break;
                        case 2:
                            Studentlist();
                            break;
                        case 3:
                            markAttendance();
                            break;
                        case 4:
                            AttendanceList();
                            break;
                        case 5:
                            system("cls");
                            printf("Exam Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go back.\n\n");
                            printf("\n\n\t\t\t\t\t\t\t=========================================\n");
                            printf("\t\t\t\t\t\t\t  ADD /UPDATE / DELETE EXAM Details\n");
                            printf("\t\t\t\t\t\t\t=========================================\n");
                            printf("\n\n\t\t\t\t\t\t\t 1. Add New Examination\n");
                            printf("\n\t\t\t\t\t\t\t 2.Update Examination\n");
                            printf("\n\t\t\t\t\t\t\t 3. Delete Examination\n");
                            printf("\n\t\t\t\t\t\t\tEnter your choice: ");
                            scanf("%d", &ch);
                            switch (ch)
                            {
                            case 0:
                                goto admin;
                                break;
                            case 1:
                                addExam();
                                break;
                            case 2:
                                updateExam();
                                break;
                            case 3:
                                deleteExam();
                                break;
                            default:
                                printf("\n\t\t\t\tInvalid Choice...\n\n");
                            }
                            getchar();
                            getchar();
                            break;
                        case 6:
                            examlist();
                            break;
                        case 7:
                            addMarks();
                            break;
                        case 8:
                            updateMarks();
                            break;
                        case 9:
                            deleteMarks();
                            break;
                        case 10:
                            displayMarksBystudent_id();
                            break;
                        case 11:
                            Subjectlist();
                            break;
                        case 12:
                            Classlist();
                            break;
                        case 13:
                            EmployeeList();
                            break;
                        case 14:
                            listFeesStatus();
                            break;
                        case 15:
                            listSalaryStatus();
                            break;
                        default:
                            printf("\n\t\tInvalid Choice...\n\n");
                        }
                        getchar();
                        printf("\n\n\t\t\t\t\t\t\tPress Any Key To Continue...");
                        getchar();

                        break;
                    }
                    break;

                default:
                    printf("\n\t\t\t\t\t\tInvalid Choice...\n\n");
                }
            }
            break;

        case 3:
            while (1)
            {
                 strcpy(role, "Student");
                     login(role);

                studentmenu();
                printf("\n\t\t\t\t\t\tEnter your choice: ");
                scanf("%d", &ch);

                switch (ch)
                {
                case 0:
                    goto landingPage; /// using goto
                    break;
                case 1:
                    admissionLetter();
                    break;
                case 2:
                    Departmentlist();
                    break;
                case 3:
                    listFeesStatus();
                    break;
                case 4:
                    Subjectlist();
                    break;
                case 5:
                    Classlist();
                    break;
                case 6:
                    displayMarksBystudent_id();
                    break;
                default:
                    printf("\n\t\t\t\t\t\tInvalid Choice...\n\n");
                }
                getchar();
                printf("\n\n\t\t\t\t\t\t\tPress Any Key To Continue...");
                getchar();
            }
            break;
        case 101:
        {
            signup();
        }
        default:
            printf("\n\t\t\t\t\t\tInvalid  Choice...\n\n");
        }
    }

    return 0;
}