// #############################################################################################
//  Assignment: 1
//  Milestone : 2
// #############################################################################################

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

struct Person
{
    char fullName[31];
	int birthYear;
	double houseHoldIncome;
	char cntyName[31];
};
struct UserLogin {
	char username[11];
	char password[9];
};
struct Account {
	int accountNumber;
	char accountType;
};

#endif