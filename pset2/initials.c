// A program that takes user input and returns the first letter of word in uppercase.
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define BLANK ' '

int main(void)
{
    string name = get_string();
    char initials[strlen(name)];
    int count = 0;
    
    for(int i = 0, n = strlen(name); i < n; i++)
    {
        if (i == 0 && name[i] !=BLANK)
        {
           initials[count] = toupper(name[i]); 
           printf("%c", initials[count]);
           count++;
        }
        else if (name[i] == BLANK && name[i+1] != BLANK && name[i+1] != '\0')
        {
           initials[count] = toupper(name[i+1]);
           printf("%c", initials[count]);
           count++;
        }
    }
    printf("\n");
}