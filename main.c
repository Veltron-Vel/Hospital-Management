#include <direct.h>
#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"
#include "billing.h"

int login();
void showMenu();

int main()
{
    if (login() == 0)
    {
        return 0;
    }
    showMenu();
    return 0;
}

int login()
{
    char username[20], password[20];
    printf("-----LOGIN-----\n");

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, "admin001") == 0 && strcmp(password, "12345678") == 0)
    {
        printf("Login successful!\n");
        return 1;
    }
    else
    {
        printf("Login failed!\n");
        return 0;
    }
}

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
