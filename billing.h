#ifndef BILLING_H
#define BILLING_H

typedef struct billing
{
    int patient_id;
    double money;
    double paid;
    double due;

} billing;

void addBilling();
void viewBillings();
void searchBilling();

#endif