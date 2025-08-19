#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"
#include "patient.h"
#include "appointment.h"
#define FILE_PATH "data/billing.txt"

void billingMenu()
{
    int choice;
    do
    {
        printf("\n-----BILLING MANAGEMENT-----\n");
        printf("1. Add bill\n");
        printf("2. View bill(s)\n");
        printf("3. Search bill by ID\n");
        printf("4. Update payment status\n");
        printf("5. Return to main menu\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBill();
                break;
            case 2:
                viewBill();
                break;
            case 3:
                searchBill();
                break;
            case 4:
                updateStatus();
                break;
            case 5:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice. Try again...\n");
        }
    } while (choice != 5);
}

int BpatientExists(int targetpid)
{
    Patient P;
    FILE *fp = fopen("data/patient.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &P.id, &P.name, &P.age, &P.gender, &P.disease) == 5)
    {
        if (targetpid == P.id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int appointmentExists(int targetaid)
{
    Appointment A;
    FILE *fp = fopen("data/appointment.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }

    while (fscanf(fp, "%d|%d|%d|%19[^|]|%9[^|]|%199[^\n]\n", &A.appointment_id, &A.patient_id, &A.doctor_id, &A.date, &A.time, &A.reason) == 6)
    {
        if (targetaid == A.appointment_id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addBill()
{
    FILE *fp = fopen(FILE_PATH, "a");

    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    Billing B;

    printf("Enter billing ID: ");
    scanf("%d", &B.billingID);
    while (getchar() != '\n');

    printf("Enter patient ID: ");
    scanf("%d", &B.patientID);
    while (getchar() != '\n');

    if (BpatientExists(B.patientID) != 1)
    {
        printf("Error: Patient not found\n");
        fclose(fp);
        return;
    }

    printf("Enter appointment ID: ");
    scanf("%d", &B.appointmentID);
    while (getchar() != '\n');

    if (appointmentExists(B.appointmentID) != 1)
    {
        printf("Error: Appointment not found\n");
        fclose(fp);
        return;
    }

    printf("Enter amount: ");
    scanf("%f", &B.amount);
    while (getchar() != '\n');

    printf("Enter payment status (Paid/Unpaid): ");
    fgets(B.paymentStatus, sizeof(B.paymentStatus), stdin);
    B.paymentStatus[strcspn(B.paymentStatus, "\n")] = '\0';

    fprintf(fp, "%d|%d|%d|%.2f|%s\n", B.billingID, B.patientID, B.appointmentID, B.amount, B.paymentStatus);
    fclose(fp);
    printf("Bill added successfully!\n");
}

void viewBill()
{
    FILE *fp = fopen(FILE_PATH, "r");
    int count = 0;
    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }
    Billing B;

    printf("\n-----BILLING RECORDS-----\n");
    while (fscanf(fp, "%d|%d|%d|%f|%19[^\n]\n", &B.billingID, &B.patientID, &B.appointmentID, &B.amount, &B.paymentStatus) == 5)
    {
        printf("Billing ID    : %d\n", B.billingID);
        printf("Patient ID    : %d\n", B.patientID);
        printf("Appointment ID: %d\n", B.appointmentID);
        printf("Amount        : %.2f\n", B.amount);
        printf("Payment Status: %s\n", B.paymentStatus);
        printf("\n");
        count++;
    }
    if (count > 0)
    {
        printf("-----END-----\n");
    }
    else
    {
        printf("No billing information found\n");
    }
        fclose(fp);
}

void searchBill()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");

    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }
    Billing B;

    printf("Enter bill ID: ");
    scanf("%d", &targetID);
    while (getchar() != '\n');

    while (fscanf(fp, "%d|%d|%d|%f|%19[^\n]\n", &B.billingID, &B.patientID, &B.appointmentID, &B.amount, &B.paymentStatus) == 5)
    {
        if (targetID == B.billingID)
        {
            found = 1;
            printf("\n-----BILLING INFORMATION-----\n");
            printf("Billing ID    : %d\n", B.billingID);
            printf("Patient ID    : %d\n", B.patientID);
            printf("Appointment ID: %d\n", B.appointmentID);
            printf("Amount        : %.2f\n", B.amount);
            printf("Payment Status: %s\n", B.paymentStatus);
            printf("-----END-----\n");
        }
    }
    fclose(fp);

    if (found = 0)
    {
        printf("Billing information not found\n");
    }
}

void updateStatus()
{
    int targetID, found = 0;
     FILE *fp = fopen(FILE_PATH, "r");
     FILE *temp = fopen("data/temp.txt", "w");

     if (fp == NULL || temp == NULL)
     {
        printf("Failed to open file\n");
        return;
     }
     Billing B;

     printf("Enter billing ID: ");
     scanf("%d", &targetID);
     while (getchar() != '\n');

     while (fscanf(fp, "%d|%d|%d|%f|%19[^\n]\n", &B.billingID, &B.patientID, &B.appointmentID, &B.amount, &B.paymentStatus) == 5)
     {
        if (targetID == B.billingID)
        {
            found = 1;
            printf("Enter new payment status: ");
            fgets(B.paymentStatus, sizeof(B.paymentStatus), stdin);
            B.paymentStatus[strcspn(B.paymentStatus, "\n")] = '\0';
        }
        fprintf(temp, "%d|%d|%d|%.2f|%s\n", B.billingID, B.patientID, B.appointmentID, B.amount, B.paymentStatus);
     }
     fclose(fp);
     fclose(temp);
     if (found == 1)
     {
        remove("data/billing.txt");
        rename("data/temp.txt", "data/billing.txt");
        printf("Payment status updated succesfully!\n");
     }
     else
     {
        remove("data/temp.txt");
        printf("Billing information not found\n");
     }
}
