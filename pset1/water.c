// A program that asks a user for a number of minutes and calculates the number of litres used in a shower of that duration.
#include <stdio.h>
#include <cs50.h>

int main (void)
{
    printf("minutes: ");
    int minutes = GetInt();
    int bottles = (minutes * 12);
    printf("bottles: %i\n", bottles);
}