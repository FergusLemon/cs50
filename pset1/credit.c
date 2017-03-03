/* A program that implements Luhn's Algorithm for verifying if a credit card number is a valid number (not necessarily
a genuine card).  Program prompts for and takes a user input and returns the name of the card provider (Amex, Mastercard
or Visa) if valid and invalid if not. */

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#define VISA_LENGTH_1 13
#define VISA_LENGTH_2 16
#define VISA_PREFIX_START 40
#define VISA_PREFIX_END 49
#define AMEX_LENGTH 15
#define AMEX_PREFIX_1 34
#define AMEX_PREFIX_2 37
#define INVALID "INVALID"
#define AMEX "AMEX"
#define MASTERCARD "MASTERCARD"
#define VISA "VISA"
#define ZERO 0
#define TWO 2
#define TEN 10

int numberOfDigits(long long cc_num);
void resetTempCopy(long long cc_num_copy, long long cc_num);
int firstTwoDigits(long long cc_num, int cc_num_length);
int calculateSumOfValues(int count, long long cc_num);
int luhnsAlgorithmCalc(int *cc_num_array, int cc_num_array_size);
bool isEvenIndex(int index);
int calculateProduct(int number);
bool isValid(int sum);
void checkCardProvider(int count, int prefix);
bool isVisa(int length, int prefix);
bool isAmex(int length, int prefix);


int main (void)
{
   printf("Number: ");
   long long creditcard_num = GetLongLong();
   long long creditcard_num_copy = creditcard_num;
   int count = numberOfDigits(creditcard_num_copy);
   resetTempCopy(creditcard_num_copy, creditcard_num);
   int prefix = firstTwoDigits(creditcard_num_copy, count);
   int luhns_total = calculateSumOfValues(count, creditcard_num);
   if(isValid(luhns_total))
   {
      checkCardProvider(count, prefix);
   }
   else
   {
      printf("%s\n", INVALID);
   }
}

int numberOfDigits(long long cc_num)
{
   int count = ZERO;
   while (cc_num != ZERO)
   {
       cc_num /= TEN;
       count++;
   }
   return count;
}

void resetTempCopy(long long cc_num_copy, long long cc_num)
{
   cc_num_copy = cc_num;
}

int firstTwoDigits(long long cc_num, int cc_num_length)
{
   int exponent = cc_num_length - TWO;
   int base = TEN;
   long long power = pow(base, exponent);
   int first_two_digits = cc_num / power;
   return first_two_digits;
}

int calculateSumOfValues(int count, long long cc_num)
{
   int cc_num_reversed[count];
   int total = ZERO;
   for(int i = ZERO; i < count; i++)
   {
      cc_num_reversed[i] = cc_num%TEN;
      cc_num /= TEN;
   }
   total = luhnsAlgorithmCalc(cc_num_reversed, count);
   return total;
}

int luhnsAlgorithmCalc(int *cc_num_array, int cc_num_length)
{
   int sum = ZERO;
   for(int i = ZERO; i < cc_num_length; i++)
   {
      if(isEvenIndex(i))
      {
         sum += cc_num_array[i];
      }
      else
      {
         int product = calculateProduct(cc_num_array[i]);
         sum += product;
      }
   }
   return sum;
}

bool isEvenIndex(int index)
{
   if(index%TWO == ZERO)
   {
      return true;
   }
   else
   {
      return false;
   }
}

int calculateProduct(int number)
{
   int sum = ZERO;
   int doubled_amount = number * TWO;
   if(doubled_amount < TEN)
   {
      sum += doubled_amount;
   }
   else
   {
      while(doubled_amount > ZERO)
      {
         sum += doubled_amount%TEN;
         doubled_amount /= TEN;
      }
   }
   return sum;
}

bool isValid(int sum)
{
   if(sum %TEN == ZERO)
   {
      return true;
   }
   else
   {
      return false;
   }
}

void checkCardProvider(int length, int prefix)
{
   if (isVisa(length, prefix))
   {
      printf("%s\n", VISA);
   }
   else if (isAmex(length, prefix))
   {
      printf("%s\n", AMEX);
   }
   else
   {
      printf("%s\n", MASTERCARD);
   }
}


bool isVisa(int length, int prefix)
{
   if((length == VISA_LENGTH_1 || length == VISA_LENGTH_2) && (prefix >= AMEX_PREFIX_1 && prefix <= VISA_PREFIX_END))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool isAmex(int length, int prefix)
{
   if((length == AMEX_LENGTH) && (prefix>= AMEX_PREFIX_1 || prefix <= AMEX_PREFIX_2))
   {
      return true;
   }
   else
   {
      return false;
   }
}
