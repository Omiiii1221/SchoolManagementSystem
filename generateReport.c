#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
#include "marks.h"
#include <windows.h>

// Pre-defining grade cutoffs
#define CUTOFF_1ST_DIV 60.0
#define CUTOFF_2ND_DIV 50.0
#define CUTOFF_3RD_DIV 40.0

// Function to convert string to uppercase
void toUpperCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

// Function to generate report cards for students
void generateReport()
{
    system("cls");
    FILE *studentFile = fopen("C:\\SMS\\Student.txt", "rb");
    FILE *marksFile = fopen("C:\\SMS\\marks.csv", "r");

    if (!studentFile || !marksFile)
    {
        printf("\t\t\t\t\t\tUnable to open file for generating report\n");
        if (studentFile)
            fclose(studentFile);
        if (marksFile)
            fclose(marksFile);
        return;
    }

    int inputStudentID;
    char inputClassName[50];

    // getting input for student ID and class name
    printf("\n\n\n\n\n\n\t\t\t\t\t\tEnter Student ID: ");
    scanf("%d", &inputStudentID);
    getchar();

    printf("\n\t\t\t\t\t\tEnter Class Name: ");
    fgets(inputClassName, sizeof(inputClassName), stdin);
    inputClassName[strcspn(inputClassName, "\n")] = '\0';
    toUpperCase(inputClassName);

    struct Student student;
    int totalMarks;
    int subjectsCount;
    float percentage;
    char grade[15];

    printf("\n\n\n\n\n\n\t\t\t\t\t\t=========================================\n");
    printf("\t\t\t\t\t\t             Report\n");
    printf("\t\t\t\t\t\t=========================================\n");

    // Reading student data
    int studentFound = 0;
    while (fread(&student, sizeof(student), 1, studentFile))
    {
        if (student.student_id == inputStudentID && strcmp(student.Studentclass, inputClassName) == 0)
        {
            studentFound = 1;
            printf("\t\t\t\t\t\tStudent ID: %d\n", student.student_id);
            printf("\t\t\t\t\t\tName: %s\n", student.Studentname);
            printf("\t\t\t\t\t\tMobile Number: %s\n", student.S_phone);

            totalMarks = 0;    // Reset total marks for each student
            subjectsCount = 0; // Reset subjects count for each student

            // Reading marks data
            char line[256];
            while (fgets(line, sizeof(line), marksFile))
            {
                int studentId;
                sscanf(line, "%d", &studentId);

                if (studentId == student.student_id)
                {
                    char *token = strtok(line, ",");
                    int i = 0;
                    while (token != NULL)
                    {
                        if (i > 0)
                        { // Skip the first token which is the student ID
                            float mark;
                            if (sscanf(token, "%f", &mark) == 1 && mark >= 0)
                            {
                                totalMarks += mark;
                                subjectsCount++;
                            }
                        }
                        token = strtok(NULL, ",");
                        i++;
                    }
                    break;
                }
            }
            rewind(marksFile); // Reset file pointer to beginning of marks file

            // Calculate percentage if there are subjects
            if (subjectsCount > 0)
            {
                percentage = (float)totalMarks / subjectsCount;

                // Determine grade based on percentage
                if (percentage >= CUTOFF_1ST_DIV)
                {
                    strcpy(grade, "1st Division");
                }
                else if (percentage >= CUTOFF_2ND_DIV)
                {
                    strcpy(grade, "2nd Division");
                }
                else if (percentage >= CUTOFF_3RD_DIV)
                {
                    strcpy(grade, "3rd Division");
                }
                else
                {
                    strcpy(grade, "Fail");
                }

                printf("\t\t\t\t\t\tTotal Marks: %d\n", totalMarks);
                printf("\t\t\t\t\t\tPercentage: %.2f%%\n", percentage);
                printf("\t\t\t\t\t\tGrade: %s\n", grade);
                printf("\t\t\t\t\t\t-----------------------------------------\n\n");
            }
            else
            {
                printf("\t\t\t\t\t\tNo marks found for the student.\n");
                printf("\t\t\t\t\t\t-----------------------------------------\n\n");
            }
            break;
        }
    }

    if (!studentFound)
    {
        printf("\t\t\t\t\t\tNo student found with ID %d in class %s.\n", inputStudentID, inputClassName);
        printf("\t\t\t\t\t\t-----------------------------------------\n\n");
    }

    // Closing both files
    fclose(studentFile);
    fclose(marksFile);
}


