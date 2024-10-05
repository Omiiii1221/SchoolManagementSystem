// exams.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <unistd.h> // for Linux sleep

#include "generateReport.h"
#include "exams.h"

struct exams E;
FILE *fp;

void addExam()
{
    system("cls");
    fp = fopen("C:\\SMS\\exams.txt", "a");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tError opening file");
        return;
    }
    printf("\n\n\t\t\t\t\t\t\t=========================================\n");
    printf("\t\t\t\t\t\t\t          Add Examination\n");
    printf("\t\t\t\t\t\t\t=========================================\n");

    printf("\n\n\t\t\t\t\t\t\tEnter Examination Name: ");
    fgets(E.examName, sizeof(E.examName), stdin);
    E.examName[strcspn(E.examName, "\n")] = '\0';
    getchar();

    printf("\n\t\t\t\t\t\t\tEnter Starting Date (DD/MM/YYYY): ");
    fgets(E.startingDate, sizeof(E.startingDate), stdin);
    E.startingDate[strcspn(E.startingDate, "\n")] = '\0';
    getchar();

    printf("\n\t\t\t\t\t\t\tEnter Ending Date (DD/MM/YYYY): ");
    fgets(E.endingDate, sizeof(E.endingDate), stdin);
    E.endingDate[strcspn(E.endingDate, "\n")] = '\0';
    getchar();
    printf("\n\n\t\t\t\t\t\t%s Exam Added Successfully\n", E.examName);
    fwrite(&E, sizeof(E), 1, fp);
    fclose(fp);
    getchar();
}

void examlist()
{
    system("cls");
    struct exams E;
    printf("\n\n\t\t\t\t\t\t\t\t\t<== Exam's List ==>\n\n");
    printf("\t\t\t\t\t\t--------------------------------------------------------------------------------\n");

    printf("\t\t\t\t\t\t%-30s %-35s %-25s\n", "exam Name", "Starting Date", "Ending Date");
    printf("\t\t\t\t\t\t--------------------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\exams.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\tError opening file.\n");
        printf("\n\n\t\t\t\t\t\tRedirecting to add exam...");
        sleep(5);  // sleep will pause terminal for desired seconds
        addExam(); // it will redirect user to add exam
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1)
    {
        printf("\t\t\t\t\t\t%-30s %-35s %-25s\n", E.examName, E.startingDate, E.endingDate);
    }

    fclose(fp);
    getchar();
}

void updateExam()
{
    system("cls");
    char examName[100];
    int found = 0;
    printf("\n\n\t\t\t\t\t\t\t=========================================\n");
    printf("\t\t\t\t\t\t\t          Update Examination Details\n");
    printf("\t\t\t\t\t\t\t=========================================\n");
    printf("\n\t\t\t\t\t\t\tEnter Examination Name to Update: ");
    fgets(examName, sizeof(examName), stdin);
    examName[strcspn(examName, "\n")] = '\0';
    getchar();
    FILE *temp;
    fp = fopen("C:\\SMS\\exams.txt", "rb");
    temp = fopen("C:\\SMS\\temp.txt", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\n\t\t\t\t\t\tError opening file.\n");
        return;
    }
    while (fread(&E, sizeof(E), 1, fp) == 1)
    {
        if (strcmp(E.examName, examName) == 0)
        {
            found = 1;
            printf("\n\t\t\t\t\t\t\tEnter New Examination Name: ");
            fgets(E.examName, sizeof(E.examName), stdin);
            E.examName[strcspn(E.examName, "\n")] = '\0';
            getchar();

            printf("\n\t\t\t\t\t\t\tEnter New Starting Date: ");
            fgets(E.startingDate, sizeof(E.startingDate), stdin);
            E.startingDate[strcspn(E.startingDate, "\n")] = '\0';
            getchar();

            printf("\n\t\t\t\t\t\t\tEnter New Ending Date: ");
            fgets(E.endingDate, sizeof(E.endingDate), stdin);
            E.endingDate[strcspn(E.endingDate, "\n")] = '\0';
            getchar();

            printf("\n\n\t\t\t\t\t\t%s Exam Updated Successfully\n", E.examName);
            getchar();
        }
        fwrite(&E, sizeof(E), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("C:\\SMS\\exams.txt");
    rename("C:\\SMS\\temp.txt", "C:\\SMS\\exams.txt");

    if (!found)
    {
        printf("\n\t\t\t\t\t\tNo Exam Found with the Name %s\n", examName);
        getchar();
    }
    getchar();
}

void deleteExam()
{
    system("cls");
    char examName[100];
    int found = 0;

    printf("\n\n\t\t\t\t\t\t\t=========================================\n");
    printf("\t\t\t\t\t\t\t          Delete Examination Details\n");
    printf("\t\t\t\t\t\t\t=========================================\n");
    printf("\n\t\t\t\t\t\t\tEnter Examination Name to Delete: ");
    fgets(examName, sizeof(examName), stdin);
    examName[strcspn(examName, "\n")] = '\0';
    getchar();
    FILE *temp;
    fp = fopen("C:\\SMS\\exams.txt", "rb");
    temp = fopen("C:\\SMS\\temp.txt", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\n\t\t\t\t\t\tError opening file.\n");
        return;
    }

    while (fread(&E, sizeof(E), 1, fp) == 1)
    {
        if (strcmp(E.examName, examName) != 0)
        {
            fwrite(&E, sizeof(E), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("C:\\SMS\\exams.txt");
    rename("C:\\SMS\\temp.txt", "C:\\SMS\\exams.txt");

    if (found)
    {
        printf("\n\t\t\t\t\t\t%s Exam Deleted Successfully\n", examName);
    }
    else
    {
        printf("\n\t\t\t\t\t\tNo Exam Found with the Name %s\n", examName);
    }
}
