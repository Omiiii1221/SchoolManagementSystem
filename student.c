// student.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // for Windows sleep
#include <unistd.h>  // for Linux sleep
#include <ctype.h>   // toupper

#include "student.h"
#include "class.h"
#include "generateStudentId.h"

FILE *fp;
struct Student S;

void addStudent()
{
    system("cls");
    char myDate[12];
    char capital[50];
    int i;
    printf("\n\n\t\t\t\t\t\t\t\t<== Add Student ==>\n\n");

    // Note
    printf("\n\t\t\t\t\t\t\t*NOTE: Please use capital letters..\n\n\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(S.date, myDate);
    getchar();

    int lastid = getlastStudent_id();
    S.student_id = generateStudent_id(lastid);
    saveStudent_id(S.student_id);
    printf("\n\t\t\t\t\t\t\tStudent ID: %d\n", S.student_id);

    printf("\n\n\t\t\t\t\t\t\tEnter Student's Name: ");
    fgets(S.Studentname, sizeof(S.Studentname), stdin);
    S.Studentname[strcspn(S.Studentname, "\n")] = '\0';

    printf("\n\t\t\t\t\t\t\tEnter Student's Address: ");
    fgets(S.studentAddress, sizeof(S.studentAddress), stdin);
    S.studentAddress[strcspn(S.studentAddress, "\n")] = '\0';

    printf("\n\t\t\t\t\t\t\tEnter Student's Phone No: ");
    fgets(S.S_phone, sizeof(S.S_phone), stdin);
    S.S_phone[strcspn(S.S_phone, "\n")] = '\0';
    getchar();

    printf("\n\t\t\t\t\t\t\tEnter Student's Class: ");
    fgets(S.Studentclass, sizeof(S.Studentclass), stdin);
    S.Studentclass[strcspn(S.Studentclass, "\n")] = '\0';

    // Convert class to upper case
    for (i = 0; S.Studentclass[i] != '\0'; i++)
    {
        capital[i] = toupper(S.Studentclass[i]);
    }
    capital[i] = '\0';
    strcpy(S.Studentclass, capital);

    // Fetch tuition fee from class file
    struct Class C;
    int class_found = 0;
    fp = fopen("C:\\SMS\\Class.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tUnable to open class file\n");
        return;
    }
    while (fread(&C, sizeof(C), 1, fp) == 1)
    {
        if (strcmp(C.class_name, S.Studentclass) == 0)
        {
            S.fees_due = C.tuitionfee;
            class_found = 1;
            break;
        }
    }
    fclose(fp);

    if (!class_found)
    {
        printf("\n\t\t\t\t\t\t\tClass not found. Please add the class first.\n");
        printf("\n\t\t\t\t\t\t\tRedirecting to add class...");
        sleep(5);   // sleep will pause terminal for desired seconds
        addClass(); // it will redirect user to add class
        return;
    }

    S.fees_paid = 0.0;

    fp = fopen("C:\\SMS\\Student.txt", "ab");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tUnable to open file\n");
        return;
    }

    fwrite(&S, sizeof(S), 1, fp);
    fclose(fp);

    printf("\n\t\t\t\t\t\t\tStudent Added Successfully\n");
}

