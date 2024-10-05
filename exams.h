
#ifndef EXAMS_H
#define EXAMS_H

struct exams
{
    char examName[50];
    char startingDate[12];
    char endingDate[12];
};

void addExam();
void examlist();
void updateExam();
void deleteExam();
#endif // EXAMS_H