#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
// struct Account account = { 0 };
// struct UserLogin login = { {0} };
// struct Demographic demographic = { 0 };

// get the account details from the user and returns it using modifiable Account pointer
void getAccount(struct Account *accPtr)
{
    printf("Account Data: New Record\n");
    printf("----------------------------------------\n");
    printf("Enter the account number: ");
    accPtr->accountNumber = getInteger();
    printf("Enter the account type (A=Agent | C=Customer): ");
    accPtr->accountType = getCharOption("AC");
    printf("\n");
}
// get the inputs for Person structure from the user and returns it using modifiable Person pointer
void getPerson(struct Person *perPtr)
{
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
    printf("\n");
}
// get the inputs for UserLogin structure from the user and returns it using modifiable UserLogin pointer
void getUserLogin(struct UserLogin *uslPtr)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter user login (10 chars max): ");
    getCString(uslPtr->username, 1, 10);
    printf("Enter the password (must be 8 chars in length): ");
    getCString(uslPtr->password, 8, 8);
    printf("\n");
}