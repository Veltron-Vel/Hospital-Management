#ifndef APPOINTMENT_H
#define APPOINTMENT_H

typedef struct appointment
{
    int appointment_id;
    int patient_id;
    int doctor_id;
    char date[20];   // Format: DD-MM-YYYY
    char time[10];    // Format: HH:MM
    char reason[200];
} Appointment;

void addAppointment();
void viewAppointment();
void searchAppointment();
void deleteAppointment();
void appointmentMenu();

#endif
