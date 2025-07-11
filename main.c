#include <direct.h>
#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"
#include "billing.h"

void showMenu()
{
    _mkdir("data"); //creates 'data' folder if it doesn't exist
    int choice;
    do
    {
        printf("\n-----HOSPITAL MANAGEMENT SYSTEM-----\n");
        printf("1. Patient Management\n");
        printf("2. Doctor management\n");
        printf("3. Appointment\n");
        printf("4. Billing\n");
        printf("5. Exit\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                patientMenu();
                break;
            case 2:
                doctorMenu();
                break;
            case 3:
                appointmentMenu();
                break;
            case 4:
                billingMenu();
                break;
            case 5:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Try again...\n");
        }
    } while (choice != 5);
}
int main()
{
    showMenu();
    return 0;
}
