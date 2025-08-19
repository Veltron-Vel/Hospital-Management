#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"
#define FILE_PATH "data/appointment.txt"

void appointmentMenu()
{
    int choice;
    do
    {
        printf("\n-----APPOINTMENT MANAGEMENT-----\n");
        printf("1. Add appointment\n");
        printf("2. View appointment(s)\n");
        printf("3. Search appointment by ID\n");
        printf("4. Delete appointment\n");
        printf("5. Return to main menu\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                addAppointment();
                break;
            case 2:
                viewAppointment();
                break;
            case 3:
                searchAppointment();
                break;
            case 4:
                deleteAppointment();
                break;
            case 5:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice. Try again...\n");
        }
    } while (choice != 5);
}

int patientExists(int targetpid)
{
    Patient p;
    FILE *fp = fopen("data/patient.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &p.id, &p.name, &p.age, &p.gender, &p.disease) == 5)
    {
        if (targetpid == p.id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int doctorExists(int targetdid)
{
    Doctor d;
    FILE *fp = fopen("data/patient.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &d.id, &d.name, &d.age, &d.gender, &d.specialty) == 5)
    {
        if (targetdid == d.id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addAppointment()
{
    FILE *fp = fopen(FILE_PATH, "a");
    if(fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    Appointment A;
    printf("Enter appointment id: ");
    scanf("%d", &A.appointment_id);
    while (getchar() != '\n');

    printf("Enter patient's ID: ");
    scanf("%d", &A.patient_id);
    while (getchar() != '\n');

    if (patientExists(A.patient_id) != 1)
    {
        printf("Error: Patient not found\n");
        fclose(fp);
        return;
    }

    printf("Enter the doctors ID: ");
    scanf("%d", &A.doctor_id);
    while (getchar() != '\n');

    if (doctorExists(A.doctor_id) != 1)
    {
        printf("Error: doctor not found\n");
        fclose(fp);
        return;
    }

    printf("Enter appointment date (DD-MM-YYYY): ");
    fgets(A.date, sizeof(A.date), stdin);
    A.date[strcspn(A.date, "\n")] = '\0';

    printf("Enter appointment time (HH:MM): ");
    fgets(A.time, sizeof(A.time), stdin);
    A.time[strcspn(A.time, "\n")] = '\0';

    printf("Enter reason for appointment: ");
    fgets(A.reason, sizeof(A.reason), stdin);
    A.reason[strcspn(A.reason, "\n")] = '\0';

    fprintf(fp, "%d|%d|%d|%s|%s|%s\n", A.appointment_id, A.patient_id, A.doctor_id, A.date, A.time, A.reason);
    fclose(fp);

    printf("Appointment added successfully!\n");
}

void viewAppointment()
{
    FILE *fp = fopen(FILE_PATH, "r");
    if(fp == NULL)
    {
        printf("No appointment records found\n");
        return;
    }

    Appointment A;
    printf("\n-----Appointment Data-----\n");
    while(fscanf(fp, "%d|%d|%d|%19[^|]|%9[^|]|%199[^\n]\n", &A.appointment_id, &A.patient_id, &A.doctor_id, &A.date, &A.time, &A.reason) == 6)
    {
        printf("Appointment ID: %d\n", A.appointment_id);
        printf("Patient ID    : %d\n", A.patient_id);
        printf("Doctors ID    : %d\n", A.doctor_id);
        printf("Date          : %s\n", A.date);
        printf("Time          : %s\n", A.time);
        printf("Reason        : %s\n", A.reason);
        printf("\n");
    }
    printf("---------END---------\n");

    fclose(fp);
}

void searchAppointment()
{
    Appointment A;
    int ID, found = 0;
    
    FILE *fp = fopen(FILE_PATH, "r");
    if(fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    printf("Enter appointment ID: ");
    scanf("%d", &ID);
    while (getchar() != '\n');

    while(fscanf(fp, "%d|%d|%d|%10[^|]|%5[^|]|%199[^\n]\n", &A.appointment_id, &A.patient_id, &A.doctor_id, &A.date, &A.time, &A.reason) == 6)
    {
        if(ID == A.appointment_id)
        {
        found = 1;

        printf("\n-----APPOINTMENT DATA-----\n");
        printf("Appointment ID :%d\n",A.appointment_id);
        printf("Patient ID     : %d\n", A.patient_id);
        printf("Doctors ID     : %d\n", A.doctor_id);
        printf("Date           : %s\n", A.date);
        printf("Time           : %s\n", A.time);
        printf("Reason         : %s\n", A.reason);
        printf("---------END---------\n");

        break;
        }
    }

    fclose(fp);

    if(found == 0)
    {
        printf("No appointment found with this ID\n");
    }
}

void deleteAppointment()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    printf("Enter appointment ID: ");
    scanf("%d", &targetID);
    while (getchar() != '\n');
    Appointment A;
    while(fscanf(fp, "%d|%d|%d|%10[^|]|%5[^|]|%199[^\n]\n", &A.appointment_id, &A.patient_id, &A.doctor_id, &A.date, &A.time, &A.reason) == 6)
    {
        if (targetID == A.appointment_id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d|%d|%d|%s|%s|%s\n", A.appointment_id, A.patient_id, A.doctor_id, A.date, A.time, A.reason);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("data/appointment.txt");
    rename("data/temp.txt", "data/appointment.txt");

    if (found == 1)
    {
        printf("Appointment deleted successfully!\n");
    }
    else
    {
        printf("Appointment not found\n");
    }
}
