// #############################################################################################
//  Assignment: 2
//  Milestone : 4
// #############################################################################################

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

// Application Data Retrieval From Text Files
int loadAccounts(struct Account accountArr[], int maxSize); // loads data from accounts.txt file to accounts array
int loadTickets(struct Ticket ticketArr[], int maxSize);    // loads data from tickets.txt file to tickets array

int saveAccounts(const struct Account accountArr[], int maxSize);
int saveTickets(const struct Ticket ticketArr[], int maxSize);

// Application Logic Functions
void applicationStartup(struct AccountTicketingData *accTicPtr);                                          // provides entry point to application
int menuLogin(const struct Account accountArr[], int max);                                                // navigation menu for login
void menuAgent(struct AccountTicketingData *accTicPtr, const struct Account *accPtr);                     // navigation menu for agents
int findAccountIndexByAcctNum(int accountNumber, const struct Account accountArr[], int max, int prompt); // returns index for an account number
int findTicketIndexByTicNum(int ticketNumber, const struct Ticket ticketArr[], int max, int prompt);      // returns index for a ticket number
void pauseExecution();                                                                                    // pause execution till user press enter key

// Account Displaying Functions
void displayAccountDetailHeader(void);                                           // display account detail header
void displayAccountDetailRecord(const struct Account *accPtr);                   // display account details
void displayAllAccountDetailRecords(const struct Account accountArr[], int max); // display all account details

// Ticket Displaying Functions
void displayTicketDetailHeader(void);                                             // display Ticket detail header
void displayTicketDetailRecord(const struct Ticket *ticketPtr);                   // display ticket details
void displayTicketMessage(const struct Ticket *ticketPtr);                        // display Ticket's messages
void displayNewTicketsDetailRecords(const struct Ticket ticketArr[], int max);    // display New tickets detailed records
void displayActiveTicketsDetailRecords(const struct Ticket ticketArr[], int max); // display Active tickets detailed records
void displayCloseTicketsDetailRecords(const struct Ticket ticketArr[], int max);  // display Closed tickets detailed records

#endif // !ACCOUNT_TICKETING_H_