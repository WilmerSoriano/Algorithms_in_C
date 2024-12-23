/*Merge Sort*/
/*
	Takes in parameter for test file and sort
	the list in order from least to greatest using
	the Merge Sort Algorithm.

	(OPTIONAL) When you compile you may use the 
	gcc -DPRINTARRAY MergeSort.c
	to print the value before and after sorting.
*/

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
		while(fgets(num, sizeof(num), file) != NULL)			//Loops to just count the line in a file
		{
			line++;												
		}

		fseek(file, 0, SEEK_SET);
		*array = malloc(line * sizeof(int));  // resets file and save the info 
		*Size = line;

		while(a < line)					//start saving line with numbers into arraY
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

void merge(int arr[], int left, int middle, int right)
{
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;
	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void MergeSort(int arr[], int L, int R)
{
	if (L < R)
	{
		int M = (L+R)/2;
		MergeSort(arr, L, M);
		MergeSort(arr, M+1, R);
		merge(arr, L, M, R);
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
	clock_t start, end, start2, end2;
	int *AP = NULL;
	int Elements = 0;

	/* Assignment 3 */

	FileHand_ArrayFill(argc, argv, &AP, &Elements);  /*merge sort, also I used address to save Array*/
 //                                                   /*to Print (AP) and Elements to save only import*/
	#ifdef PRINTARRAY											/*info about array and Elements counted from file*/
	printf("Before Merge Sort:\n");
	PrintArray( AP, Elements);
	#endif

	start = clock();
	MergeSort(AP, 0, Elements-1);		//NOTE TO SELF: the -1 MUST be INCLUDED !!! probably has to do with a NULl inside AP which element tries to count.
	end = clock();
	
	#ifdef PRINTARRAY
	printf("\nAfter Merge Sort:\n");
	PrintArray( AP, Elements);
	#endif

	free(AP);													// Reset, now Insertion Sort

	FileHand_ArrayFill(argc, argv, &AP, &Elements);

	#ifdef PRINTARRAY
	printf("\nBefore InsertionSort:\n");
	PrintArray( AP, Elements);
	#endif

	start2 = clock();
	InsertionSort(AP,Elements);
	end2 = clock();

	#ifdef PRINTARRAY
	printf("\nAfter InsertionSort:\n");
	PrintArray(AP, Elements);
	#endif

	free(AP);										

	printf("\nProcessed %d \n", Elements); 

	printf("Merge Sort = %ld Tics \n", end-start);
	printf("Insertion Sort = %ld Tics \n", end2-start2);

	return 0; 
} 