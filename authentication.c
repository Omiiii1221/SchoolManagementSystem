#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h> // For getch()
#include "authentication.h"
#include <unistd.h> // for Linux sleep
#include <windows.h>

// Function to get user input securely for password
void get_password(char *password, int maxLength)
{
    int i = 0;
    char ch;
    while (i < maxLength - 1 && (ch = getch()) != '\r')
    {
        if (ch == '\b' && i > 0)
        { // Handle backspace
            printf("\b \b");
            i--;
        }
        else if (ch != '\b')
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}

// Function to sign up
void signup()
{
    system("cls");
    FILE *fp = fopen("C:\\SMS\\Authentication.csv", "a");
    if (!fp)
    {
        perror("\n\n\t\t\tUnable to open file for writing");
        return;
    }

    struct user user;
    // getchar(); // Clear buffer

    printf("\n\t\t\t\t\t\t\tEnter your full Name: ");
    fgets(user.fullname, sizeof(user.fullname), stdin);
    user.fullname[strcspn(user.fullname, "\n")] = 0;

    printf("\n\t\t\t\t\t\t\tEnter Date of Birth (YYYY-MM-DD): ");
    fgets(user.dob, sizeof(user.dob), stdin);
    user.dob[strcspn(user.dob, "\n")] = 0;

    printf("\n\t\t\t\t\t\t\tEnter Mobile Number: ");
    fgets(user.mobileNumber, sizeof(user.mobileNumber), stdin);
    user.mobileNumber[strcspn(user.mobileNumber, "\n")] = 0;

    printf("\n\t\t\t\t\t\t\tEnter your Email id: ");
    fgets(user.emailid, sizeof(user.emailid), stdin);
    user.emailid[strcspn(user.emailid, "\n")] = 0;

    printf("\n\t\t\t\t\t\t\tEnter gender: ");
    fgets(user.gender, sizeof(user.gender), stdin);
    user.gender[strcspn(user.gender, "\n")] = 0;

    printf("\n\t\t\t\t\t\t\tEnter username: ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = 0;

    printf("\n\t\t\t\t\t\t\tEnter Password: ");
    get_password(user.password, sizeof(user.password));

    printf("\n\t\t\t\t\t\t\tEnter role (Admin/principal/Accountant/Teacher/Student): ");
    fgets(user.role, sizeof(user.role), stdin);
    user.role[strcspn(user.role, "\n")] = 0;

    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", user.fullname, user.dob, user.mobileNumber, user.emailid, user.gender, user.username, user.password, user.role);
    fclose(fp);
    printf("\n\n\t\t\t\t\t\t\tUser added successfully!\n");
    printf("\n\n\t\t\t\t\t\t\tlogging in!\n");
}

// Function to log in
void login(const char *role)
{
    
    struct user user;
    char username[50], password[50];
    int found = 0;

    getchar(); // Clear buffer

    printf("\n\n\n\t\t\t\t\t\tEnter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("\n\n\t\t\t\t\t\tEnter Password: ");
    get_password(password, sizeof(password));

    FILE *fp = fopen("C:\\SMS\\Authentication.csv", "r");
    if (!fp)
    {
        perror("\n\n\t\t\t\t\t\t\tUnable to open file for reading");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%49[^,],%11[^,],%12[^,],%49[^,],%9[^,],%19[^,],%19[^,],%19s",
               user.fullname, user.dob, user.mobileNumber, user.emailid, user.gender,
               user.username, user.password, user.role);

        if (strcmp(user.username, username) == 0 &&
            strcmp(user.password, password) == 0 &&
            strcmp(user.role, role) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
    {
        printf("\n\n\t\t\t\t\t\tLogin successful.\n");
    }
    else
    {
        printf("\n\n\t\t\t\t\t\tInvalid username, password, or role.\n");
        printf("\n\n\t\t\t\t\t\tRedirecting to sign up.\n");
        sleep(2);
        signup();
        getchar();
    }
}
// int main()
// {
//     int choice;
//     char role[20];
//     printf("1. Sign up\n");
//     printf("2. Log in\n");
//     printf("Enter your choice: ");
//     scanf("%d", &choice);

//     switch (choice)
//     {
//     case 1:
//         signup();
//         break;
//     case 2:

//         printf("Enter your role (admin/principal/Accountant/Teacher/student): ");
//         scanf("%s", role);
//         login(role);
//         break;
//     default:
//         printf("Invalid choice\n");
//     }

//     return 0;
// }