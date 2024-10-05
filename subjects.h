//Subjects.h
#ifndef SUBJECTS_H
#define SUBJECTS_H

typedef struct
{
    int subject_id;
    char class_name[50];
    char subject_name[50];
    int teacher_id;
    int Totel_sub_marks;
} Subject;

void addSubject();
void Subjectlist();
void DeleteSubject();

#endif
