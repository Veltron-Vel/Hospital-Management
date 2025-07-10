#ifndef PATIENTS_H
#define PATIENTS_H


typedef struct patient
{
    char name[50];
    int age;
    char gender;
    int id;
    char disease[30];
}patient;


void addPatient();
void viewPatient();
void searchPatient();

#endif