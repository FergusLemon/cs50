// A program that takes a user input and recreates a Pyramid from the computer game Mario.

#include <stdio.h>
#include <cs50.h>
// a constant to represent the max number of blocks in a row of a pyramid on either side of the gap
#define BLOCKS "########################"
// a constant to represent the max number of blanks in a row of a pyramid on either side of the gap
#define BLANKS "                        "
// a constant to represent the two space gap in between the walls of the pyramid
#define GAP "  "

int main (void)
{
    int height;
    int i;
    
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    for( i = 0; i < height; i++ )
    {
        int n = (height -1) - i;
        printf("%.*s", n, BLANKS);
        printf("%.*s", (i + 1), BLOCKS);
        printf("%s", GAP);
        printf("%.*s\n", (i + 1), BLOCKS);
    }
}