// #############################################################################################
//  Assignment: 1 
//  Milestone : 4
// #############################################################################################

#include <stdio.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
// display account detail header
void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
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
// provides entry point to application
void applicationStartup(struct Account accountArr[], int max)
{
    int accIndex;
    do
    {
        accIndex = menuLogin(accountArr, max);
        if (accIndex != -1)
        {
            if (accountArr[accIndex].accountType == 'A')
            {
                menuAgent(accountArr, max, &accountArr[accIndex]);
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
    int userChoice, flag = 1, accNumber, accIndex = -1;
    char c;
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
            printf("\nEnter your account#: ");
            accNumber = getPositiveInteger();
            accIndex = findAccountIndexByAcctNum(accNumber, accountArr, max, 1);
            if (accIndex != -1)
                flag = 0;
            else
            {
                printf("ERROR:  Login failed!\n\n");
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
// navigation for agents
void menuAgent(struct Account accountArr[], int max, const struct Account *accPtr)
{
    int userChoice, index = -1, found = 0, i;
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
        printf("0) Logout\n\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 5);
        switch (userChoice)
        {

        case 1:
            found = 0;
            for (i = 0; i < max && !found; i++)
            {
                if (accountArr[i].accountNumber == 0)
                {
                    index = i;
                    found = 1;
                }
            }
            if (found)
            {
                getAccount(&accountArr[index]);
                printf("*** New account added! ***\n\n");
                pauseExecution();
            }
            else
            {
                printf("ERROR: Account listing is FULL, call ITS Support!\n");
            }
            break;
        case 2:
            index = -1;
            found = 0;
            index = findAccountIndexByAcctNum(0, accountArr, max, 0);
            if (index != -1)
            {
                updateAccount(&accountArr[index]);
            }
            else
            {
                printf("\nERROR: Access Denied.\n");
                pauseExecution();
            }
            break;

        case 3:
            index = -1;
            found = 0;
            index = findAccountIndexByAcctNum(0, accountArr, max, 0);
            if (index != -1)
            {
                if (accPtr->accountNumber == accountArr[index].accountNumber)
                {
                    printf("\nERROR: You can't remove your own account!\n\n");
                }
                else
                {
                    displayAccountDetailHeader();
                    displayAccountDetailRecord(&accountArr[index]);
                    printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                    c = getCharOption("YN");
                    if (c == 'Y')
                    {
                        accountArr[index].accountNumber = 0;
                        printf("\n*** Account Removed! ***\n\n");
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
            printf("\n");
            displayAllAccountDetailRecords(accountArr, max);
            pauseExecution();
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
// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}