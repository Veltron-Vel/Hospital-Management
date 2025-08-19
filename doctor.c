#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doctor.h"
#define FILE_PATH "data/doctor.txt"

void doctorMenu()
{
    int choice;
    do
    {
        printf("\n\033[1;34m-----DOCTOR MANAGEMENT-----\033[0m\n");
        printf("1. Add doctor\n");
        printf("2. View doctor(s)\n");
        printf("3. Search doctor by ID\n");
        printf("4. Delete doctor\n");
        printf("5. Return to main menu\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                addDoctor();
                break;
            case 2:
                viewDoctor();
                break;
            case 3:
                searchDoctor();
                break;
            case 4:
                deleteDoctor();
                break;
            case 5:
                printf("\033[34mReturning to main menu\033[0m\n");
                break;
            default:
                printf("\033[31mInvalid choice. Try again...\033[0m\n");
        }
    } while (choice != 5);
}

void addDoctor()
{
    FILE *fp = fopen(FILE_PATH, "a");
    if (fp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }
    Doctor D;

    printf("Enter doctor's id: ");
    scanf("%d", &D.id);
    while (getchar() != '\n');

    printf("Enter name: ");
    fgets(D.name, sizeof(D.name), stdin);
    D.name[strcspn(D.name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &D.age);
    while (getchar() != '\n');

    printf("Enter gender: ");
    fgets(D.gender, sizeof(D.gender), stdin);
    D.gender[strcspn(D.gender, "\n")] = '\0';

    printf("Enter specialty: ");
    fgets(D.specialty, sizeof(D.specialty), stdin);
    D.specialty[strcspn(D.specialty, "\n")] = '\0';

    fprintf(fp, "%d|%s|%d|%s|%s\n", D.id, D.name, D.age, D.gender, D.specialty);
    fclose(fp);
    printf("\033[32mDoctor added successfully!\033[0m\n");
}

void viewDoctor()
{
    FILE *fp = fopen(FILE_PATH, "r");
    int count = 0;
    if (fp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }
    Doctor D;

    printf("\n\033[1;34m-----DOCTOR RECORDS-----\033[0m\n");
    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &D.id, &D.name, &D.age, &D.gender, &D.specialty) == 5)
    {
        printf("ID       : %d\n", D.id);
        printf("Name     : %s\n", D.name);
        printf("Age      : %d\n", D.age);
        printf("Gender   : %s\n", D.gender);
        printf("Specialty: %s\n", D.specialty);
        printf("\n");
        count++;
    }
    if (count > 0)
    {
        printf("\033[1;34m---------END---------\033[0m\n");
    }
    else
    {
        printf("\033[31mNo doctor information found in the records\033[0m\n");
    }
    fclose(fp);
}

void searchDoctor()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    if (fp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }
    printf("Enter doctor's ID: ");
    scanf("%d", &targetID);
    while (getchar() != '\n');
    Doctor D;

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &D.id, &D.name, &D.age, &D.gender, &D.specialty) == 5)
    {
        if (targetID == D.id)
        {
            found = 1;

            printf("\n\033[1;34m-----DOCTOR INFORMATION-----\033[0m\n");
            printf("ID       : %d\n", D.id);
            printf("Name     : %s\n", D.name);
            printf("Age      : %d\n", D.age);
            printf("Gender   : %s\n", D.gender);
            printf("Specialty: %s\n", D.specialty);
            printf("\033[1;34m---------END---------\033[0m\n");
        break;
        }
    }
    fclose(fp);

    if (found == 0)
    {
        printf("\033[31mNo doctor found with this ID\033[0m\n");
    }
}

void deleteDoctor()
{
    int targetID, found = 0;
    FILE *fp = fopen(FILE_PATH, "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\033[31mFailed to open file\033[0m\n");
        return;
    }
    Doctor D;

    printf("Enter doctor's id: ");
    scanf("%d", &targetID);
    while (getchar() != '\n');

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%49[^\n]\n", &D.id, &D.name, &D.age, &D.gender, &D.specialty) == 5)
    {
        if (targetID == D.id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d|%s|%d|%s|%s\n", D.id, D.name, D.age, D.gender, D.specialty);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("data/doctor.txt");
    rename("data/temp.txt", "data/doctor.txt");

    if (found == 1)
    {
        printf("\033[32mDoctor deleted successfully!\033[0m\n");
    }
    else
    {
        printf("\033[31mDoctor data not found\033[0m\n");
    }
}