void updateStudent()
{
    system("cls");
    int student_id, found = 0;
    char capital[50];
    int i;

    printf("\n\n\n\t\t\t\t\t\t\t\t<== Update Student ==>\n\n");
    printf("\n\t\t\t\t\t\t\tEnter Student ID to Update: ");
    scanf("%d", &student_id);
    getchar();

    FILE *fp_temp = fopen("C:\\SMS\\temp.txt", "wb");
    if (fp_temp == NULL)
    {
        printf("\n\t\t\t\t\t\t\tUnable to open temporary file\n");
        return;
    }

    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        perror("\n\t\t\t\t\t\t\tUnable to open file\n");
        fclose(fp_temp);
        return;
    }

    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        if (S.student_id == student_id)
        {
            found = 1;
            printf("\n\t\t\t\t\t\t\tUpdating details for Student ID: %d\n", student_id);

            printf("\n\t\t\t\t\t\t\tEnter New Student's Name: ");
            fgets(S.Studentname, sizeof(S.Studentname), stdin);
            S.Studentname[strcspn(S.Studentname, "\n")] = '\0';

            printf("\n\t\t\t\t\t\t\tEnter New Student's Address: ");
            fgets(S.studentAddress, sizeof(S.studentAddress), stdin);
            S.studentAddress[strcspn(S.studentAddress, "\n")] = '\0';

            printf("\n\t\t\t\t\t\t\tEnter New Student's Phone No: ");
            fgets(S.S_phone, sizeof(S.S_phone), stdin);
            S.S_phone[strcspn(S.S_phone, "\n")] = '\0';
            getchar();

            printf("\n\t\t\t\t\t\t\tEnter New Student's Class: ");
            fgets(S.Studentclass, sizeof(S.Studentclass), stdin);
            S.Studentclass[strcspn(S.Studentclass, "\n")] = '\0';

            // Convert class to upper case
            for (i = 0; S.Studentclass[i] != '\0'; i++)
            {
                capital[i] = toupper(S.Studentclass[i]);
            }
            capital[i] = '\0';
            strcpy(S.Studentclass, capital);
            
            // Fetch new tuition fee from class file
            struct Class C;
            int class_found = 0;
            FILE *fp_class = fopen("C:\\SMS\\Class.txt", "rb");
            if (fp_class == NULL)
            {
                printf("\t\t\t\t\t\t\tUnable to open class file\n");
                fclose(fp_temp);
                fclose(fp);
                return;
            }
            while (fread(&C, sizeof(C), 1, fp_class) == 1)
            {
                if (strcmp(C.class_name, S.Studentclass) == 0)
                {
                    S.fees_due = C.tuitionfee;
                    class_found = 1;
                    break;
                }
            }
            fclose(fp_class);

            if (!class_found)
            {
                printf("\n\t\t\t\t\t\t\tClass not found. Please add the class first.\n");
                fclose(fp_temp);
                fclose(fp);
                printf("\n\t\t\t\t\t\t\tRedirecting to add class...");
                sleep(5);   // sleep will pause terminal for desired seconds
                addClass(); // it will redirect user to add class
                return;
            }
        }
        fwrite(&S, sizeof(S), 1, fp_temp);
    }

    fclose(fp);
    fclose(fp_temp);

    if (found)
    {
        printf("\n\t\t\t\t\t\t\tStudent Updated Successfully.\n");
        remove("C:\\SMS\\Student.txt");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\Student.txt");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tStudent ID Not Found.\n");
        remove("C:\\SMS\\temp.txt");
    }
}

