#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "appointment.h"

void addAppointment()
{
    appointment A;


    printf("Type the appointment id:\n");
    scanf("%d",&A.appointment_id);
    while(getchar()!='\n'); // clear input buffer

    printf("Type the patients ID:\n");
    scanf("%d",&A.patient_id);
    while(getchar()!='\n'); // clear input buffer

    printf("Type the doctors ID:\n");
    scanf("%d",&A.doctor_id); 
    while(getchar()!='\n'); // clear input buffer

    printf("Type the date of the appointment (DD-MM-YYYY):\n");
    fgets(A.date,sizeof(A.date),stdin);   
    A.date[strcspn(A.date,"\n")] = '\0';

    printf("Type the time of the appointment (HH:MM):\n");
    fgets(A.time,sizeof(A.time),stdin);   
    A.time[strcspn(A.time,"\n")] = '\0';

    printf("Type the reason of the appointment:\n");
    fgets(A.reason,sizeof(A.reason),stdin);   
    A.reason[strcspn(A.reason,"\n")] = '\0';

    FILE *ptr = fopen("Appointments.dat","ab");
    if(ptr==NULL)
    {
        printf("File couldn't open;\n");
        return;
    }

    fwrite(&A,sizeof(appointment),1,ptr);
    fclose(ptr);

    printf("Appointment added succesfully:\n");
}

void viewAppointments()
{
    FILE *ptr=fopen("Appointments.dat","rb");
    if(ptr==NULL)
    {
        printf("No appointment records found\n");
        return;
    }

    appointment A;
    while(fread(&A,sizeof(appointment),1,ptr))
    {
        printf("\n---Appointment Data---\n");
        printf("Appointment ID :%d\n",A.appointment_id);
        printf("Patient ID     : %d\n", A.patient_id);
        printf("Doctors ID     : %d\n", A.doctor_id);
        printf("Date           : %s\n", A.date);
        printf("Time           : %s\n", A.time);
        printf("Reason         : %s\n", A.reason);
        printf("---------END---------\n");
    }

    fclose(ptr);
}

void searchAppointments()
{
    appointment A;
    int ID,found=0;
    printf("Type the appointment ID:\n");
    scanf("%d",&ID);

    FILE *ptr = fopen("Appointments.dat","rb");
    if(ptr==NULL)
    {
        printf("File wasnt found\n");
        return;
    }

    while(fread(&A,sizeof(appointment),1,ptr))
    {
        if(A.appointment_id==ID)
        {
        found = 1;

        printf("\n---Appointment Data---\n");
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

    fclose(ptr);

    if(found == 0)
    {
        printf("No appointments found with this ID\n");
    }
}