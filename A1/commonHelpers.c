

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "commonHelpers.h"
#include <time.h>
#include <ctype.h>

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

int getInteger(void)
{
	int value;
	char newLine = 'x';
	do
	{
		scanf("%d%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (newLine != '\n');
	return value;
}

int getPositiveInteger(void)
{
	int value = -1;
	do
	{
		value = getInteger();
		if (value <= 0)
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (value <= 0);
	return value;
}

double getDouble(void)
{
	double value;
	char newLine = 'x';
	do
	{
		scanf("%lf%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (newLine != '\n');
	return value;
}

double getPositiveDouble(void)
{
	double value;
	do
	{
		value = getDouble();
		if (value <= 0)
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}
	} while (value <= 0);
	return value;
}

int getIntFromRange(int lowerInteger, int higherInteger)
{
	int rangeInteger;
	do
	{
		rangeInteger = getInteger();
		if (rangeInteger < lowerInteger || rangeInteger > higherInteger)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lowerInteger, higherInteger);
		}
	} while (rangeInteger < lowerInteger || rangeInteger > higherInteger);
	return rangeInteger;
}

//Array Length Counter
int length(const char *strings)
{
	int i = 0, l = 0;
	for (i = 0; strings[i] != '\0'; i++)
	{
		++l;
	}
	return l;
}

char getCharOption(const char validCharacters[])
{

	char singleCharacter;
	char newLine;
	int flag = 1, i;
	do
	{
		singleCharacter = '\0';
		newLine = '*';
		scanf("%c%c", &singleCharacter, &newLine);
		if (newLine == '\n')
		{
			for (i = 0; validCharacters[i] != '\0'; i++)
			{
				if (singleCharacter == validCharacters[i])
				{
					flag = 0;
				}
			}
			if (flag)
			{
				printf("ERROR: Character must be one of [%s]: ", validCharacters);
				// clearStanadardInputBuffer();
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", validCharacters);
			// clearStandardInputBuffer();
		}
	} while (flag);
	return singleCharacter;
}

void copy(char *from, char *to)
{
	int i;
	for (i = 0; from[i] != '\0'; i++)
	{
		to[i] = from[i];
	}
	to[i] = '\0';
	return;
}

void getCString(char *s, int lowerBound, int upperBound)
{
	char myLine[151];
	int len = 0;
	while (1)
	{
		scanf("%[^\n]%*c", myLine);
		len = length(myLine);
		if (upperBound == lowerBound)
		{
			if (len != upperBound)
			{
				printf("ERROR: String length must be exactly %d chars: ", lowerBound);
				*myLine = '\0';
			}
			else
			{
				copy(myLine, s);
				break;
			}
		}
		else if (len > upperBound)
		{
			printf("ERROR: String length must be no more than %d chars: ", upperBound);
			*myLine = '\0';
		}
		else if (len < lowerBound)
		{
			printf("ERROR: String length must be between %d and %d chars: ", lowerBound, upperBound);
			*myLine = '\0';
		}
		else
		{
			copy(myLine, s);
			break;
		}
	}
}

void getCStringUserName(char *s)
{
	char myLine[100];
	int i, checkSpace;
	while (1)
	{
		checkSpace = 0;
		getCString(myLine, 1, 10);
		for (i = 0; myLine[i] != '\0'; i++)
		{
			if (myLine[i] == ' ')
			{
				checkSpace = 1;
				break;
			}
		}
		if (checkSpace) {
			printf("ERROR: The user login must NOT contain whitespace characters.\n");
			printf("Enter user login (10 chars max): ");
			*myLine = '\0';
		}
		else
			break;
	}
	copy(myLine, s);
	return;
}

void getCStringPassword(char *s) {
	int i, checkPass = 1;
	do {
		getCString(s, 8, 8);
		int capitalCase = 0, lowerCase = 0, numCase = 0, symCase = 0;
		for (i = 0; i < 8; i++)
		{
			if (isdigit(s[i]))
				numCase++;
			else if (isupper(s[i]))
				capitalCase++;
			else if (islower(s[i]))
				lowerCase++;
			else if (s[i] == '!'|| s[i] == '@' ||
					s[i] == '#' || s[i] == '$' ||
					s[i] == '%' || s[i] == '^' ||
					s[i] == '&' || s[i] == '*') 
					symCase++;
		}
		if (capitalCase != 2 || lowerCase != 2 || numCase != 2 || symCase != 2)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("%16s character: !@#$%%^&*\n","symbol");
			printf("Enter the password(must be 8 chars in length) : ");
		}
		else {
			checkPass = 0;
		}
	} while (checkPass);
	return;
}

void getCStringCountry(char* s) {
	int i;
	getCString(s, 1, 30);
	for (i = 0; s[i] != '\0'; i++)
	{	
		if (s[i]>=97)
		{
			s[i] = s[i] - 32;
		}
	}
}