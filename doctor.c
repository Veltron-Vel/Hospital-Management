#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"

void addDoctor()
{
    doctor D;

    printf("Type the doctors name:\n");
    fgets(D.name,sizeof(D.name),stdin);   /// Name input
    D.name[strcspn(D.name,"\n")] = '\0';  /// Removing newline

    printf("Type the doctors ID:\n");
    scanf("%d",&D.id);                    //ID input

    printf("Type the doctors age:\n");
    scanf("%d",&D.age);                    /// Age input

    printf("Type the doctors gender: M or F\n");
    scanf(" %c",&D.gender);                 /// Gender input. Space for before %c to ensure safety

    while((getchar())!='\n');           /// Clearing Input buffer 

    printf("Type the doctors specializations:\n");
    fgets(D.speciality,sizeof(D.speciality),stdin); /// Diagnosis input
    D.speciality[strcspn(D.speciality,"\n")] = '\0'; /// Removing newline
    
    printf("Type experience:\n");
    scanf("%d",&D.experience);          /// Input experience

    FILE *ptr = fopen("Doctors.dat","ab");
    if(ptr==NULL)
    {
        printf("File couldn't open;\n");
        return;
    }

    fwrite(&D,sizeof(doctor),1,ptr);
    fclose(ptr);

    printf("Doctor added succesfully:\n");
}

void viewDoctors()
{
    FILE *ptr=fopen("Doctors.dat","rb");
    if(ptr==NULL)
    {
        printf("No doctor records found\n");
        return;
    }

    doctor D;
    int count = 1;
    while(fread(&D,sizeof(doctor),1,ptr))
    {
        printf("\n---Doctor Data---\n");
        printf("Doctor No :%d\n",count++);
        printf("Name      : %s\n", D.name);
        printf("ID        : %d\n", D.id);
        printf("Age       : %d\n", D.age);
        printf("Gender    : %c\n", D.gender);
        printf("Speciality: %s\n", D.speciality);
        printf("Experience:%d\n", D.experience);
        printf("---------END---------\n");
    }

    fclose(ptr);
}

void searchDoctor()
{
    doctor D;
    int ID,found=0;
    printf("Type the doctor ID:\n");
    scanf("%d",&ID);

    FILE *ptr = fopen("Doctors.dat","rb");
    if(ptr==NULL)
    {
        printf("File wasnt found\n");
        return;
    }

    while(fread(&D,sizeof(doctor),1,ptr))
    {
        if(D.id==ID)
        {
        found = 1;
        printf("\n---Doctors Data---\n");
        printf("Name      : %s\n", D.name);
        printf("ID        : %d\n", D.id);
        printf("Age       : %d\n", D.age);
        printf("Gender    : %c\n", D.gender);
        printf("Speciality: %s\n", D.speciality);
        printf("Experience:%d\n", D.experience);
        printf("---------END---------\n");
        break;
        }
    }

    fclose(ptr);

    if(found == 0)
    {
        printf("No doctors found with this ID\n");
    }
}