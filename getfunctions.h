// this file will have funs that will gatter info about totals

//getfunctions.h

#ifndef GETFUNCTIONS_H
#define GETFUNCTIONS_H

 void makefolder();
 
// func to count how many students are present and how many are absent for day
void get_current_date(char *current_date);

// this func gets count of total students from file student.txt
void count_attendance(const char *attendance_filename, int *total_present, int *total_absent);

// this func gets count of total teachers from file teachers.txt
int get_total_employees(const char *filename);

// Function to get the total number of paid employees
int get_total_paid_employees(const char *filename);

// Function to get the total number of unpaid employees
int get_total_unpaid_employees(const char *filename);

int get_total_students(const char *filename);

void get_total_students_enrolled_in_Class();

//this func will print totel revenue
int get_total_Revenue(const char *filename);
// void Classlist();
void payFees();

void listFeesStatus();
// void TeacherList();
void studentmenu();

void list_students_and_total_revenue(const char *filename);
#endif 