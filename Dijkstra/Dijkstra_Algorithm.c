/*
	Dijkstra's algorithm is an algorithm for finding the 
	shortest paths between nodes in a weighted graph,
	I have provided a PDF sample Drawing of what the 
	path should look like.

	(OPTIONAL) When you compile you may use the 
	gcc -DPRINTARRAY Dijkstra_Algorithm.c
	to print the value before and after sorting.

	NOTE: A graph.txt is provided instead of the
	TestFile list of Number.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define VertexCount 5
#define MAX 50

typedef struct
{
	char label[6];
	int distance;
	int previous;
	int visited;
}
Vertex;

void ReadFileIntoArray(int argc, char *argv[], int Matrix[][VertexCount], Vertex VertexArray[]) //remeber to include something on the 2D of the array
{
	char *file_name = argv[1];
	char num [MAX] = {};
	int row = 0;
	int col, val;
	char *token = NULL;															  										
	
	FILE *file = NULL;
	file = fopen(file_name, "r");

	if (file == NULL)
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	else
	{
		while(fgets(num, sizeof(num), file) != NULL)
		{
			if (num[strlen(num)-1] == '\n')		//This removes a vertex without edge. So we don't worry about it.
				num[strlen(num)-1] = '\0';

			token = strtok(num, ",");								//tokenize the first one for the letter/Vertex
			strcpy(VertexArray[row].label, token);				// ran into a problem where I couldn't use '=' so we used strcpy

			while ((token = strtok(NULL, ",")) != NULL)	// we don't need to use 'num' as a buffer now we can use NULL to start right where we left off
			{
				//token = strtok(num, ",");
				col = atoi(token);							//The hardest part of the code:
				//													I did't knew where to store vertex adj / neighbor number
				//													bruh, solution: use it as a column for matrix...since they are array.
				token = strtok(NULL, ",");
				val = atoi(token);

				Matrix[row][col] = val;						//now store the 2 number into matrix
			}
			row++;						
		}
		fclose(file);
	}
}

void Convert(char vertex_Letter[], int *array_num, Vertex Label[])
{
	int i = 0;

	while (strcmp(Label[i].label, vertex_Letter) != 0 && i < VertexCount)  //again use strcmp because of the issue with char, also while loop is way better.
	{																							//NOTE: 0 = True so while it's not true, keep looking.
		i++;
	}
	*array_num = i;			
}

void Dijkstra( int AdjMatrix[][VertexCount], Vertex VertexArray[],int StartVertex)
{
	int x, i;
	int CurrentVertex = StartVertex;
	VertexArray[StartVertex].distance = 0;
	VertexArray[StartVertex].previous = -1;
	VertexArray[StartVertex].visited = 1;

	for (x = 0; x < VertexCount-1; x++)
	{
		for(i = 0; i < VertexCount; i++)
		{
			if (AdjMatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited)
			{
				if (VertexArray[CurrentVertex].distance +AdjMatrix[CurrentVertex][i] < VertexArray[i].distance)
				{
					VertexArray[i].distance = VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i];
					VertexArray[i].previous = CurrentVertex;
				}
			}
		}

		int SmallestVertexIndex = -1;
		int SmallestVertex = INT_MAX;

		for(i = 0; i < VertexCount; i++)
		{
			if (!VertexArray[i].visited)
			{
				if (VertexArray[i].distance < SmallestVertex)
				{
					SmallestVertex = VertexArray[i].distance;
					SmallestVertexIndex = i;
				}
			}
		}
		CurrentVertex = SmallestVertexIndex;
		VertexArray[CurrentVertex].visited = 1;
	}
}

void ThePath(int index, Vertex VertexArray[])
{
	int i = 0;
	int length, end;
	int path[MAX] = {};

	length = VertexArray[index].distance;// Saved the number to be used to print later
	end =  index;
	
	while(VertexArray[index].previous != -1)
	{
		path[i] = index;
		index = VertexArray[index].previous;
		i++;
	}
	path[i] = index;

	printf("The path from %s to %s is %s", VertexArray[index].label,VertexArray[end].label,VertexArray[index].label);// I wanted to get -> in correct order so hence why it's repeated 
	while( i > 0)																																		//multiple times
	{
		i--;
		printf("->%s", VertexArray[path[i]].label);
	}
	printf(" and has a length of %d \n", length);
}

int main(int argc, char *argv[])
{
	char start[MAX] = {}, destination[MAX] = {};
   int i,j;
	int index = 0;
	Vertex VertexArray[VertexCount] = {};   			//NOTE: VertexArray would be PASSED for ALL FUNCTIOn, it carries all the Info
   int AdjMatrix[VertexCount][VertexCount] = {};

   for(i = 0; i < VertexCount; i++)				//we initalized Matrix and VertexArray with -1 , 0 and max value.
   {
      for(j = 0; j < VertexCount; j++)
      {
         AdjMatrix[i][j] = -1;
      }
   }

	for (i = 0; i < VertexCount; i++)
	{
		strcpy(VertexArray[i].label, "");			// Dealing with struct char use strcpy and strcmp, to work values
		VertexArray[i].distance = INT_MAX;
		VertexArray[i].previous = -1;
		VertexArray[i].visited = 0;
	}

	ReadFileIntoArray(argc, argv, AdjMatrix, VertexArray);

	#ifdef PRINTIT
	printf("\n");
	for(i = 0 ; i < VertexCount; i ++)
	{
		for(j = 0; j < VertexCount; j ++)
			printf("%5d\t", AdjMatrix[i][j]);
		printf("\n");
	}
	#endif

	printf("\nWhat is the starting vertex?: "); //eventhough it was one letter... strings are better
	scanf(" %s", start);

	Convert(start, &index, VertexArray);
	Dijkstra(AdjMatrix, VertexArray, index);

	#ifdef PRINTIT
	printf("\n\nI\tL\tD\tP\tV\n");
	for(i = 0; i < VertexCount; i ++)
	{
		printf("%d\t%s\t%d\t%d\t%d\n", i, VertexArray[i].label,VertexArray[i].distance, VertexArray[i].previous, VertexArray[i].visited);
		printf("\n");
	}
	#endif

	printf("\nWhat is the destination vertex?: ");
	scanf(" %s", destination);

	Convert(destination, &index, VertexArray);
	ThePath(index, VertexArray);

   return 0;
}