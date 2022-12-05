// #############################################################################################
//  Assignment: 2
//  Milestone : 1
// #############################################################################################

#ifndef TICKET_H_
#define TICKET_H_
struct Message
{
	char accountType;
	char fullName[31];
	char message[151];
};

struct Ticket
{
	int ticNum;
	int cusAccNum;
	int ticStatus;
	char ticSubject[31];
	int ticMesCounter;
	struct Message ticMesArr[20];
};

#endif // !TICKET_H_