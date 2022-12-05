// #############################################################################################
//  Assignment: 1 
//  Milestone : 3
// #############################################################################################

#include <stdio.h>
#include "accountTicketingUI.h"
// display account detail header
void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
    printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}
// display account details
void displayAccountDetailRecord(struct Account *accPtr)
{
    int i;
    char hiddenPass[9];
    for (i = 0; accPtr->accountCredential.password[i] != '\0'; i++)
        if (i % 2 == 0)
            hiddenPass[i] = accPtr->accountCredential.password[i];
        else
            hiddenPass[i] = '*';
    
    hiddenPass[i] = '\0';
    printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n",
           accPtr->accountNumber,
           accPtr->accountType == 'C' ? "CUSTOMER" : "AGENT",
           accPtr->accountDetails.fullName, accPtr->accountDetails.birthYear,
           accPtr->accountDetails.houseHoldIncome, accPtr->accountDetails.cntyName,
           accPtr->accountCredential.username, hiddenPass);
}