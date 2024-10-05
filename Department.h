#ifndef DEPARTMENT_H
#define DEPARTMENT_H

struct Department
{
    int id;
    char name[50];
};

void addDepartment();
void Departmentlist();
void DeleteDepartment();
// functions.h
void markAttendance();
void AttendanceList();
void payFees();
void listFeesStatus();
// void TeacherList();
void studentmenu();


#endif
