/*
	Takes in parameter for test file and sort
	the list in order from least to greatest using
	the Quick Sort Algorithm.

	(OPTIONAL) When you compile you may use the 
	gcc -DPRINTARRAY QuickSort.c
	to print the value before and after sorting.
*/

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void ReadFileIntoArray(int argc, char *argv[], int **array, int *Size)
{
	char *file_name = argv[1];
	char num [10] = {};
	int records = 0;
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
		while(fgets(num, sizeof(num), file) != NULL)			//Loops to just count the line in a file
		{
			records++;												
		}

		fseek(file, 0, SEEK_SET);
		*array = malloc(records * sizeof(int));  // resets file and save the info 
		*Size = records;

		while(a < records)					//start saving line with numbers into arraY
		{
			fgets(num, sizeof(num), file);
			(*array)[a] = atoi(num);
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

void swap(int *SwapA, int *SwapB)
{
	int temp = *SwapA;
	*SwapA = *SwapB;
	*SwapB = temp;
}

int partition (int A[], int low, int high)
{
	#if QSM
	int middle = (high+low)/2;
	swap(&A[middle], &A[high]);
	#elif QSRND
	int random = (rand() % (high-low+1)) + low;
	swap(&A[random], &A[high]);
	#endif
	int pivot = A[high];

	int i, j = 0;
	i = (low - 1);
	for (j = low; j < high; j++)
	{
		if (A[j] < pivot)
		{
			i++;
			swap(&A[i], &A[j]);
		}
	}
	swap(&A[i + 1], &A[high]);
	return (i + 1);
}

void QuickSort(int A[], int low, int high)
{
	if (low < high)
	{
		int ndx = partition(A, low, high);
		QuickSort(A, low, ndx - 1);
		QuickSort(A, ndx + 1, high);
	}
}

int main(int argc, char* argv[])
{ 
	clock_t start, end, start2, end2;
	int Elements = 0;
	int *AP = NULL;
	int total_tic = 0;
	int runs ;
	int a;
	//					Turns out argc just counts the number of parameter we type in the command including
	if( argc < 3) 	/*the compile part which start from argv[0] then next line argv[1],[2],[3]... etc*/
	{					/*Therefore if there's less than 3, with the 3rd not having a variable set deafult to 10.*/
		printf("Number of runs not specified on command line...defaulting to 10\n");
		runs = 10;
	}
	else
	{
		runs = atoi(argv[2]);  //otherwise convert the 3rd parameter into an intenger.
	}

	for(a = 0; a < runs; a++)
	{
		ReadFileIntoArray(argc, argv, &AP, &Elements);  
                                                  
		#ifdef PRINTARRAY											
		printf("\nBefore Quick Sort:\n");
		PrintArray( AP, Elements);
		#endif

		start = clock();
		QuickSort(AP, 0, Elements-1);		//NOTE TO SELF: the -1 MUST be INCLUDED !!! 
		end = clock();						/*probably has to do with a NULL inside AP which element tries to count as part of the list.*/

		printf("Run %d complete : %ld tics\n", a+1, end-start);
		
		#ifdef PRINTARRAY
		printf("\nAfter Quick Sort:\n");
		PrintArray( AP, Elements);
		#endif

		free(AP);

		total_tic = end-start + total_tic;
	}
	
	printf("The avergae run time for %d run is %d\n", runs, (total_tic)/runs);	// NOTE: not instructed to round.									

	printf("\nProcessed %d records\n", Elements); 

	return 0; 
} 