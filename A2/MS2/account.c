// #############################################################################################
//  Assignment: 2
//  Milestone : 2
// #############################################################################################

#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"

// get the account details from the user and returns it using modifiable Account pointer
void getAccount(struct Account *accPtr)
{

    printf("\nNew Account Data (Account#:%d)\n", accPtr->accountNumber);
    printf("----------------------------------------\n");
    printf("Enter the account type (A=Agent | C=Customer): ");
    accPtr->accountType = getCharOption("AC");
    printf("\n");
    getPerson(&accPtr->accountDetails);
    if (accPtr->accountType == 'A')
    {
        getUserLogin(&accPtr->accountCredential);
        printf("\n");
    }
    else
    {
        accPtr->accountCredential.username[0] = '\0';
        accPtr->accountCredential.password[0] = '\0';
    }
}

// get the inputs for Person structure from the user and returns it using modifiable Person pointer
void getPerson(struct Person *perPtr)
{
    int i;
    printf("Person Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter the person's full name (30 chars max): ");
    getCString(perPtr->fullName, 1, 30);
    printf("Enter birth year (current age must be between 18 and 110): ");
    perPtr->birthYear = getIntFromRange(currentYear() - 110, currentYear() - 18);
    printf("Enter the household Income: $");
    perPtr->houseHoldIncome = getPositiveDouble();
    printf("Enter the country (30 chars max.): ");
    getCString(perPtr->cntyName, 1, 30);
    for (i = 0; perPtr->cntyName[i] != '\0'; i++)
    {
        if (perPtr->cntyName[i] >= 97 && perPtr->cntyName[i] <= 122)
        {
            perPtr->cntyName[i] -= 32;
        }
    }
    printf("\n");
}

// get the inputs for UserLogin structure from the user and returns it using modifiable UserLogin pointer
void getUserLogin(struct UserLogin *uslPtr)
{
    int i, notFound;
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    do
    {
        notFound = 1;
        printf("Enter user login (10 chars max): ");
        getCString(uslPtr->username, 1, 10);
        for (i = 0; uslPtr->username[i] != '\0' && notFound; i++)
        {
            if (uslPtr->username[i] == ' ')
            {
                notFound = 0;
                uslPtr->username[0] = '\0';
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
            }
        }
    } while (!notFound);
    getUserPassword(uslPtr->password);
}

// updates account details using Account pointer
void updateAccount(struct Account *accPtr)
{
    int userChoice;
    do
    {
        printf("\nUpdate Account: %d (%s)\n", accPtr->accountNumber, accPtr->accountDetails.fullName);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", accPtr->accountType);
        printf("2) Person\n");
        printf("3) Login\n");
        printf("0) Done\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 3);
        switch (userChoice)
        {
        case 1:
            printf("\nEnter the account type (A=Agent | C=Customer): ");
            accPtr->accountType = getCharOption("AC");
            if (accPtr->accountType == 'A')
            {
                printf("\nAgent type accounts require a user login.  Please enter this information now:\n\n");
                getUserLogin(&accPtr->accountCredential);
            }
            else
            {
                accPtr->accountCredential.username[0] = '\0';
                accPtr->accountCredential.password[0] = '\0';
            }
            break;

        case 2:
            updatePerson(&accPtr->accountDetails);
            break;

        case 3:
            if (accPtr->accountType == 'A')
                updateUserLogin(&accPtr->accountCredential);
            else
                printf("\nERROR:  Customer account types don't have user logins!\n");
            break;
        case 0:
            printf("\n");
            break;
        }
    } while (userChoice);
}

// updates Person details using Person pointer
void updatePerson(struct Person *perPtr)
{
    int userChoice, i;
    do
    {
        printf("\nPerson Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Full name (current value: %s)\n", perPtr->fullName);
        printf("2) Household Income (current value: $%.2lf)\n", perPtr->houseHoldIncome);
        printf("3) Country (current value: %s)\n", perPtr->cntyName);
        printf("0) Done\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 3);
        switch (userChoice)
        {
        case 1:
            printf("\nEnter the person's full name (30 chars max): ");
            getCString(perPtr->fullName, 1, 30);
            break;
        case 2:
            printf("\nEnter the household Income: $");
            perPtr->houseHoldIncome = getPositiveDouble();
            break;
        case 3:
            printf("\nEnter the country (30 chars max.): ");
            getCString(perPtr->cntyName, 1, 30);
            for (i = 0; perPtr->cntyName[i] != '\0'; i++)
            {
                if (perPtr->cntyName[i] >= 97 && perPtr->cntyName[i] <= 122)
                {
                    perPtr->cntyName[i] -= 32;
                }
            }
            break;
        case 0:
            break;
        }
    } while (userChoice);
}

// updates userLogin info using UserLogin pointer
void updateUserLogin(struct UserLogin *uslPtr)
{
    int userChoice;
    do
    {
        printf("\nUser Login: %s - Update Options\n", uslPtr->username);
        printf("----------------------------------------\n");
        printf("1) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        userChoice = getIntFromRange(0, 1);
        switch (userChoice)
        {
        case 1:
            printf("\n");
            getUserPassword(uslPtr->password);
            break;
        case 0:
            break;
        }
    } while (userChoice);
}

// get the user password with all specification
void getUserPassword(char *password)
{
    int i, notFound = 1;
    int digits = 0, uppCases = 0, lowCases = 0, symbols = 0;
    do
    {
        digits = 0, uppCases = 0, lowCases = 0, symbols = 0;
        printf("Enter the password (must be 8 chars in length): ");
        getCString(password, 8, 8);
        for (i = 0; password[i] != '\0'; i++)
        {
            if (password[i] >= 48 && password[i] <= 57)
            {
                digits++;
            }
            else if (password[i] >= 65 && password[i] <= 90)
            {
                uppCases++;
            }
            else if (password[i] >= 97 && password[i] <= 122)
            {
                lowCases++;
            }
            else if (
                (password[i] >= 35 && password[i] <= 38) ||
                password[i] == '!' || password[i] == '@' ||
                password[i] == '^' || password[i] == '*')
            {
                symbols++;
            }
        }
        if (digits == 2 && uppCases == 2 && lowCases == 2 && symbols == 2)
        {
            notFound = 0;
        }
        else
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("%9s Digit: 0-9\n", "");
            printf("%9s UPPERCASE character\n", "");
            printf("%9s lowercase character\n", "");
            printf("%9s symbol character: !@#$%%^&*\n", "");
            password[0] = '\0';
        }
    } while (notFound);
}
