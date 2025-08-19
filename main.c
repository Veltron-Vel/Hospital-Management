#include <direct.h>
#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"
#include "billing.h"

int login();
void showAdminMenu();
void showUserMenu();

int main()
{
    _mkdir("data");
    int access = login();

    if (access == 1)
    {
        printf("\nLogin successful. Welcome to Hospital Management System!\n");
        showAdminMenu();
    }
    else if (access == -1)
    {
        printf("\nInvalid password. Access denied");
        return -1;
    }
    else
    {
        printf("\nWelcome to Hospital Management System!\n");
        showUserMenu();
    }
    return 0;
}

int login()
{
    int user;
    char password[20];
    printf("-----LOGIN-----\n");
    printf("Log in as:\n");
    printf("1. Admin\n");
    printf("2. User\n");
    scanf("%d", &user);
    while(getchar() != '\n');
    
    if (user == 1)
    {
        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        if (strcmp(password, "12345678") == 0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else if (user == 2)
    {
        return 0;
    }
}

void showAdminMenu()
{
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
        while (getchar() != '\n');

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

void showUserMenu()
{
    int choice;
    do
    {
        printf("\n-----HOSPITAL MANAGEMENT SYSTEM-----\n");
        printf("1. Search patient by ID\n");
        printf("2. View available doctors\n");
        printf("3. Search appointment by ID\n");
        printf("4. Search billing by ID\n");
        printf("5. Exit\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch(choice)
        {
            case 1:
                searchPatient();
                break;
            case 2:
                viewDoctor();
                break;
            case 3:
                searchAppointment();
                break;
            case 4:
                searchBill();
                break;
            case 5:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Try again...\n");
        }
    } while (choice != 5);
}
