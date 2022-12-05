//
// Your identification information commented header goes here...
//
#ifndef ACCOUNT_TICKETING_H_
#define ACCOUNT_TICKETING_H_

#include "account.h"
#include "ticket.h"

struct AccountTicketingData
{
    struct Account *accounts;   // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array
    struct Ticket *tickets;     // array of tickets
    const int TICKET_MAX_SIZE;  // maximum elements for ticket array
};

void displayAccountDetailHeader(void);                         // display account detail header
void displayAccountDetailRecord(const struct Account *accPtr); // display account details

void applicationStartup(struct AccountTicketingData *accTicPtr);                                             // provides entry point to application
int menuLogin(const struct Account accountArr[], int max);                                                // navigation menu for login
void menuAgent(struct AccountTicketingData *accTicPtr, const struct Account *accPtr);                       // navigation for agents
int findAccountIndexByAcctNum(int accountNumber, const struct Account accountArr[], int max, int prompt); // returns index for an account number
void displayAllAccountDetailRecords(const struct Account accountArr[], int max);                          // display all account details
void pauseExecution();                                                                                    // pause execution till user press enter key

#endif // !ACCOUNT_TICKETING_H_