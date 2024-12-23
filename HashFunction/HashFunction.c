/*
	The HashFunction is implemented differently
	compared to the rest of the Algorithms.

	I will be using Destiny 2 (Video Game Inspiaration)
	to model the function of the Algorithm
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 15
 
/* Node for storing information */
typedef struct Exotic
{
   char *name;
   char *ammo; 
   char element; 
   char *archetype;
   int RPM; 
   int impact;
   int magazaine;
   float damage; 
   float rare;
   struct Exotic *next_ptr;
}
EXOTIC;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(EXOTIC *NewNode, EXOTIC * vault[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (vault[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		vault[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		EXOTIC *TempPtr = vault[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(EXOTIC *vault[])
{
	EXOTIC *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = vault[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				free(TempPtr->ammo);
				free(TempPtr->archetype);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(EXOTIC *vault[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Exotic to delete from the vault ");
	//fgets(LookupName, 100, stdin);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	EXOTIC *TempPtr = vault[HashIndex];
	EXOTIC *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nExotic %s does not exist in the vault\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == vault[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					vault[HashIndex] = TempPtr->next_ptr;
					printf("\nExotic %s has been deleted from the vault\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nExotic %s has been deleted from the vault\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nExotic %s does not exist in the vault\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(EXOTIC *vault[])
{
	int i;
	EXOTIC *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = vault[i];

		printf("\nvault[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(EXOTIC *vault[])
{
	int i;
	EXOTIC *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = vault[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(EXOTIC *vault[])
{
	EXOTIC *TempPtr = NULL;
	char damage[10] = {};
	char full[10] = {};
	char exact[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Exotic name ");
//	fgets(LookupName, 100, stdin);
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = vault[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					
					printf("damage\t\t");
					sprintf(damage, "%.3f", TempPtr->damage);
					for (int i = 0; i < strlen(damage); i++)
					{
						if (damage[i] == '.')
						{
							printf("\' ");
						}
						else
						{
							printf("%c", damage[i]);
						}
					}
					printf("\"\n");
					printf("rare\t\t%.1f lbs\n", TempPtr->rare);
					if (TempPtr->element == 'B')
						printf("Element\t\tM F\n");
					else if (TempPtr->element == 'U')
						printf("Element\t\tUnknown\n");
					else
						printf("Element\t\t%c\n", TempPtr->element);
					printf("Ammo\t%s\n", TempPtr->ammo);
					printf("Achetype\t%s\n", TempPtr->archetype);
					printf("RPM\t%d\n", TempPtr->RPM);
					printf("Impact \t%d\n", TempPtr->impact);
					printf("Magazaine size\t%d\n", TempPtr->magazaine);

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nExotic %s not found in vault\n\n", LookupName);
}

void AddNewPokemon(EXOTIC *vault[])
{
	int HashIndex = 0;
	EXOTIC *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(EXOTIC));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Exotic name ");
	fgets(TempBuffer, sizeof(TempBuffer), stdin);
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's damage the exact value ie(000.000)", NewNode->name);
	scanf("%f", &(NewNode->damage));
	
	printf("\n\nEnter %s's rare value with exact rarness ie(00.00) ", NewNode->name);
	scanf("%f", &(NewNode->rare));
	
	printf("\n\nEnter %s's possible Element (S/A/V/N/) ", NewNode->name);
	scanf(" %c", &(NewNode->element));
	NewNode->element = toupper(NewNode->element );
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
	printf("\n\nEnter %s's category ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->ammo = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->ammo, TempBuffer);

	printf("\n\nEnter %s's archetype", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';	
	NewNode->archetype = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->archetype, TempBuffer);

	printf("\n\nEnter %s's RPM (round per minute)", NewNode->name);
	scanf("%d", &(NewNode->RPM));

	printf("\n\nEnter %s's Impact ", NewNode->name);
	scanf("%d", &(NewNode->impact));

	printf("\n\nEnter %s's Magazaine size ", NewNode->name);
	scanf("%d", &(NewNode->magazaine));

	AddNode(NewNode, vault);
}

int ReadFileIntoHashTable(int argc, char *argv[], EXOTIC *vault[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	EXOTIC *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(EXOTIC));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->damage = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->rare = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->element = *token;
			
			token = strtok(NULL, "|");
			NewNode->ammo = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->ammo, token);

			token = strtok(NULL, "|");
			NewNode->archetype = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->archetype, token);

			token = strtok(NULL, "|");
			NewNode->RPM = atoi(token);
			
			token = strtok(NULL, "|");
			NewNode->impact = atoi(token);

			token = strtok(NULL, "|");
			NewNode->magazaine = atoi(token);

			AddNode(NewNode, vault);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	EXOTIC *vault[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, vault);
 
	do
	{
		printf("\n\nVault Inventory\n\n"
			   "1. Show all Exotic in vault for a given letter\n"
			   "2. Look up Exotic by name\n"
			   "3. How many Exotic are in the vault?\n"
			   "4. Display the vault\n"
			   "5. Add a new Exoitc\n"
			   "6. Delete a Exotic from the Vault\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(vault);
				break;
			case SHOWBYNAME:
				ShowByName(vault);
				break;
			case COUNT:
				printf("Your vault contains %d Exotic\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(vault);
				break;
			case ADD:
				AddNewPokemon(vault);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(vault))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(vault);

	return 0;
}			  
