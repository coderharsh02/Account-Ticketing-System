// #############################################################################################
//  Assignment: 1 
//  Milestone : 4
// #############################################################################################

#ifndef ACCOUNT_TICKETING_H_
#define ACCOUNT_TICKETING_H_

#include "account.h"

void displayAccountDetailHeader(void);                         // display account detail header
void displayAccountDetailRecord(const struct Account *accPtr); // display account details

void applicationStartup(struct Account accountArr[], int max);                                            // provides entry point to application
int menuLogin(const struct Account accountArr[], int max);                                                // navigation menu for login
void menuAgent(struct Account accountArr[], int max, const struct Account *accPtr);                       // navigation for agents
int findAccountIndexByAcctNum(int accountNumber, const struct Account accountArr[], int max, int prompt); // returns index for an account number
void displayAllAccountDetailRecords(const struct Account accountArr[], int max);                          // display all account details
void pauseExecution();                                                                                    // pause execution till user press enter key

#endif // !ACCOUNT_TICKETING_H_