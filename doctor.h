#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct doctor
{
    char name[30];
    int id;
    int age;
    char gender;
    char speciality[30];
    int experience;
} doctor;

void addDoctor();
void viewDoctors();
void searchDoctor();

#endif