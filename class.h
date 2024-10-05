//class.h

#ifndef CLASS_H
#define CLASS_H

struct Class
{
    int class_id;
    char class_name[50];
    int teacher_id;
    float tuitionfee;
};

void addClass();
void Classlist();
void DeleteClass();
void classes_with_Subjects();
#endif
