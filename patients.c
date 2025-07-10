#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "patients.h"

void addPatient()
{
    patient P;

    printf("Type the patients name:\n");
    fgets(P.name,sizeof(P.name),stdin);   /// Name input
    P.name[strcspn(P.name,"\n")] = '\0';  /// Removing newline

    printf("Type the patients age:\n");
    scanf("%d",&P.age);                    /// Age input

    printf("Type the patients gender: M or F\n");
    scanf(" %c",&P.gender);                 /// Gender input. Space for before %c to ensure safety

    printf("Type the patients ID:\n");
    scanf("%d",&P.id);                  /// ID input

    while((getchar())!='\n');           /// Clearing Input buffer 

    printf("Type the patients diagnosis:\n");
    fgets(P.disease,sizeof(P.disease),stdin); /// Diagnosis input
    P.disease[strcspn(P.disease,"\n")] = '\0'; /// Removing newline                           

    FILE *ptr = fopen("Patients.dat","ab");
    if(ptr==NULL)
    {
        printf("File couldn't open;\n");
        return;
    }

    fwrite(&P,sizeof(patient),1,ptr);
    fclose(ptr);

    printf("Patient added succesfully:\n");


}

void viewPatient()
{
    FILE *ptr=fopen("Patients.dat","rb");
    if(ptr==NULL)
    {
        printf("No patient records found\n");
        return;
    }

    patient P;
    int count = 1;
    while(fread(&P,sizeof(patient),1,ptr))
    {
        printf("\n---Patient Data---\n");
        printf("Patient No:%d\n",count++);
        printf("ID        : %d\n", P.id);
        printf("Name      : %s\n", P.name);
        printf("Age       : %d\n", P.age);
        printf("Gender    : %c\n", P.gender);
        printf("Diagnosis : %s\n", P.disease);
        printf("---------END---------\n");
    }

    fclose(ptr);
}

void searchPatient()
{
    patient P;
    int ID,found=0;
    printf("Type the patient ID:\n");
    scanf("%d",&ID);

    FILE *ptr = fopen("Patients.dat","rb");
    if(ptr==NULL)
    {
        printf("File wasnt found\n");
        return;
    }

    while(fread(&P,sizeof(patient),1,ptr))
    {
        if(P.id==ID)
        {
        found = 1;
        printf("\n---Patient Data---\n");
        printf("ID       : %d\n", P.id);
        printf("Name     : %s\n", P.name);
        printf("Age      : %d\n", P.age);
        printf("Gender   : %c\n", P.gender);
        printf("Diagnosis: %s\n", P.disease);
        printf("---------END---------\n");
        break;
        }
    }

    fclose(ptr);

    if(found == 0)
    {
        printf("No patient found with this ID\n");
    }
}