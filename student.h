//student.h

#ifndef STUDENT_H
#define STUDENT_H

struct Student
{
    int student_id;
    char Studentname[50];
    char studentAddress[50];
    char S_phone[11];
    char Studentclass[50];
    char date[12];
    char subject_name[50];
    float fees_due;
    float fees_paid;
} S;

void addStudent();
void updateStudent();
void DeleteStudent();
void Studentlist();
void admissionLetter();


#endif // STUDENT_H
