// generete student id
// we want to generate student id as +1 to last id given to any student
// to achive this we will make 1 new file called student id and
// we save all ids in  it

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"
#include <windows.h>// for windows sleep
#include <unistd.h>// for linux sleep

FILE *fp;

struct S;

// this will save ids to file by making a file called student id
void saveStudent_id(int new_id)
{
    // opening file in append mode
    // a  means if we dont have file it will amke a new file and
    fp = fopen("C:\\SMS\\student_ids.txt", "a");
    if (fp == NULL)
    {
        perror("\n\t\t\t\t\t\tUnable to open file");
        return;
    }
    // saving new id at file
    fprintf(fp, "%d\n", new_id);
    fclose(fp); // closing file
}

// func to get last id from file student id
//
int getlastStudent_id()
{
    int lastid = 0; // 0 at start  basically it will save last student id
    // opening file in read
    fp = fopen("C:\\SMS\\student_ids.txt", "r");
    if (fp == NULL)
    {

        return lastid;
    }

    while (fscanf(fp, "%d", &lastid) == 1)
    {
    }
    fclose(fp);
    return lastid;
}

//  this will generate id by adding 1 to last id
int generateStudent_id(int lastid)
{
    return lastid + 1;
}
// int main()
// {
//     addStudent();
//     return 0;
// }
