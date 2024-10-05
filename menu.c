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
#include "generateReport.h"
#include "authentication.h"
#include "menus.h"

void get_current_date(char *current_date);
void count_attendance(const char *attendance_filename, int *total_present, int *total_absent);
int get_total_students(const char *filename);
int get_total_employees(const char *filename);
int get_total_paid_employees(const char *filename);
int get_total_unpaid_employees(const char *filename);

void landingPage() // home
{
    system("cls");
    printf("Home...\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t 0 to Exit.\n\n");
    printf("\n\n\t\t\t\t\t\t# if you dont have account yet choose 101....");
    printf("\n\n\n\n\t\t\t\t\t\t<------------------------------------------------------------->\n");
    printf("\t\t\t\t\t\t\t\t<== School Management System ==> \n");
    printf("\t\t\t\t\t\t<------------------------------------------------------------->\n");
    printf("\n\n\t\t\t\t\t\t\t\t\t\tI Am\n");
    printf("\n\n\n\t\t\t\t\t\t1. Admin \t\t2. Employee \t\t3. Student\n");
    printf("\n\n\t\t\t\t\t\tEnter your choice: ");
}

void Adminmenu()
{
    system("cls");
    char student_filename[] = "C:\\SMS\\Student.txt";
    char attendance_filename[] = "C:\\SMS\\Attendance.txt";
    char subject_filename[] = "C:\\SMS\\Subject.txt";
    char employee_filename[] = "C:\\SMS\\Employee.txt";

    int total_students = get_total_students(student_filename);
    int total_employees = get_total_employees(employee_filename);
    int total_present, total_absent;
    int total_paid = get_total_paid_employees(employee_filename);
    int total_unpaid = get_total_unpaid_employees(employee_filename);
    float total_revenue = get_total_Revenue(student_filename);

    count_attendance(attendance_filename, &total_present, &total_absent);
    printf("Admin Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");

    printf("\n\n\n\n\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t<== School Management System ==>\t\t\t\t\t|\t\t<== Admin Dashboard ==> \t\t|\n");
    printf("\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n\n");

    printf("1. Add Department\t\t");
    printf("2. Department List\t\t");
    printf("3. Delete Department\t\t|Total Students: %d| |Total Present: %d| |Total Absent: %d|\n\n", total_students, total_present, total_absent);
    printf("4. Add Student\t\t\t");
    printf("5. Student List\t\t\t");
    printf("6. Delete Student\t\t|Total Employees:%d |                                    |\n\n", total_employees);
    printf("7. Update Student\t\t");
    printf("8. Add Attendance\t\t");
    printf("9. Attendance List\t\t|-------------------------------------------------------|\n\n");
    printf("10. Add Subject\t\t\t");
    printf("11. Subject List\t\t");
    printf("12. Delete Subject\n\n");
    printf("13. Add Class\t\t\t");
    printf("14. Class List\t\t\t");
    printf("15. Delete Class\t\t\t\t\t|  <===   Revenue   ===> |\n\n");
    printf("16. Add Employee\t\t");
    printf("17. List Employees\t\t");
    printf("18. Delete Employee\t\t\t\t\t| Total Revenue : %.2f|\n\n", total_revenue);
    printf("19. Pay Fees\t\t\t");
    printf("20. List Fee Status\t\t");
    printf("21. Add/Update/Delete Exam\n\n");
    printf("22. list Exams\t\t\t");
    printf("23. Add Marks\t\t\t");
    printf("24. Update  Marks\n\n");
    printf("25. Delete Marks\t\t");
    printf("26. Display Marks\t\t");
    printf("27. generate Report's\n\n");
    printf("28. Pay Salary\t\t\t");
    printf("29. List Salary Status\n\n");
    printf("30. Revenue Report\t\t\t\t\t\t\t\t\t\t\t\t\t|  <===   Salaries  ===> |\n\n");
    printf("0. Exit\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t| Paid :%d |  | Unpaid :%d |\n\n", total_paid, total_unpaid);
}

