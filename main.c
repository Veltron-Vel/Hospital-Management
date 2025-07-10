#include <stdio.h>
#include "patients.h"
#include "doctor.h"
#include "appointment.h"
#include "billing.h"

int main()
{
    int input;

    while(1)
    {
        printf("\n------------Hospital Management System------------\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Add Doctor\n");
        printf("5. View Doctors\n");
        printf("6. Search Doctor by ID\n");
        printf("7. Add Appointment\n");
        printf("8. View Appointments\n");
        printf("9. Search Appointment by ID\n");
        printf("10. Add Billing\n");
        printf("11. View Billings\n");
        printf("12. Search Billings by patient ID\n");

        printf("0. Exit\n");

        printf("Type which function you want to use:\n");
        scanf("%d",&input);
        while(getchar()!='\n');

        switch(input)
        {
            case 1:
            addPatient();
            break;

            case 2:
            viewPatient();
            break;

            case 3:
            searchPatient();
            break;

            case 4:
            addDoctor();
            break;

            case 5:
            viewDoctors();
            break;

            case 6:
            searchDoctor();
            break;

            case 7:
            addAppointment();
            break;

            case 8:
            viewAppointments();
            break;

            case 9:
            searchAppointments();
            break;

            case 10:
            addBilling();
            break;

            case 11:
            viewBillings();
            break;

            case 12:
            searchBilling();
            break;

            case 0:
            printf("Exiting program\n");
            return 0;

            default:
            printf("Invalid choice, try again\n");
            break;            
        }
    }

    return 0;
}