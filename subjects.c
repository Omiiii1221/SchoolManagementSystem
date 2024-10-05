// subjects.c
// This file contains functions related to subjects:
// Add subjects, list subjects, delete subjects

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjects.h"
#include <windows.h> // For Windows Sleep
#include <unistd.h>  // For Linux Sleep
#include "generateReport.h"

FILE *fp;

void addSubject()
{
    system("cls");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t<== Add Subjects ==>\n\n");

    fp = fopen("C:\\SMS\\Subject.txt", "a");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tUnable to open file\n");
        return;
    }

    Subject Sub;

    printf("\n\t\t\t\t\t\t\tEnter Subject ID: ");
    scanf("%d", &Sub.subject_id);

    printf("\n\t\t\t\t\t\t\tEnter Class Name: ");
    scanf(" %[^\n]s", Sub.class_name);
    toUpperCase(Sub.class_name);

    printf("\n\t\t\t\t\t\t\tEnter Subject Name: ");
    scanf(" %[^\n]s", Sub.subject_name);

    printf("\n\t\t\t\t\t\t\tEnter Teacher ID: ");
    scanf("%d", &Sub.teacher_id);

    printf("\n\t\t\t\t\t\t\tEnter Totel Marks for %s: ", Sub.subject_name);
    scanf("%d", &Sub.Totel_sub_marks);

    fprintf(fp, "%d,%s,%s,%d,%d\n", Sub.subject_id, Sub.class_name, Sub.subject_name, Sub.teacher_id,Sub.Totel_sub_marks);
    fclose(fp);

    printf("\n\n\t\t\t\t\t\t\tSubject Added Successfully.\n");
}

// Function to list all subjects
void Subjectlist()
{
    system("cls");
    printf("\n\t\t\t\t\t\t\t\t<== List of Subjects ==>\n\n");
    printf("\t\t\t\t\t\t%-15s %-25s %-25s %-10s\n", "Subject ID", "Class Name", "Subject Name", "Teacher ID");
    printf("\t\t\t\t\t\t----------------------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Subject.txt", "r");
    if (fp == NULL)
    {
        perror("\n\t\t\t\t\t\t\tUnable to open file");
        printf("\n\n\t\t\t\t\t\tRedirecting to add subject...");
        sleep(5);     // Sleep will pause terminal for desired seconds
        addSubject(); // Redirect user to add subject
        return;
    }

    Subject Sub;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d,%[^,],%[^,],%d", &Sub.subject_id, Sub.class_name, Sub.subject_name, &Sub.teacher_id);
        printf("\t\t\t\t\t\t%-10d %-30s %-30s %-10d\n", Sub.subject_id, Sub.class_name, Sub.subject_name, Sub.teacher_id);
    }

    fclose(fp);
    getchar();
}

// Function to delete a subject
void DeleteSubject()
{
    int subject_id, found = 0;
    system("cls");
    printf("\n\t\t\t\t\t\t\t\t<== Delete Subject ==>\n\n");
    printf("\n\t\t\t\t\t\t\tEnter Subject ID to Delete: ");
    scanf("%d", &subject_id);

    FILE *ft = fopen("C:\\SMS\\temp.txt", "w");
    if (ft == NULL)
    {
        perror("\n\t\t\t\t\t\t\tUnable to open temporary file");
        return;
    }

    fp = fopen("C:\\SMS\\Subject.txt", "r");
    if (fp == NULL)
    {
        perror("\n\t\t\t\t\t\t\tUnable to open file");
        fclose(ft);
        return;
    }

    Subject Sub;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d,%[^,],%[^,],%d", &Sub.subject_id, Sub.class_name, Sub.subject_name, &Sub.teacher_id);
        if (subject_id == Sub.subject_id)
        {
            found = 1;
        }
        else
        {
            fprintf(ft, "%d,%s,%s,%d\n", Sub.subject_id, Sub.class_name, Sub.subject_name, Sub.teacher_id);
        }
    }

    fclose(fp);
    fclose(ft);

    if (found)
    {
        printf("\n\n\t\t\t\t\t\t\tSubject Deleted Successfully.\n");
        remove("C:\\SMS\\Subject.txt");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\Subject.txt");
    }
    else
    {
        printf("\n\n\t\t\t\t\t\t\tSubject Not Found.\n");
        remove("C:\\SMS\\temp.txt");
    }
}