void principlemenu()
{
    system("cls");
    char student_filename[] = "C:\\SMS\\Student.txt";
    char attendance_filename[] = "C:\\SMS\\Attendance.txt";
    char subject_filename[] = "C:\\SMS\\Subject.txt";
    char employee_filename[] = "C:\\SMS\\Employee.txt";

    int total_students = get_total_students(student_filename);
    int total_employees = get_total_employees(employee_filename);
    int total_present, total_absent;
    int total_paid = get_total_paid_employees(employee_filename);
    int total_unpaid = get_total_unpaid_employees(employee_filename);

    count_attendance(attendance_filename, &total_present, &total_absent);
    printf("Principal's Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");

    printf("\n\n\n\n\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t<== School Management System ==>\t\t\t\t\t|\t\t<== Principal's Dashboard ==> \t\t|\n");
    printf("\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n\n");

    printf("1. Add Department\t\t");
    printf("2. Department List\t\t");
    printf("3. Delete Department\t\t|Total Students: %d| |Total Present: %d| |Total Absent: %d|\n\n", total_students, total_present, total_absent);
    printf("4. Add Student\t\t\t");
    printf("5. Student List\t\t\t");
    printf("6. Delete Student\t\t|Total Employees:%d|                                    |\n\n", total_employees);
    printf("7. Generate Report\t\t");
    printf("8. Add Attendance\t\t");
    printf("9. Attendance List\n\n");
    printf("10. Add Subject\t\t\t");
    printf("11. Subject List\t\t");
    printf("12. Delete Subject\t\t|-------------------------------------------------------|\n\n");
    printf("13. Add Class\t\t\t");
    printf("14. Class List\t\t\t");
    printf("15. List Employees\t\t|-------------------------------------------------------|\n\n");
    printf("16. Pay Fees\t\t\t");
    printf("17. List Fee Status\t\t");
    printf("18. Pay/List Salary Status\t\t\t\t|  <===  Salaries  ===> |\n\n");
    printf("0. Exit\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t| Paid :%d |  | Unpaid :%d |\n\n", total_paid, total_unpaid);
}

void accountantmenu()
{
    system("cls");
    char student_filename[] = "C:\\SMS\\Student.txt";
    char attendance_filename[] = "C:\\SMS\\Attendance.txt";
    char subject_filename[] = "C:\\SMS\\Subject.txt";
    char employee_filename[] = "C:\\SMS\\Employee.txt";

    int total_students = get_total_students(student_filename);
    int total_employees = get_total_employees(employee_filename);
    int total_present, total_absent;
    int total_paid = get_total_paid_employees(employee_filename);
    int total_unpaid = get_total_unpaid_employees(employee_filename);

    count_attendance(attendance_filename, &total_present, &total_absent);
    printf("Accountant's Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");

    printf("\n\n\n\n\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t<== School Management System ==>\t\t\t\t\t|\t\t<== Accountant's Dashboard ==> \t\t|\n");
    printf("\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n\n");
    printf("1. Department List\t\t");
    printf("2. Add Student\t\t");
    printf("3. Student List\t\t\t\t|Total Students: %d| |Total Present: %d| |Total Absent: %d|\n\n", total_students, total_present, total_absent);
    printf("4. Delete Student\t\t");
    printf("5. Pay Fees\t\t");
    printf("6. List Fee Status\t\t\t|Total Employees:%d|                                   |\n\n", total_employees);
    printf("7. Attendance List\t\t");
    printf("8. Subject List\t\t");
    printf("9. Employee List\t\t\t|-------------------------------------------------------|\n\n");
    printf("10. Pay Fees\t\t\t");
    printf("11. Generate Report\t");
    printf("12. Totel Revenue\t\t\t\t\t\t|  <===  Salaries  ===> |\n\n");
    printf("0. Exit\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t| Paid :%d |  | Unpaid :%d |\n\n", total_paid, total_unpaid);
}

