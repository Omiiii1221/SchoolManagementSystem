// marks.h

#ifndef MARKS_H
#define MARKS_H
#define MAX_SUBJECTS 10

struct Marks {
    int Studentid;
    float marks[MAX_SUBJECTS];
   char class_name[50];
};

void addMarks();
void updateMarks();
void deleteMarks();
void displayMarksFromCSV(const char *filename, int studentId, const char *className);
void displayMarksBystudent_id();

#endif // MARKS_H