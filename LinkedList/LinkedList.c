/* LinkList by Wilmer Soriano */
/* Compile and run with Testfile.txt file */

/* 
   Detail:
   Counts the number records found in a file
   and adds them to give a total.

   The program add them each value into the
   linklist (no particular order)
   The time is counted by ticks
   1 tick = 1 microsecond

   (OPTIONAL) you may print the node information
   by using:
   gcc -DPRINT LinkedList.c 
*/ 

 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)  //Simple old Linkedlist
{
	NODE* NewNode , *TempNode;					//Remember not to set '=' to NULL

	NewNode = malloc(sizeof(struct node));
	NewNode->number = Number;
	NewNode->next_ptr = NULL;

	if(*LinkedListHead == NULL)
	{
		*LinkedListHead = NewNode;
	}
	else
	{
		TempNode = *LinkedListHead;

		while(TempNode->next_ptr != NULL)
		{
			TempNode = TempNode->next_ptr;
		}
		TempNode->next_ptr = NewNode;
	}
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
	char *file_name = argv[1];									//argv does not work with fgets hence why I stored into pointer							
	char num [100] = {};  										
	int total = 0;
	int rec = 0;
	int add;
	
	FILE *file = NULL;
	file = fopen(file_name, "r");

	if (file == NULL)
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	else
	{
		while(fgets(num,sizeof(num),file) != NULL)			//This loops as follows:
		{																	/*fgets use file and reads the first line until it meets a NULL*/
			add = 0;														/*Saves that character into num(which is a char)*/
			rec++;

			add = atoi(num);											/*Remeber that fgets returns a char/string not intenger so..*/
			total += add;												/*we use atoi to covert into intenger*/	

			AddNodeToLL(add, LLH);
		}
		printf("%d records were read for a total sum of %d\n", rec, total);
	}
	fclose(file);
}

void PrintLL(NODE *LLH) // passes LLH until the end
{ 
	NODE* OldNode;
	OldNode = LLH;

	while(OldNode != NULL) // Reads the LinkList
	{
		#ifdef PRINT
		printf("\n%p %d %p\n", OldNode, OldNode->number, OldNode->next_ptr); //prints node information
		#endif

		OldNode = OldNode->next_ptr;
	}
}

void FreeLL(NODE **LLH) 
{ 
	int total = 0;
	int del = 0;
	NODE* TempNode, *HOLD;

	TempNode = *LLH;

	while (TempNode != NULL) //As long as the reader behind has a number inside..
	{
		#ifdef PRINT
		printf("\nFreeing %p %d %p\n", TempNode, TempNode->number, TempNode->next_ptr);
		#endif
		total += TempNode->number;      // record the total

		HOLD = TempNode->next_ptr;      //Hold next node
		free(TempNode);     				 // throw away whatever the reader behind had
		TempNode = HOLD;					 // give the reader what Holder has

		del++;
	}											// repeat until the next pointer/Node is null
	*LLH = NULL;							// since the next node is a null the only node that has a number is the reader aka the Head.
	printf("\n%d nodes were deleted for a total sum of %d\n",del,total);
}

int main(int argc, char* argv[])	 
{ 
	NODE *LLH = NULL;
	clock_t start, end;

	/* capture the clock in a start time */
	start = clock();
	ReadFileIntoLL(argc, argv, &LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to write the file into the linked list\n", end-start);

	/* capture the clock in a start time */
	start = clock();
	#ifdef PRINT
	PrintLL(LLH);
	#endif
	/* capture the clock in an end time */
	end = clock();
	#ifdef PRINT
	printf("\n%ld tics to print the linked list\n", end-start);
	#endif

	/* capture the clock in a start time */
	start = clock();
	FreeLL(&LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to free the linked list\n", end-start);

	return 0; 
} 