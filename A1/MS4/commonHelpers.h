// #############################################################################################
//  Assignment: 1 
//  Milestone : 4
// #############################################################################################

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int currentYear(void);                               // Get the current 4-digit year from the system
void clearStandardInputBuffer(void);                 // Empty the standard input buffer
int getInteger(void);                                // get integer from user validate it and return it
int getPositiveInteger(void);                        // get positive integer from user validate it and return it
double getDouble(void);                              // get double from user validate it and return it
double getPositiveDouble(void);                      // get positive double from user validate it and return it
int getIntFromRange(int lowerBound, int upperBound); // get integer in range from user validate it and return it
char getCharOption(const char validChars[]);         // receive characters in array and returns user selected character
void getCString(char *cstringPtr, int min, int max); // validate the user string input according to min and max values

#endif // !COMMON_HELPERS_H_
