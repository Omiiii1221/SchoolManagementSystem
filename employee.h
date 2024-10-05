//employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

struct Employee
{
    int employee_id;
    char name[50];
    char position[50];
    float salary;
    float salary_paid;
};

void addEmployee();
void EmployeeList();
void DeleteEmployee();

#endif
