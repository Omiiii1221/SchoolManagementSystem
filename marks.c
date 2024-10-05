#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include "marks.h"
#include "class.h"
#include "subjects.h"
#include "student.h"
#include "generateReport.h"

#define MAX_SUBJECTS 10
void displayMarksBystudent_id();
// Function to save marks to a CSV file
void saveMarksToCSV(const char *filename, struct Marks *M)
{
    FILE *fp = fopen(filename, "a");
    if (!fp)
    {
        printf("\t\t\t\t\t\t\tUnable to open file for writing marks\n");
        return;
    }

    fprintf(fp, "%d", M->Studentid);
    for (int i = 0; i < MAX_SUBJECTS; i++)
    {
        if (M->marks[i] >= 0)
        {
            fprintf(fp, ",%.2f", M->marks[i]);
        }
        else
        {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n");

    fclose(fp);
}

// Function to add marks for a student
void addMarks()
{
addMarksAgain:

    system("cls");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t<== Add Marks ==>\n\n");

    struct Marks M;
    printf("\n\t\t\t\t\t\t\tEnter Student ID: ");
    scanf("%d", &M.Studentid);

    FILE *fp = fopen("C:\\SMS\\Student.txt", "r");
    if (M.Studentid != S.student_id)
    {
        printf("\n\t\t\t\t\t\t\tStudent not found..");
        printf("\n\t\t\t\t\t\t\tRedirecting to add marks in 2 sec..");
        sleep(2);
        goto addMarksAgain;
    }

    printf("\n\t\t\t\t\t\t\tEnter Class Name: ");
    scanf(" %[^\n]s", M.class_name);
    toUpperCase(M.class_name);

    FILE *subjectFile = fopen("C:\\SMS\\Subject.txt", "r");
    if (!subjectFile)
    {
        printf("\t\t\t\t\t\t\tUnable to open Subject file for reading\n");
        return;
    }

    int classFound = 0;
    printf("\n\t\t\t\t\t\t\tEnter marks for each subject:\n\n");
    int i = 0;
    memset(M.marks, -1, sizeof(M.marks)); // Initialize marks array with -1
    printf("\n\t\t\t\t\t\t\t-----------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), subjectFile))
    {
        int subject_id, teacher_id;
        char subjClassName[50];
        char subjName[50];

        sscanf(line, "%d,%[^,],%[^,],%d", &subject_id, subjClassName, subjName, &teacher_id);

        toUpperCase(subjClassName);

        if (strcmp(subjClassName, M.class_name) == 0)
        {
            classFound = 1;
            printf("\t\t\t\t\t\t\t%-30s: ", subjName);
            float marks;
            scanf("%f", &marks);

            if (i < MAX_SUBJECTS)
            {
                M.marks[i++] = marks;
            }
            else
            {
                break;
            }
        }
    }
    fclose(subjectFile);
    printf("\n\t\t\t\t\t\t\t-----------------------------------------\n");

    if (!classFound)
    {
        printf("\t\t\t\t\t\t\tNo subjects found for this class\n");
        return;
    }

    saveMarksToCSV("C:\\SMS\\marks.csv", &M);
    printf("\n\n\t\t\t\t\t\t\tMarks added successfully!\n");
}

// update marks

void updateMarks()
{
    system("cls");
    FILE *fp, *temp;
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t<== Update Marks ==>\n\n");

    struct Marks M;
    printf("\n\t\t\t\t\t\t\tEnter Student ID: ");
    scanf("%d", &M.Studentid);

    printf("\n\t\t\t\t\t\t\tEnter Class Name: ");
    scanf(" %[^\n]s", M.class_name);
    toUpperCase(M.class_name);

    fp = fopen("C:\\SMS\\marks.csv", "r");
    temp = fopen("C:\\SMS\\temp.txt", "w");

    if (!fp || !temp)
    {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp))
    {
        struct Marks tempMarks;
        char *token = strtok(line, ",");
        tempMarks.Studentid = atoi(token);
        token = strtok(NULL, ",");
        strcpy(tempMarks.class_name, token);
        toUpperCase(tempMarks.class_name);

        int i = 0;
        while ((token = strtok(NULL, ",")) != NULL && i < MAX_SUBJECTS)
        {
            tempMarks.marks[i++] = atof(token);
        }

        if (tempMarks.Studentid == M.Studentid && strcmp(tempMarks.class_name, M.class_name) == 0)
        {
            found = 1;
            printf("\n\t\t\t\t\t\t\tEnter marks for each subject:\n\n");
            for (i = 0; i < MAX_SUBJECTS; i++)
            {
                printf("\t\t\t\t\t\t\tSubject %d: ", i + 1);
                scanf("%f", &tempMarks.marks[i]);
            }
        }

        fprintf(temp, "%d,%s", tempMarks.Studentid, tempMarks.class_name);
        for (int j = 0; j < MAX_SUBJECTS; j++)
        {
            fprintf(temp, ",%.2f", tempMarks.marks[j]);
        }
        fprintf(temp, "\n");
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("C:\\SMS\\marks.csv");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\marks.csv");
        printf("\n\n\t\t\t\t\t\t\tMarks updated successfully!\n");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tStudent ID or Class Name not found.\n");
        remove("C:\\SMS\\temp.txt");
    }
}

// Function to display marks from CSV
void displayMarksFromCSV(const char *filename, int studentId, const char *className)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("\t\t\t\t\t\t\tUnable to open marks file for reading\n");
        return;
    }

    FILE *subjectFile = fopen("C:\\SMS\\Subject.txt", "r");
    if (!subjectFile) {
        printf("\t\t\t\t\t\t\tUnable to open Subject file for reading\n");
        fclose(fp);
        return;
    }

    char subjectNames[MAX_SUBJECTS][50];
    int subjectCount = 0;
    char line[256];

    // Reading subject names of the  class
    while (fgets(line, sizeof(line), subjectFile)) {
        int subject_id, teacher_id, totelMarks;
        char subjClassName[50];
        char subjName[50];

       
        sscanf(line, "%d,%[^,],%[^,],%d,%d", &subject_id, subjClassName, subjName, &teacher_id, &totelMarks);
        toUpperCase(subjClassName);

        if (strcmp(subjClassName, className) == 0) {
            strcpy(subjectNames[subjectCount++], subjName);
        }
    }
    fclose(subjectFile);

    if (subjectCount == 0) {
        printf("\t\t\t\t\t\t\tNo subjects found for this class\n");
        fclose(fp);
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        int id;
        sscanf(line, "%d", &id);
        if (id == studentId) {
            found = 1;
            printf("\t\t\t\t\t\t\tStudent ID: %d\n", id);
            char *token = strtok(line, ",");
            int i = 0;

        
            while (token != NULL) {
                if (i > 0 && i <= subjectCount) { 
                    printf("\n\t\t\t\t\t\t\t%-30s:\t%.2f", subjectNames[i - 1], atof(token));
                }
                token = strtok(NULL, ",");
                i++;
            }
            break;
        }
    }

    if (!found) {
        printf("\t\t\t\t\t\t\tMarks with Student ID %d not found.\n", studentId);
    }

    fclose(fp);
}


