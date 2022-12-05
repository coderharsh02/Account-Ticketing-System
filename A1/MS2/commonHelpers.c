// #############################################################################################
//  Assignment: 1
//  Milestone : 2
// #############################################################################################

#include <stdio.h>
#include <time.h>
#include "commonHelpers.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing
    }
}
int getInteger(void)
{
    char newLine = 'x';
    int value;
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
    int value = getInteger();
    while (value <= 0)
    {
        printf("ERROR: Value must be a positive integer greater than zero: ");
        value = getInteger();
    }
    return value;
}
double getDouble(void)
{
    char newLine = 'x';
    double value;
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
    double value = getDouble();
    while (value <= 0)
    {
        printf("ERROR: Value must be a positive double floating-point number: ");
        value = getDouble();
    }
    return value;
}
int getIntFromRange(int lowerBound, int upperBound)
{
    int value = getInteger();
    while (value > upperBound || value < lowerBound)
    {
        printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        value = getInteger();
    }
    return value;
}
char getCharOption(const char validChars[])
{
    int c, flag = 1, len, i;
    char res;
    do
    {
        len = 0;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            res = (char)c;
            len++;
        }
        if (len == 1)
        {
            for (i = 0; validChars[i] != '\0' && flag; i++)
                if (res == validChars[i])
                    flag = 0;

        }
        if(flag)
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
    } while (flag);
    return res;
}
void getCString(char *cstringPtr, int min, int max)
{
    int strLen, c, flag = 0;
    do
    {
        flag = 0;
        strLen = 0;
        while ((c = getchar()) != '\n' && c != EOF)
            cstringPtr[strLen++] = (char)c;
        cstringPtr[strLen] = '\0';
        if (min == max)
        {
            if (strLen != max)
            {
                flag = 1;
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
        }
        else if (strLen < min)
        {
            flag = 1;
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
        }
        else if (strLen > max)
        {
            flag = 1;
            printf("ERROR: String length must be no more than %d chars: ", max);
        }
    } while (flag);
}