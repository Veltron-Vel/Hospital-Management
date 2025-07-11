#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char specialty[50];
} Doctor;

void addDoctor();
void viewDoctor();
void searchDoctor();
void deleteDoctor();
void doctorMenu();

#endif
