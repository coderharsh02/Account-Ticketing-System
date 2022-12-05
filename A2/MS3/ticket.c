#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "ticket.h"
#include "account.h"
#include "commonHelpers.h"

// get the new ticket details from the agent and returns it using modifiable Ticket pointer
void getTicket(struct Ticket *ticketPtr, const struct Account *accPtr)
{
    ticketPtr->cusAccNum = accPtr->accountNumber;
    ticketPtr->ticStatus = 1;
    printf("\nNew Ticket (Ticket#:%06d)\n", ticketPtr->ticNum);
    printf("----------------------------------------\n");
    printf("Enter the ticket SUBJECT (30 chars. maximum): ");
    getCString(ticketPtr->ticSubject, 1, 30);
    printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
    getCString(ticketPtr->ticMesArr[0].message, 1, 150);
    strcpy(ticketPtr->ticMesArr[0].fullName, accPtr->accountDetails.fullName);
    ticketPtr->ticMesArr[0].accountType = 'C';
    ticketPtr->ticMesCounter++;
    printf("\n*** New ticket created! ***\n\n");
}

// manages the ticket giving different option
void manageTick(struct Ticket *ticketPtr, const struct Account *accPtr)
{
    int userChoice;
    char ch;
    do
    {
        printf("\n----------------------------------------\n");
        printf("Ticket %06d - Update Options\n", ticketPtr->ticNum);
        printf("----------------------------------------\n");
        printf("Status  : %s\n", ticketPtr->ticStatus == 1 ? "ACTIVE" : "CLOSED");
        printf("Subject : %s\n", ticketPtr->ticSubject);
        printf("Acct#   : %d\n", ticketPtr->cusAccNum);
        printf("Customer: %s\n", ticketPtr->ticMesArr[0].fullName);
        printf("----------------------------------------\n");
        printf("1) Add CUSTOMER message\n");
        printf("2) Add AGENT message\n");
        printf("3) Close ticket\n");
        printf("4) Re-activate ticket\n");
        printf("0) Done\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 4);
        switch (userChoice)
        {
        case 1:
            if (ticketPtr->ticStatus == 1)
            {
                if (ticketPtr->ticMesCounter < 20)
                {
                    printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                    getCString(ticketPtr->ticMesArr[ticketPtr->ticMesCounter].message, 1, 150);
                    ticketPtr->ticMesArr[ticketPtr->ticMesCounter].accountType = 'C';
                    strcpy(ticketPtr->ticMesArr[ticketPtr->ticMesCounter].fullName, ticketPtr->ticMesArr[0].fullName);
                    ticketPtr->ticMesCounter++;
                }
                else
                {
                    printf("\nERROR: Message limit has been reached, call ITS Support!\n");
                }
            }
            else
            {
                printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
            }
            break;
        case 2:
            if (ticketPtr->ticStatus == 1)
            {
                if (ticketPtr->ticMesCounter < 20)
                {
                    printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                    getCString(ticketPtr->ticMesArr[ticketPtr->ticMesCounter].message, 1, 150);
                    ticketPtr->ticMesArr[ticketPtr->ticMesCounter].accountType = 'A';
                    strcpy(ticketPtr->ticMesArr[ticketPtr->ticMesCounter].fullName, accPtr->accountDetails.fullName);
                    ticketPtr->ticMesCounter++;
                }
                else
                {
                    printf("\nERROR: Message limit has been reached, call ITS Support!\n");
                }
            }
            else
            {
                printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
            }
            break;
        case 3:
            if (ticketPtr->ticStatus == 1)
            {
                printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                ch = getCharOption("YN");
                if (ch == 'Y')
                {
                    ticketPtr->ticStatus = 0;
                    printf("\n*** Ticket closed! ***\n");
                }
            }
            else
            {
                printf("\nERROR: Ticket is already closed!\n");
            }
            break;
        case 4:
            if (ticketPtr->ticStatus == 0)
            {
                printf("\nAre you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
                ch = getCharOption("YN");
                if (ch == 'Y')
                {
                    ticketPtr->ticStatus = 1;
                    printf("\n*** Ticket re-activated! ***\n");
                }
            }
            else
            {
                printf("\nERROR: Ticket is already active!\n");
            }
            break;
        case 0:
            printf("\n");
            break;
        }
    } while (userChoice);
}