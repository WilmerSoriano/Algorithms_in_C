/* InsertionSort by Wilmer Soriano*/


#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void FileHand_ArrayFill(int argc, char *argv[],int **array, int *Size)
{
	char *file_name = argv[1];
	char num [10] = {};
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
		while(fgets(num, sizeof(num), file) != NULL)			//This loops as follows
		{
			line++;												
		}

		fseek(file, 0, SEEK_SET);
		*array = (int*)malloc(line * sizeof(int));
		*Size = line;

		while(a < line)
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

void InsertionSort(int *A, int n)
{
	int i, key, j;

	for(j = 1; j < n; j++)
	{
		key = A[j];
		i= j - 1;

		while (i >= 0 && A[i] > key)
		{
			A [i + 1] = A[i];
			i = i -1;
		}
		A [i + 1] = key;
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