// Function to display marks by student ID
void displayMarksBystudent_id()
{
    system("cls");
    int studentId;
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tEnter Student ID: ");
    if (scanf("%d", &studentId) != 1) {
        printf("\n\t\t\t\t\t\t\tInvalid input. Please enter a valid Student ID.\n");
        return;
    }
    getchar(); 

    printf("\n\t\t\t\t\t\t\tEnter Class Name: ");
    char className[50];
    fgets(className, sizeof(className), stdin);
    className[strcspn(className, "\n")] = '\0'; // remove trailing newline
    toUpperCase(className);

    printf("\n\n\t\t\t\t\t\t\t=========================================\n");
    printf("\t\t\t\t\t\t\t          Marks Details\n");
    printf("\t\t\t\t\t\t\t=========================================\n");

    displayMarksFromCSV("C:\\SMS\\marks.csv", studentId, className);

    printf("\n\t\t\t\t\t\t\t-----------------------------------------\n");
}

// to delete marks of student by its id
void deleteMarks()
{
    system("cls");
    FILE *fp, *temp;
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t<== Delete Marks ==>\n\n");

    int studentId;
    printf("\n\t\t\t\t\t\t\tEnter Student ID to delete: ");
    scanf("%d", &studentId);

    fp = fopen("C:\\SMS\\marks.csv", "r");
    temp = fopen("C:\\SMS\\temp.txt", "w");

    if (!fp || !temp)
    {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp))
    {
        struct Marks tempMarks;
        char *token = strtok(line, ",");
        tempMarks.Studentid = atoi(token);
        token = strtok(NULL, ",");
        strcpy(tempMarks.class_name, token);

        int i = 0;
        while ((token = strtok(NULL, ",")) != NULL && i < MAX_SUBJECTS)
        {
            tempMarks.marks[i++] = atof(token);
        }

        if (tempMarks.Studentid == studentId)
        {
            found = 1;
            continue; // Skip this line (do not write it to temp file)
        }

        fprintf(temp, "%d,%s", tempMarks.Studentid, tempMarks.class_name);
        for (int j = 0; j < MAX_SUBJECTS; j++)
        {
            fprintf(temp, ",%.2f", tempMarks.marks[j]);
        }
        fprintf(temp, "\n");
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("C:\\SMS\\marks.csv");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\marks.csv");
        printf("\n\n\t\t\t\t\t\t\tMarks deleted successfully!\n");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tStudent ID not found.\n");
        remove("C:\\SMS\\temp.txt");
    }
}

// int main() {
//     addMarks();
//     displayMarksBystudent_id();
//     return 0;
// }