void generateClassReport() {
    system("cls");
    FILE *studentFile = fopen("C:\\SMS\\Student.txt", "rb");
    FILE *marksFile = fopen("C:\\SMS\\marks.csv", "r");
    FILE *subjectFile = fopen("C:\\SMS\\Subject.txt", "r");

    if (!studentFile || !marksFile || !subjectFile) {
        printf("\t\t\t\t\t\tUnable to open file for generating report\n");
        if (studentFile) fclose(studentFile);
        if (marksFile) fclose(marksFile);
        if (subjectFile) fclose(subjectFile);
        return;
    }

    char inputClassName[50];
    printf("\n\n\n\n\n\n\t\t\t\t\t\tEnter Class Name: ");
    fgets(inputClassName, sizeof(inputClassName), stdin);
    inputClassName[strcspn(inputClassName, "\n")] = '\0'; // Remove trailing newline
    toUpperCase(inputClassName);

getchar();
    struct Student student;
    char subjects[MAX_SUBJECTS][50];
    int subjCount = 0;
    char line[256];

    // Read subjects for the class
    while (fgets(line, sizeof(line), subjectFile)) {
        int subject_id, teacher_id;
        char subjClassName[50], subjName[50];
        sscanf(line, "%d,%[^,],%[^,],%d", &subject_id, subjClassName, subjName, &teacher_id);
        toUpperCase(subjClassName);

        if (strcmp(subjClassName, inputClassName) == 0) {
            strcpy(subjects[subjCount++], subjName);
        }
    }
    fclose(subjectFile);

    printf("\n\n\n\n\n\n\t\t\t\t\t\t====================================================================\n");
    printf("\t\t\t\t\t\t                           Class Report for %s\n", inputClassName);
    printf("\t\t\t\t\t\t====================================================================\n");

    int classFound = 0;

    // Reading marks data
    while (fgets(line, sizeof(line), marksFile)) {
        int studentId;
        sscanf(line, "%d", &studentId);

        // Get student details from Student.txt
        int studentFound = 0;
        rewind(studentFile); // Reset file pointer to beginning of student file
        while (fread(&student, sizeof(student), 1, studentFile)) {
            if (student.student_id == studentId && strcmp(student.Studentclass, inputClassName) == 0) {
                studentFound = 1;
                classFound = 1;
                printf("%-10d %-20s", student.student_id, student.Studentname);

                int totalMarks = 0;    // Reset total marks for each student
                int subjectsCount = 0; // Reset subjects count for each student

                char *token = strtok(line, ",");
                int i = 0;
                while (token != NULL) {
                    if (i > 0) { // Skip the first token which is the student ID
                        float mark;
                        if (sscanf(token, "%f", &mark) == 1 && mark >= 0) {
                            printf("%10.2f", mark);
                            totalMarks += mark;
                            subjectsCount++;
                        } else {
                            printf("%10s", "N/A");
                        }
                    }
                    token = strtok(NULL, ",");
                    i++;
                }

                // Calculate percentage if there are subjects
                if (subjectsCount > 0) {
                    float percentage = (float)totalMarks / subjectsCount;
                    printf("%10d %10.2f%%\n", totalMarks, percentage);
                } else {
                    printf("%10s\n", "No marks found");
                }
                break;
            }
        }

        if (!studentFound) {
            printf("No student found with ID %d in class %s.\n", studentId, inputClassName);
        }
    }

    if (!classFound) {
        printf("\t\t\t\t\t\tNo students found in class %s.\n", inputClassName);
    }

    // Closing both files
    fclose(studentFile);
    fclose(marksFile);
    getchar();
    getchar();
}
