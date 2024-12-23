#include <stdio.h>
#include <string.h>
#define HASHTABLESIZE 15

int Alphanumeric(char name[25])
{
   int value = 0, i = 0;
   
   for (i = 0; i < strlen(name)-1; i++)
   {
      value = value + name[i];
   }
   return value % HASHTABLESIZE;
}

int main (void)
{
   char key[25] = {};

   printf("Enter a key:");
   fgets(key, sizeof(key), stdin);

   printf("\nThe hash value for %s is %d\n", key, Alphanumeric(key));
   return 0;
}