#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#define FILE_PATH "data/patient.txt"

void patientMenu()
{
    int choice;
    do
    {
        printf("\n-----PATIENT MANAGEMENT-----\n");
        printf("1. Add patient\n");
        printf("2. View patient(s)\n");
        printf("3. Search patient by ID\n");
        printf("4. Delete patient\n");
        printf("5. Return to main menu\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        switch(choice)
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
                deletePatient();
                break;
            case 5:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice. Try again...\n");
        }
    } while (choice != 5);
}

void addPatient()
{
    FILE *fp = fopen(FILE_PATH, "a");

    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    Patient P;

    printf("Enter patient id: ");
    scanf("%d", &P.id);
    getchar();

    printf("Enter name: ");
    fgets(P.name, sizeof(P.name), stdin);
    P.name[strcspn(P.name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &P.age);
    getchar();

    printf("Enter gender: ");
    fgets(P.gender, sizeof(P.gender), stdin);
    P.gender[strcspn(P.gender, "\n")] = '\0';

    printf("Enter disease: ");
    fgets(P.disease, sizeof(P.disease), stdin);
    P.disease[strcspn(P.disease, "\n")] = '\0';

    fprintf(fp, "%d|%s|%d|%s|%s\n", P.id, P.name, P.age, P.gender, P.disease);
    fclose(fp);

    printf("Patient added successfully!\n");
}

void viewPatient()
{
    FILE *fp = fopen(FILE_PATH, "r");

    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    Patient P;
    printf("\n-----PATIENT RECORDS-----\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &P.id, &P.name, &P.age, &P.gender, &P.disease) == 5)
    {
        printf("ID     : %d\n", P.id);
        printf("Name   : %s\n", P.name);
        printf("Age    : %d\n", P.age);
        printf("Gender : %s\n", P.gender);
        printf("Disease: %s\n", P.disease);
        printf("\n");
    }
     printf("---------END---------\n");

    fclose(fp);
}

void searchPatient()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }
    printf("Enter patient's ID: ");
    scanf("%d", &targetID);
    Patient P;

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &P.id, &P.name, &P.age, &P.gender, &P.disease) == 5)
    {
        if (targetID == P.id)
        {
            found = 1;

            printf("\n-----PATIENT INFORMATION-----\n");
            printf("ID     : %d\n", P.id);
            printf("Name   : %s\n", P.name);
            printf("Age    : %d\n", P.age);
            printf("Gender : %s\n", P.gender);
            printf("Disease: %s\n", P.disease);
            printf("---------END---------\n");
        break;
        }
    }
    fclose(fp);

    if (found == 0)
    {
        printf("No doctor found with this ID\n");
    }
}

void deletePatient()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    printf("Enter patient's ID: ");
    scanf("%d", &targetID);
    Patient P;

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &P.id, &P.name, &P.age, &P.gender, &P.disease) == 5)
    {
        if (targetID == P.id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d|%s|%d|%s|%s\n", P.id, P.name, P.age, P.gender, P.disease);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("data/patient.txt");
    rename("data/temp.txt", "data/patient.txt");

    if (found == 1)
    {
        printf("Patient deleted successfully!\n");
    }
    else
    {
        printf("Patient data not found\n");
    }
}