void DeleteStudent()
{
    system("cls");
    int student_id, found = 0;
    printf("\n\n\n\t\t\t\t\t\t\t\t<== Delete Student ==>\n\n");
    printf("\n\t\t\t\t\t\t\tEnter Student ID to Delete: ");
    scanf("%d", &student_id);
    getchar();

    FILE *ft = fopen("C:\\SMS\\temp.txt", "wb");
    if (ft == NULL)
    {
        perror("\n\t\t\t\t\t\t\tUnable to open temporary file\n");
        return;
    }

    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        perror("\n\t\t\t\t\t\t\tUnable to open file\n");
        fclose(ft);
        return;
    }

    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        if (student_id == S.student_id)
        {
            found = 1;
        }
        else
        {
            fwrite(&S, sizeof(S), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    if (found)
    {
        printf("\n\n\t\t\t\t\t\t\tStudent Deleted Successfully.\n");
        remove("C:\\SMS\\Student.txt");
        rename("C:\\SMS\\temp.txt", "C:\\SMS\\Student.txt");
    }
    else
    {
        printf("\n\n\t\t\t\t\t\t\tStudent ID Not Found.\n");
        remove("C:\\SMS\\temp.txt");
    }
}

void Studentlist()
{
    system("cls");
    struct Student S;
    printf("\n\n\t\t\t\t\t\t\t\t<== Student List ==>\n\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("%-15s  %-30s %-35s %-15s %-20s %-12s %-10s %-10s\n", "Student_id", "Student Name", "Address", "Contact No", "Class", "Date", "Fees Due", "Fees Paid");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Student.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\tError opening file.\n");
        printf("\n\n\t\t\t\t\t\tRedirecting to add student...");
        sleep(5);     // sleep will pause terminal for desired seconds
        addStudent(); // it will redirect user to add student
        return;
    }

    while (fread(&S, sizeof(struct Student), 1, fp) == 1)
    {
        printf("%-15d  %-30s %-35s %-15s %-20s %-12s %-10.2f %-10.2f\n", S.student_id, S.Studentname, S.studentAddress, S.S_phone, S.Studentclass, S.date, S.fees_due, S.fees_paid);
    }

    fclose(fp);
    getchar();
}

void admissionLetter()
{
    int studentID;
    struct Class C;
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t\t\t<== Admission Letter ==>\n\n");
    printf("\n\t\t\t\t\t\t\tEnter Student ID: ");
    scanf("%d", &studentID);
    getchar();

    fp = fopen("C:\\SMS\\Student.txt", "rb");
    int found = 0;
    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        if (S.student_id == studentID)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
    {
        FILE *fp_class = fopen("C:\\SMS\\Class.txt", "rb");
        int class_found = 0;
        while (fread(&C, sizeof(C), 1, fp_class) == 1)
        {
            if (strcmp(C.class_name, S.Studentclass) == 0)
            {
                class_found = 1;
                break;
            }
        }
        fclose(fp_class);

        if (class_found)
        {
            printf("\n\t\t\t\t\t\t\t\t---ADMISSION CONFIRMATION---\n");
            printf("\t\t\t\t\t\t\tStudent ID : %d\n", S.student_id);
            printf("\t\t\t\t\t\t\tClass : %s\n", C.class_name);
            printf("\t\t\t\t\t\t\tAdmission Date : %s\n", S.date);
            printf("\t\t\t\t\t\t\tAccount Status : Active\n");
        }
        else
        {
            printf("\n\n\t\t\t\t\t\t\tClass Record Not Found!");
            printf("\n\n\t\t\t\t\t\t\tRedirecting to add class...");
            sleep(5);   // sleep will pause terminal for desired seconds
            addClass(); // it will redirect user to add class
        }
    }
    else
    {
        printf("\n\n\t\t\t\t\t\t\tStudent Record Not Found!");
    }
    getchar();
}

void classList()
{
    system("cls");
    struct Class C;
    printf("\n\n\t\t\t\t\t\t\t\t\t<== Class List ==>\n\n");
    printf("\n\n\t\t\t\t\t\t\t%-10s  %-30s %-10s %-30s\n", "Class_id", "Class Name", "Tuition Fee", "Teacher ID");
    printf("\n\n\t\t\t\t\t\t\t---------------------------------------------------------------------------------\n");

    fp = fopen("C:\\SMS\\Class.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\n\t\t\t\t\t\t\tError opening file\n");
        printf("\n\n\t\t\t\t\t\t\tRedirecting to add class...");
        sleep(5);   // sleep will pause terminal for desired seconds
        addClass(); // it will redirect user to add class
        return;
    }

    while (fread(&C, sizeof(C), 1, fp) == 1)
    {
        printf("\t\t\t\t\t\t\t%-10d  %-30s %-10d %-30d\n", C.class_id, C.class_name, C.tuitionfee, C.teacher_id);
    }
    printf("\n\n\t\t\t\t\t\t\t--------------------------------------------------------------------------------\n");

    fclose(fp);
    getchar();
}
