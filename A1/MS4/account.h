//
// Your identification information commented header goes here...
//
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// Person Structure
struct Person
{
	char fullName[31];
	int birthYear;
	double houseHoldIncome;
	char cntyName[31];
};
// UserLogin Structure
struct UserLogin
{
	char username[11];
	char password[9];
};
// Account Structure
struct Account
{
	int accountNumber;
	char accountType;
	struct Person accountDetails;
	struct UserLogin accountCredential;
};

void getAccount(struct Account *accPtr);	 // get the account details from the user and returns it using modifiable Account pointer
void getPerson(struct Person *perPtr);		 // get the inputs for Person structure from the user and returns it using modifiable Person pointer
void getUserLogin(struct UserLogin *uslPtr); // get the inputs for UserLogin structure from the user and returns it using modifiable UserLogin pointer

void updateAccount(struct Account *accPtr);		// updates account details using Account pointer
void updatePerson(struct Person *perPtr);		// updates Person details using Person pointer
void updateUserLogin(struct UserLogin *uslPtr); // updates userLogin info using UserLogin pointer

#endif //! ACCOUNT_H_