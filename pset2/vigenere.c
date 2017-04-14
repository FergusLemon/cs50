/* program that implements Vigenere's cipher.  Takes a command like argument representing the key, a user generated
input as the plaintext and returns the encrypted value */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define UPPERCASE_A_ASCII 65
#define UPPERCASE_Z_ASCII 90
#define LOWERCASE_A_ASCII 97
#define LOWERCASE_Z_ASCII 122

bool isKeyInvalid(string key);
int numberOfLettersInString(string key);
void encryptText(string plaintext, string keyword);
int convertToAscii(string keyword, int n);
int rebaseAsciiToVigenere(int m);
char checkValueToAddToCiphertext(int original_value, int new_value);
bool isUppercase(char letter);
bool isLowercase(char letter);
// function to keep track of characters used in the key and recycle them when the last one is used
int updateKeyCount(int key_count, int key_length);


int main(int argc, string argv[]) 
{
    if(argc != 2)
    {
        printf("Please enter a single valid keyword.\n");
        return 1;
    }    
    else if(isKeyInvalid(argv[1]))
    {
        printf("Please enter a keyword containing only letters between a-z or A-Z.\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        printf("plaintext: ");
        string plaintext = get_string();
        printf("ciphertext: ");
        encryptText(plaintext, key);
        printf("\n");
        return 0;    
    }
}

bool isKeyInvalid(string key)
{
    int letters = numberOfLettersInString(key);
    int length_of_key = strlen(key);
    if(letters < length_of_key)
    {
        return true;
    }
    return false;
}

int numberOfLettersInString(string key)
{
    int length_of_key = strlen(key);
    int count = 0;
    for(int i = 0; i < length_of_key; i++)
    {
        if(isalpha(key[i]))
        {
            count++;
        }
    }
    return count;
}

void encryptText(string plaintext, string keyword)
{
    int plaintext_length = strlen(plaintext);
    int key_length = strlen(keyword);
    char ciphertext[plaintext_length];
    int c = 0;
    
    for(int j = 0; j < plaintext_length; j++)
    {
        if(isalpha(plaintext[j]))
        {
            int key_value = convertToAscii(keyword, c);
            int vigenere_value = rebaseAsciiToVigenere(key_value);
            int converted_value = plaintext[j] + vigenere_value;
            char encrypted_char = checkValueToAddToCiphertext(plaintext[j], converted_value);
            ciphertext[j] = encrypted_char;
            c = updateKeyCount(c, key_length);
        }
        else
        {
            ciphertext[j] = plaintext[j];
        }
    }
    
    for(int k = 0; k < plaintext_length; k++)
    {
        printf("%c", ciphertext[k]);
    }
}

int convertToAscii(string keyword, int n)
{
    int ascii_value = toupper(keyword[n]);
    return ascii_value;
}

int rebaseAsciiToVigenere(int m)
{
    int vigenere_value = m - UPPERCASE_A_ASCII;
    return vigenere_value;
}

char checkValueToAddToCiphertext(int original_value, int new_value)
{
    if(isUppercase(original_value) && (new_value > UPPERCASE_Z_ASCII))
    {
        char updated_value = UPPERCASE_A_ASCII + (new_value - UPPERCASE_Z_ASCII - 1);
        return updated_value;
    }
    else if(isLowercase(original_value) && (new_value > LOWERCASE_Z_ASCII))
    {
        char updated_value = LOWERCASE_A_ASCII + (new_value - LOWERCASE_Z_ASCII - 1);
        return updated_value;
    }
    else
    {
        return (char) new_value;
    }
}

bool isUppercase(char letter)
{
    if(letter >= UPPERCASE_A_ASCII && letter <= UPPERCASE_Z_ASCII)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isLowercase(char letter)
{
    if(letter >= LOWERCASE_A_ASCII && letter <= LOWERCASE_Z_ASCII)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// function to keep track of the number of chars in the key used for encryption and recycle the chars if needed
int updateKeyCount(int key_count, int key_length)
{
    if(key_count < (key_length - 1))
    {
        key_count++;
    }
    else
    {
        key_count = 0;
    }
    return key_count;
}