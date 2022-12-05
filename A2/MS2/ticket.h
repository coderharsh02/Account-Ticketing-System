// #############################################################################################
//  Assignment: 2
//  Milestone : 2
// #############################################################################################

#ifndef TICKET_H_
#define TICKET_H_
#include "account.h"

// Message Structure
struct Message
{
	char accountType;
	char fullName[31];
	char message[151];
};
// Ticket Structure
struct Ticket
{
	int ticNum;
	int cusAccNum;
	int ticStatus;
	char ticSubject[31];
	int ticMesCounter;
	struct Message ticMesArr[20];
};

void getTicket(struct Ticket *ticketPtr, const struct Account *accPtr);	 // get the new ticket details from the agent and returns it using modifiable Ticket pointer
void manageTick(struct Ticket *ticketPtr, const struct Account *accPtr); // manages the ticket giving different option

#endif // !TICKET_H_