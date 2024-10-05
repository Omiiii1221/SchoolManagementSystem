//Attendance.h
#ifndef ATTENDANCE_H
#define ATTENDANCE_H

struct Attendance
{
    int student_id;
    char date[12];
    char status;
};

void markAttendance();
void AttendanceList();

#endif
