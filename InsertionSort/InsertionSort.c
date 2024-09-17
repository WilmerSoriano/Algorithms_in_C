/* InsertionSort by Wilmer Soriano*/


/*
	This program take a single column of numbers (preferly hundreds-thousand digit value)
	Count each line, beging to perform an InsertionSort, and determine tick time.
	1 tick = 1 microsecond
	
	(OPTIONAL) When you compile you may use the 
		gcc -DPRINTARRAY InsertionSort.c
	to print the value before and after sorting.
*/

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void FileHand_ArrayFill(int argc, char *argv[],int **array, int *Size)
{
	char *file_name = argv[1];
	char num [10] = {};	// num is overridden every time we get a new value from a file, num does NOT store all the value.
	int line = 0;
	int a= 0;															  										
	
	FILE *file = NULL;
	file = fopen(file_name, "r");

	if (file == NULL)
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	else
	{
		while(fgets(num, sizeof(num), file) != NULL)	//Loop once to obtain the number of lines in a file.
		{
			line++;												
		}

		fseek(file, 0, SEEK_SET);						// Reset the Reader back to the beginning of the file line.
		*array = (int*)malloc(line * sizeof(int));
		*Size = line;

		while(a < line)								// Loop a 2nd time to obtain and store the values.
		{
			fgets(num, sizeof(num), file);
			(*array) [a] = atoi(num);
			a++;
		}
	}
	fclose(file);
}

void PrintArray(int ArrayToPrint[], int SizeAP)
{
	int i;

	for (i = 0; i < SizeAP; i++)
	{
		printf("%d\n", ArrayToPrint[i]);
	}
}

void InsertionSort(int *array, int Size)
{
	int i, key, j;

	for(j = 1; j < Size; j++)			// Saving the second value found in the array list
	{
		key = array[j];
		i= j - 1;

		while (i >= 0 && array[i] > key)	// Comparing the first value and second value  
		{
			array [i + 1] = array[i];
			i = i -1;
		}
		array [i + 1] = key;
	}
}

int main(int argc, char* argv[])	 
{ 
	clock_t start, end;
	int *AP = NULL;
	int Elements = 0;

	FileHand_ArrayFill(argc, argv, &AP, &Elements);

	#ifdef PRINTARRAY
	printf("Before InsertionSort:\n");
	PrintArray( AP, Elements);
	#endif

	start = clock();
	InsertionSort(AP,Elements);
	end = clock();

	#ifdef PRINTARRAY
	printf("\nAfter InsertionSort:\n");
	PrintArray(AP, Elements);
	printf("\nProcessed %d records\n", Elements);
 	#endif

	printf("\nInsertion Sort = %ld Tics \n", end-start);

	free(AP);

	return 0; 
} 