// #############################################################################################
//  Assignment: 2
//  Milestone : 3
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"
#include "accountTicketingUI.h"

// Application Data Retrieval Fuctions
//////////////////////////////////////

// loads data from accounts.txt file to accounts array
int loadAccounts(struct Account accountArr[], int maxSize)
{
    FILE *fp = NULL;
    int i = 0;
    fp = fopen("accounts.txt", "r");
    if (fp != NULL)
    {
        while (i < maxSize && fscanf(fp, "%d", &accountArr[i].accountNumber) != EOF)
        {
            fscanf(
                fp, "~%c~%[^~]%*c%d~%lf~%[^~\n]%*c",
                &accountArr[i].accountType,
                accountArr[i].accountDetails.fullName,
                &accountArr[i].accountDetails.birthYear,
                &accountArr[i].accountDetails.houseHoldIncome,
                accountArr[i].accountDetails.cntyName);
            if (accountArr[i].accountType == 'A')
            {
                fscanf(
                    fp, "%[^~]%*c%[^~\n]%*c",
                    accountArr[i].accountCredential.username,
                    accountArr[i].accountCredential.password);
            }
            i++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }
    return i;
}

// loads data from tickets.txt file to tickets array
int loadTickets(struct Ticket ticketArr[], int maxSize)
{
    FILE *fp = NULL;
    int i = 0;
    fp = fopen("tickets.txt", "r");
    if (fp != NULL)
    {
        while (i < maxSize && fscanf(fp, "%d", &ticketArr[i].ticNum) != EOF)
        {
            fscanf(
                fp, "|%d|%d|%[^|]%*c%d|",
                &ticketArr[i].cusAccNum,
                &ticketArr[i].ticStatus,
                ticketArr[i].ticSubject,
                &ticketArr[i].ticMesCounter);

            int j = 0;
            while (j < ticketArr[i].ticMesCounter)
            {
                fscanf(
                    fp, "%c|%[^|]%*c%[^|]%*c",
                    &ticketArr[i].ticMesArr[j].accountType,
                    ticketArr[i].ticMesArr[j].fullName,
                    ticketArr[i].ticMesArr[j].message);
                j++;
            }
            i++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }
    return i;
}

// Application Logic Functions
//////////////////////////////

// provides entry point to application
void applicationStartup(struct AccountTicketingData *accTicPtr)
{
    int accIndex;
    do
    {
        accIndex = menuLogin(accTicPtr->accounts, accTicPtr->ACCOUNT_MAX_SIZE);
        if (accIndex != -1)
        {
            if (accTicPtr->accounts[accIndex].accountType == 'A')
            {
                menuAgent(accTicPtr, &accTicPtr->accounts[accIndex]);
            }
            else
            {
                printf("ERROR:  Login failed!\n\n");
                pauseExecution();
            }
        }
    } while (accIndex != -1);
    printf("\n==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");
}

// navigation menu for login
int menuLogin(const struct Account accountArr[], int max)
{
    int userChoice, flag = 1, accIndex = -1, attempts;
    char c;
    char loginStr[50], passwordStr[50];
    do
    {
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 1);
        switch (userChoice)
        {
        case 1:
            attempts = 3;
            do
            {
                accIndex = findAccountIndexByAcctNum(0, accountArr, max, 0);
                printf("User Login        : ");
                getCString(loginStr, 1, 49);
                printf("Password          : ");
                getCString(passwordStr, 1, 49);
                if (accIndex > -1 && accountArr[accIndex].accountType == 'A')
                {
                    if (!strcmp(loginStr, accountArr[accIndex].accountCredential.username))
                    {
                        if (!strcmp(passwordStr, accountArr[accIndex].accountCredential.password))
                        {
                            flag = 0;
                        }
                    }
                }
                if (flag)
                {
                    attempts--;
                    printf("INVALID user login/password combination! [attempts remaining:%d]\n", attempts);
                }
            } while (attempts && flag);
            if (!attempts && flag)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            break;
        case 0:
            printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
            c = getCharOption("yYnN");
            if (c == 'y' || c == 'Y')
            {
                flag = 0;
            }
            else
            {
                printf("\n");
            }
            break;
        }
    } while (flag);
    return accIndex;
}

// navigation menu for agents
void menuAgent(struct AccountTicketingData *accTicPtr, const struct Account *accPtr)
{
    int userChoice, index, found, i, newAccountNumber;
    int ticNum, ticIndex, ticRemoved, newTicketNumber;
    char c;
    printf("\n");
    do
    {
        printf("AGENT: %s (%d)\n", accPtr->accountDetails.fullName, accPtr->accountNumber);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("5) List new tickets\n");
        printf("6) List active tickets\n");
        printf("7) List closed tickets\n");
        printf("8) Add a new ticket\n");
        printf("9) Manage a ticket\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 9);
        switch (userChoice)
        {

        case 1:
            found = 0;
            newAccountNumber = 0;
            for (i = 0; i < accTicPtr->ACCOUNT_MAX_SIZE; i++)
            {
                if (accTicPtr->accounts[i].accountNumber == 0 && !found)
                {
                    index = i;
                    found = 1;
                }
                if (accTicPtr->accounts[i].accountNumber > newAccountNumber)
                {
                    newAccountNumber = accTicPtr->accounts[i].accountNumber;
                }
            }
            if (found)
            {
                accTicPtr->accounts[index].accountNumber = newAccountNumber + 1;
                getAccount(&accTicPtr->accounts[index]);
                printf("*** New account added! ***\n\n");
            }
            else
            {
                printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
            }
            pauseExecution();
            break;
        case 2:
            index = findAccountIndexByAcctNum(0, accTicPtr->accounts, accTicPtr->ACCOUNT_MAX_SIZE, 0);
            if (index != -1)
            {
                updateAccount(&accTicPtr->accounts[index]);
            }
            else
            {
                printf("\nERROR: Access Denied.\n");
                pauseExecution();
            }
            break;
        case 3:
            index = findAccountIndexByAcctNum(0, accTicPtr->accounts, accTicPtr->ACCOUNT_MAX_SIZE, 0);
            if (index != -1)
            {
                if (accPtr->accountNumber == accTicPtr->accounts[index].accountNumber)
                {
                    printf("\nERROR: You can't remove your own account!\n\n");
                }
                else
                {
                    displayAccountDetailHeader();
                    displayAccountDetailRecord(&accTicPtr->accounts[index]);
                    printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                    c = getCharOption("YN");
                    if (c == 'Y')
                    {
                        ticRemoved = 0;
                        for (i = 0; i < accTicPtr->TICKET_MAX_SIZE; i++)
                        {
                            if (accTicPtr->tickets[i].cusAccNum == accTicPtr->accounts[index].accountNumber)
                            {
                                accTicPtr->tickets[i].ticNum = 0;
                                ticRemoved++;
                            }
                        }
                        accTicPtr->accounts[index].accountNumber = 0;
                        printf("\n*** Account Removed! (%d ticket(s) removed) ***\n\n", ticRemoved);
                    }
                    else
                    {
                        printf("\n*** No changes made! ***\n\n");
                    }
                }
            }
            else
            {
                printf("\nERROR: Access Denied.\n");
            }
            pauseExecution();
            break;
        case 4:
            displayAllAccountDetailRecords(accTicPtr->accounts, accTicPtr->ACCOUNT_MAX_SIZE);
            pauseExecution();
            break;
        case 5:
            printf("\n");

            do
            {
                displayNewTicketsDetailRecords(accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE);
                printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");
                ticNum = getInteger();
                if (ticNum > 0)
                {
                    ticIndex = findTicketIndexByTicNum(ticNum, accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE, 1);
                    if (ticIndex > -1 && accTicPtr->tickets[ticIndex].ticStatus == 1 && accTicPtr->tickets[ticIndex].ticMesCounter == 1)
                    {
                        displayTicketMessage(&accTicPtr->tickets[ticIndex]);
                    }
                    else
                    {
                        printf("\nERROR: Invalid ticket number.\n\n");
                    }
                    pauseExecution();
                }
            } while (ticNum);
            printf("\n");
            break;
        case 6:
            printf("\n");
            do
            {
                displayActiveTicketsDetailRecords(accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE);
                printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");
                ticNum = getInteger();
                if (ticNum > 0)
                {
                    ticIndex = findTicketIndexByTicNum(ticNum, accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE, 1);
                    if (ticIndex > -1 && accTicPtr->tickets[ticIndex].ticStatus == 1)
                    {
                        displayTicketMessage(&accTicPtr->tickets[ticIndex]);
                    }
                    else
                    {
                        printf("\nERROR: Invalid ticket number.\n\n");
                    }
                    pauseExecution();
                }
            } while (ticNum);
            printf("\n");
            break;
        case 7:
            printf("\n");
            do
            {
                displayCloseTicketsDetailRecords(accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE);
                printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");
                ticNum = getInteger();
                if (ticNum > 0)
                {
                    ticIndex = findTicketIndexByTicNum(ticNum, accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE, 1);
                    if (ticIndex > -1 && accTicPtr->tickets[ticIndex].ticStatus == 0)
                    {
                        displayTicketMessage(&accTicPtr->tickets[ticIndex]);
                    }
                    else
                    {
                        printf("\nERROR: Invalid ticket number.\n\n");
                    }
                    pauseExecution();
                }
            } while (ticNum);
            printf("\n");
            break;
        case 8:
            found = 0;
            newTicketNumber = 0;
            for (i = 0; i < accTicPtr->TICKET_MAX_SIZE; i++)
            {
                if (accTicPtr->tickets[i].ticNum == 0)
                {
                    ticIndex = i;
                    found = 1;
                }
                if (accTicPtr->tickets[i].ticNum > newTicketNumber)
                {
                    newTicketNumber = accTicPtr->tickets[i].ticNum;
                }
            }
            if (found)
            {
                index = findAccountIndexByAcctNum(0, accTicPtr->accounts, accTicPtr->ACCOUNT_MAX_SIZE, 0);
                if (index > -1)
                {
                    if (accTicPtr->accounts[index].accountType == 'C')
                    {
                        displayAccountDetailHeader();
                        displayAccountDetailRecord(&accTicPtr->accounts[index]);
                        printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");
                        c = getCharOption("YN");
                        if (c == 'Y')
                        {
                            accTicPtr->tickets[ticIndex].ticNum = newTicketNumber + 1;
                            getTicket(&accTicPtr->tickets[ticIndex], &accTicPtr->accounts[index]);
                        }
                        else
                        {
                            printf("\n*** No changes made! ***\n\n");
                        }
                    }
                    else
                    {
                        printf("\nERROR: Agent accounts can't have tickets!\n\n");
                    }
                }
                else
                {
                    printf("\nERROR: Invalid Account Number.\n\n");
                }
            }
            else
            {
                printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
            }
            pauseExecution();
            break;
        case 9:
            ticIndex = findTicketIndexByTicNum(ticNum, accTicPtr->tickets, accTicPtr->TICKET_MAX_SIZE, 0);
            if (ticIndex > -1)
            {
                manageTick(&accTicPtr->tickets[ticIndex], accPtr);
            }
            else
            {
                printf("\nERROR: Invalid ticket number.\n\n");
            }
            break;
        case 0:
            printf("\n### LOGGED OUT ###\n\n");
            break;
        }
    } while (userChoice);
}

// returns index for an account number
int findAccountIndexByAcctNum(int accountNumber, const struct Account accountArr[], int max, int prompt)
{
    int index = -1, found = 0, i;
    if (prompt == 0)
    {
        printf("\nEnter the account#: ");
        accountNumber = getPositiveInteger();
    }
    for (i = 0; i < max && !found; i++)
    {
        if (accountArr[i].accountNumber == accountNumber)
        {
            found = 1;
            index = i;
        }
    }
    return index;
}

// returns index for a ticket number
int findTicketIndexByTicNum(int ticketNumber, const struct Ticket ticketArr[], int max, int prompt)
{
    int index = -1, found = 0, i;
    if (prompt == 0)
    {
        printf("\nEnter ticket number: ");
        ticketNumber = getPositiveInteger();
    }
    for (i = 0; i < max && !found; i++)
    {
        if (ticketArr[i].ticNum == ticketNumber)
        {
            found = 1;
            index = i;
        }
    }
    return index;
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    printf("\n");
}

// Account Displaying Functions
//////////////////////////////

// display account detail header
void displayAccountDetailHeader(void)
{
    printf("\nAcct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
    printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}

// display account details
void displayAccountDetailRecord(const struct Account *accPtr)
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

// display all account details
void displayAllAccountDetailRecords(const struct Account accountArr[], int max)
{
    int index = 0;
    displayAccountDetailHeader();
    for (index = 0; index < max; index++)
    {
        if (accountArr[index].accountNumber > 0)
        {
            displayAccountDetailRecord(&accountArr[index]);
        }
    }
    printf("\n");
}

// Ticket Displaying Functions
//////////////////////////////

// display Ticket detail header
void displayTicketDetailHeader(void)
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

// display ticket details
void displayTicketDetailRecord(const struct Ticket *ticketPtr)
{

    printf(
        "%06d %5d %-15s %-6s %-30s    %2d\n",
        ticketPtr->ticNum,
        ticketPtr->cusAccNum,
        ticketPtr->ticMesArr[0].fullName,
        ticketPtr->ticStatus == 1 ? "ACTIVE" : "CLOSED",
        ticketPtr->ticSubject,
        ticketPtr->ticMesCounter);
}

// display Ticket's messages
void displayTicketMessage(const struct Ticket *ticketPtr)
{
    int i;
    printf("\n================================================================================\n");
    printf("%06d (%s) Re: %s\n", ticketPtr->ticNum, ticketPtr->ticStatus == 1 ? "ACTIVE" : "CLOSED", ticketPtr->ticSubject);
    printf("================================================================================\n");
    for (i = 0; i < ticketPtr->ticMesCounter; i++)
    {
        printf("%s (%s):\n", ticketPtr->ticMesArr[i].accountType == 'C' ? "CUSTOMER" : "AGENT", ticketPtr->ticMesArr[i].fullName);
        printf("   %s\n\n", ticketPtr->ticMesArr[i].message);
    }
}

// display New tickets detailed records
void displayNewTicketsDetailRecords(const struct Ticket ticketArr[], int max)
{
    int index = 0;
    displayTicketDetailHeader();
    for (index = 0; index < max; index++)
    {
        if (ticketArr[index].ticNum > 0 && ticketArr[index].ticStatus == 1 && ticketArr[index].ticMesCounter == 1)
        {
            displayTicketDetailRecord(&ticketArr[index]);
        }
    }
}

// display Active tickets detailed records
void displayActiveTicketsDetailRecords(const struct Ticket ticketArr[], int max)
{
    int index = 0;
    displayTicketDetailHeader();
    for (index = 0; index < max; index++)
    {
        if (ticketArr[index].ticNum > 0 && ticketArr[index].ticStatus == 1)
        {
            displayTicketDetailRecord(&ticketArr[index]);
        }
    }
}

// display Closed tickets detailed records
void displayCloseTicketsDetailRecords(const struct Ticket ticketArr[], int max)
{
    int index = 0;
    displayTicketDetailHeader();
    for (index = 0; index < max; index++)
    {
        if (ticketArr[index].ticNum > 0 && ticketArr[index].ticStatus == 0)
        {
            displayTicketDetailRecord(&ticketArr[index]);
        }
    }
}

// End