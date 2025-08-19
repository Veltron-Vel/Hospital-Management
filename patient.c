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
        printf("\n\033[1;34m-----PATIENT MANAGEMENT-----\033[0m\n");
        printf("1. Add patient\n");
        printf("2. View patient(s)\n");
        printf("3. Search patient by ID\n");
        printf("4. Delete patient\n");
        printf("5. Return to main menu\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

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
                printf("\033[34mReturning to main menu\033[0m\n");
                break;
            default:
                printf("\033[31mInvalid choice. Try again...\033[0m\n");
        }
    } while (choice != 5);
}

void addPatient()
{
    FILE *fp = fopen(FILE_PATH, "a");

    if (fp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }

    Patient P;

    printf("Enter patient id: ");
    scanf("%d", &P.id);
    while (getchar() != '\n');

    printf("Enter name: ");
    fgets(P.name, sizeof(P.name), stdin);
    P.name[strcspn(P.name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &P.age);
    while (getchar() != '\n');

    printf("Enter gender: ");
    fgets(P.gender, sizeof(P.gender), stdin);
    P.gender[strcspn(P.gender, "\n")] = '\0';

    printf("Enter disease: ");
    fgets(P.disease, sizeof(P.disease), stdin);
    P.disease[strcspn(P.disease, "\n")] = '\0';

    fprintf(fp, "%d|%s|%d|%s|%s\n", P.id, P.name, P.age, P.gender, P.disease);
    fclose(fp);

    printf("\033[32mPatient added successfully!\033[0m\n");
}

void viewPatient()
{
    FILE *fp = fopen(FILE_PATH, "r");
    int count = 0;

    if (fp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }

    Patient P;
    printf("\n\033[1;34m-----PATIENT RECORDS-----\033[0m\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &P.id, &P.name, &P.age, &P.gender, &P.disease) == 5)
    {
        printf("ID     : %d\n", P.id);
        printf("Name   : %s\n", P.name);
        printf("Age    : %d\n", P.age);
        printf("Gender : %s\n", P.gender);
        printf("Disease: %s\n", P.disease);
        printf("\n");
        count++;
    }
    if (count > 0)
    {
        printf("\033[1;34m---------END---------\033[0m\n");
    }
    else
    {
        printf("\033[31mNo patient information found in the records\033[0m\n");
    }

    fclose(fp);
}

void searchPatient()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    if (fp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }
    printf("Search patient by ID: ");
    scanf("%d", &targetID);
    while (getchar() != '\n');
    Patient P;

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &P.id, &P.name, &P.age, &P.gender, &P.disease) == 5)
    {
        if (targetID == P.id)
        {
            found = 1;

            printf("\n\033[1;34m-----PATIENT INFORMATION-----\033[0m\n");
            printf("ID     : %d\n", P.id);
            printf("Name   : %s\n", P.name);
            printf("Age    : %d\n", P.age);
            printf("Gender : %s\n", P.gender);
            printf("Disease: %s\n", P.disease);
            printf("\033[1;34m---------END---------\033[0m\n");
        break;
        }
    }
    fclose(fp);

    if (found == 0)
    {
        printf("\033[31mNo patient found with this ID\033[0m\n");
    }
}

void deletePatient()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }

    printf("Enter patient's ID: ");
    scanf("%d", &targetID);
    while (getchar() != '\n');
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
        printf("\033[32mPatient deleted successfully!\033[0m\n");
    }
    else
    {
        printf("\033[31mPatient data not found\033[0m\n");
    }
}
