#ifndef BILLING_H
#define BILLING_H

typedef struct
{
    int billingID;
    int patientID;
    int appointmentID;
    float amount;
    char paymentStatus[20];
} Billing;

void addBill();
void viewBill();
void searchBill();
void updateStatus();
void billingMenu();

#endif
