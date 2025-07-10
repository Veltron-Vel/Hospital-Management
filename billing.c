#include <stdio.h>
#include <stdlib.h>
#include "billing.h"

void addBilling()
{
    billing B;

    printf("Type patient ID:\n");
    scanf("%d",&B.patient_id);

    printf("Type total money:\n");
    scanf("%lf",&B.money);

    printf("Type paid money:\n");
    scanf("%lf",&B.paid);

    B.due = B.money - B.paid;

    FILE *ptr = fopen("Billings.dat","ab");

    if(ptr==NULL)
    {
    printf("Couldn't open file\n");
    return;
    }

    fwrite(&B,sizeof(billing),1,ptr);
    fclose(ptr);

    printf("Billing added succesfully\n");
}

void viewBillings()
{
    FILE *ptr=fopen("Billings.dat","rb");
    if(ptr==NULL)
    {
        printf("No billing records found\n");
        return;
    }

    billing B;
    while(fread(&B,sizeof(billing),1,ptr))
    {
        printf("\n---Billing Data---\n");
        printf("Patient ID : %d\n", B.patient_id);
        printf("Total money: %.2lf\n", B.money);
        printf("Paid       : %.2lf\n", B.paid);
        printf("Due        : %.2lf\n", B.money-B.paid);
        printf("---------END---------\n");
    }

    fclose(ptr);
}

void searchBilling()
{
    billing B;
    int ID,found=0;
    printf("Type the patient ID:\n");
    scanf("%d",&ID);

    FILE *ptr = fopen("Billings.dat","rb");
    if(ptr==NULL)
    {
        printf("File wasnt found\n");
        return;
    }

    while(fread(&B,sizeof(billing),1,ptr))
    {
        if(B.patient_id==ID)
        {

        printf("\n---Billing Data---\n");
        printf("Patient ID : %d\n", B.patient_id);
        printf("Total money: %.2lf\n", B.money);
        printf("Paid       : %.2lf\n", B.paid);
        printf("Due        : %.2lf\n", B.money-B.paid);
        printf("---------END---------\n");
        found = 1;
        
        break;
        }
    }

    fclose(ptr);

    if(found == 0)
    {
        printf("No billing information found with this ID\n");
    }
}





