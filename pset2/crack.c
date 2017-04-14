/* Program that cracks a 4 character password made up of uppercase and lowercase alphabetic characters
only.  The user is required to pass the hash of their password as a comman line argument to the program.
The program only cracks passwords that have been hashed using C's DES-based #crypt function. */ 

#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define UPPERCASE_A_ASCII 65
#define UPPERCASE_Z_ASCII 90
#define LOWERCASE_A_ASCII 97
#define LOWERCASE_Z_ASCII 122
#define LOWERCASE_A 'a'
#define NULL_OPERATOR '\0'
// 52 represents one full cycle through 26 lowercase letters and 26 uppercase letters
#define FULL_CYCLE 52
#define SALT_ARRAY_LENGTH 3
#define GUESS_ARRAY_LENGTH 5

char getSalt(string hashed_input, int index);
string updateGuess(string hashed_password, string salt_array);
int updateLetter(char letter);
bool isInRange(char letter);
bool isAnyUppercaseExceptZ(char letter);
bool isAnyLowercaseExceptZ(char letter);
bool isFullCycleComplete(int count1, int count2);
string hashGuess(string word, string salt);
bool checkMatch(string hashed_password, string hashed_guess);

int main(int argc, string argv[]) 
{
    if(argc != 2)
    {
        printf("Please enter your hashed password only, so I can CRACK it!\n");
        return 1;
    }
    else
    {
        string hashed_password = argv[1];
        char salt0 = getSalt(hashed_password, 0);
        char salt1 = getSalt(hashed_password, 1);
        char salt_array[SALT_ARRAY_LENGTH] = {salt0, salt1, NULL_OPERATOR};
        string guess = updateGuess(hashed_password, salt_array);
        printf("%s\n", guess);
    }
}

char getSalt(string hashed_input, int index)
{
    char salt_char = hashed_input[index];
    return salt_char;
}

string updateGuess(string hashed_password, string salt)
{
    int char_zero_update_count = 0;
    int char_one_update_count = 0;
    int char_two_update_count = 0;
    int char_three_update_count = 0;
    char guess_array[GUESS_ARRAY_LENGTH] = {LOWERCASE_A, LOWERCASE_A, LOWERCASE_A, LOWERCASE_A, NULL_OPERATOR};
    string guess = guess_array;
    string hashed_guess = hashGuess(guess, salt);
    while(checkMatch(hashed_password, hashed_guess))
    {
        if(char_zero_update_count < FULL_CYCLE)
        {
            guess[0] = updateLetter(guess[0]);
            hashed_guess = hashGuess(guess, salt);
            char_zero_update_count+= 1;
        }
        else if(isFullCycleComplete(char_zero_update_count, char_one_update_count))
        {
            guess[1] = updateLetter(guess[1]);
            char_one_update_count++;
            char_zero_update_count = 0;
        }
        else if(isFullCycleComplete(char_one_update_count, char_two_update_count))
        {
            guess[2] = updateLetter(guess[2]);
            //TODO - DRY out code
            char_two_update_count++;
            char_one_update_count = 0;
            char_zero_update_count = 0;
        }
        else
        {
            guess[3] = updateLetter(guess[3]);
            //TODO - DRY out code
            char_three_update_count++;
            char_two_update_count = 0;
            char_one_update_count = 0;
            char_zero_update_count = 0;
        }
    }
    return guess;
}

int updateLetter(char letter)
{
    if(isInRange(letter))
        {
            letter++;
        }
    else if(letter == UPPERCASE_Z_ASCII)
        {
            letter += (LOWERCASE_A_ASCII - UPPERCASE_Z_ASCII);
        }
    else if(letter == LOWERCASE_Z_ASCII)
        {
            letter -= (LOWERCASE_Z_ASCII - UPPERCASE_A_ASCII);
        }
    else
        {
            return 1;
        } 
    return letter;
}

bool isInRange(char letter)
{
    if(isAnyUppercaseExceptZ(letter) || isAnyLowercaseExceptZ(letter))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isAnyUppercaseExceptZ(char letter)
{
    if(letter >= UPPERCASE_A_ASCII && letter < UPPERCASE_Z_ASCII)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isAnyLowercaseExceptZ(char letter)
{
    if(letter >= LOWERCASE_A_ASCII && letter < LOWERCASE_Z_ASCII)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isFullCycleComplete(int count1, int count2)
{
    if(count1 == FULL_CYCLE && count2 != FULL_CYCLE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string hashGuess(string word, string salt)
{
    string hashed_guess = crypt(word, salt);
    return hashed_guess;
}

bool checkMatch(string hashed_password, string hashed_guess)
{
    if(strcmp(hashed_password, hashed_guess) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}