void teachermenu()
{
    system("cls");
    char student_filename[] = "C:\\SMS\\Student.txt";
    char employee_filename[] = "C:\\SMS\\Employee.txt";
    char attendance_filename[] = "C:\\SMS\\Attendance.txt";
    char subject_filename[] = "C:\\SMS\\Subject.txt";

    int total_students = get_total_students(student_filename);
    int total_employees = get_total_employees(employee_filename);
    int total_present, total_absent;
    printf("Teacher's Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");

    count_attendance(attendance_filename, &total_present, &total_absent);
    printf("\n\n\n\n\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t<== School Management System ==>\t\t\t\t\t|\t\t<== Teacher's Dashboard ==> \t\t|\n");
    printf("\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n\n");

    printf("1. Department List\t\t");
    printf("2. Student List\t\t\t");
    printf("3. add Attendance\t\t|Total Students: %d| |Total Present: %d| |Total Absent: %d|\n\n", total_students, total_present, total_absent);
    printf("4. Attendance List\t\t");
    printf("5. Add/Update/Delete Exam\t");
    printf("6. Exam's List\t\t\t|-------------------------------------------------------|\n\n");
    printf("7. Add Marks\t\t\t");
    printf("8. Update Marks\t\t\t");
    printf("9. Delete Marks\n\n");
    printf("10. Display Marks\t\t");
    printf("11. Subject List\t\t");
    printf("12. Class List\t\t\t\t\t|  <===  Salaries  ===> |\n\n");
    printf("13. Employee List\t\t");
    printf("14. List Fee Status\t\t");
    printf("15. List Salary Status\t\t\t\t| Paid :%d |  | Unpaid :%d |\n\n", get_total_paid_employees(employee_filename), get_total_unpaid_employees(employee_filename));
    printf("0. Exit\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
}

void EmployeeMenu()
{
    system("cls");
    char student_filename[] = "C:\\SMS\\Student.txt";
    char employee_filename[] = "C:\\SMS\\Employee.txt";
    char attendance_filename[] = "C:\\SMS\\Attendance.txt";
    char subject_filename[] = "C:\\SMS\\Subject.txt";

    int total_students = get_total_students(student_filename);
    int total_employees = get_total_employees(employee_filename);
    int total_present, total_absent;
    printf("Employee Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");

    count_attendance(attendance_filename, &total_present, &total_absent);
    printf("\n\n\n\n\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t<== School Management System ==>\t\t\t\t\t|\t\t<== Employee Dashboard ==> \t\t|\n");
    printf("\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n\n");

    printf("1. Department List\t\t");
    printf("2. Add Student\t\t\t");
    printf("3. Student List\t\t\t|Total Students: %d| |Total Present: %d| |Total Absent: %d|\n\n", total_students, total_present, total_absent);
    printf("4. Add Attendance\t\t");
    printf("5. Attendance List\t\t");
    printf("6. Subject List\t\t\t|-------------------------------------------------------|\n\n");
    printf("7. Pay Fees\t\t\t");
    printf("8. List Fee Status\t\t");
    printf("9. Pay Salary\n\n");
    printf("10. List Salary Status\t\t\t\t\t\t\t\t\t\t\t\t\t|  <===  Salaries  ===> |\n\n");
    printf("0. Exit\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t| Paid :%d |  | Unpaid :%d |\n\n", get_total_paid_employees(employee_filename), get_total_unpaid_employees(employee_filename));
}

void studentmenu()
{
    system("cls");
    printf("Student's Dashboard...\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChoose 0 to go Home.\n\n");

    printf("\n\n\n\n\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t<== School Management System ==>\t\t\t\t\t|\t\t<== Student's Dashboard ==> \t\t|\n");
    printf("\t---------------------------------------------------------------\t\t\t\t|-------------------------------------------------------|\n\n");
    printf("1. Admisssion Letter\t\t");
    printf("2. Department List\t\t");
    printf("3. Fee Status\n");
    printf("4. subject list\t\t\t");
    printf("5. class list \t\t\t");
    printf("6. view Report Card\n");
    printf("0. Exit\n\n");
}