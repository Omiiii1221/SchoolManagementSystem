//authentication

#ifndef authentication_H
#define authentication_H

struct user
{
    char fullname[50];
    char gender[10];
    char emailid[50];
    char mobileNumber[13];
    char username[20];
    char password[30];
    char dob[12];
    char role[20];
};

struct temp
{
    char username[50];
    char password[50];
};

void signup();
void login(const char *requiredRole);

#endif // authentication_H