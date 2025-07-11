#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"
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
        printf("4. Return to main menu\n");
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
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice. Try again...\n");
        }
    } while (choice != 4);
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
    getchar();

    printf("Enter patient ID: ");
    scanf("%d", &B.patientID);
    getchar();

    printf("Enter appointment ID: ");
    scanf("%d", &B.appointmentID);
    getchar();

    printf("Enter amount: ");
    scanf("%f", &B.amount);
    getchar();

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
    }
    printf("-----END-----\n");
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
    getchar();

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
