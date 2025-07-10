#ifndef APPOINTMENT_H
#define APPOINTMENT_H

typedef struct appointment
{
    int appointment_id;
    int patient_id;
    int doctor_id;
    char date[11];   /// Format: DD-MM-YYYY
    char time[6];    /// Formart: HH:MM
    char reason[200];
} appointment;


void addAppointment();
void viewAppointments();
void searchAppointments();

#endif