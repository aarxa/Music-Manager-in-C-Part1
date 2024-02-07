#include "music_manager.h"

/*************************************************************
* Function: menu()                                           *
* Date Created: 12 September 2022                            *
* Date Last Modified: 12 September                           *
* Description: Displays the menu to the user                 *
* Input parameters: None                                     *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void menu(void)
{
	printf("--------DIGITAL MUSIC MANAGER--------\n\n");
	printf("MAIN MENU:\n");
	printf("(1) Load songs\n(2) Store songs\n(3) Display the songs\n(4) Insert songs\n(5) Delete songs\n(6) Edit songs\n");
	printf("(7) Sort songs\n(8) Rate songs\n(9) Play songs\n(10) Shuffle the songs\n(11) Exit\n\n");
}

/*************************************************************
* Function: makeNode()                                       *
* Date Created: 12 September 2022                            *
* Date Last Modified: 12 September                           *
* Description: Makes a new Node using the data given         *
* Input parameters: the data to put into the node            *
* Returns: the new node                                      *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

Node* makeNode(Record newData)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode!= NULL)
	{
		strcpy(newNode->data.artist, newData.artist);
		strcpy(newNode->data.albumTitle, newData.albumTitle);
		strcpy(newNode->data.song, newData.song);
		strcpy(newNode->data.genre, newData.genre);
		newNode->data.length.minutes = newData.length.minutes;
		newNode->data.length.seconds = newData.length.seconds;
		newNode->data.plays = newData.plays;
		newNode->data.rating = newData.rating;

		newNode->pNext = NULL;
		newNode->pPrev = NULL;
	}
	return newNode;
}

/*************************************************************
* Function: insertFront()                                    *
* Date Created: 12 September 2022                            *
* Date Last Modified: 12 September                           *
* Description: inserts the node infront of the list          *
* Input parameters: None                                     *
* Returns: 1 for success, 0 for failure                      *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

int insertFront(Node** pList, Record newData)
{
	int success = 0;
	Node* newNode = makeNode(newData);

	if (newNode!= NULL)
	{
		success = 1;
		newNode->pNext = *pList;
		newNode->pPrev = NULL;

		if (*pList)
		{
			(*pList)->pPrev = newNode;
		}
		*pList = newNode;
	}
	return success; //returns 1 if success otherwise 0
}

/*************************************************************
* Function: printList()                                      *
* Date Created: 14 September 2022                            *
* Date Last Modified: 14 September                            *
* Description: Displays the menu to the user                 *
* Input parameters: None                                     *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void printList(Node* pList)
{
	while (pList!= NULL)
	{
		printf("%s,%s,%s,%s,%d:%d,%d,%d", pList->data.artist, pList->data.albumTitle, pList->data.song, pList->data.genre, pList->data.length.minutes, pList->data.length.seconds, pList->data.plays, pList->data.rating);
		printf("\n");
		pList = pList->pNext;
	}
}

/*************************************************************
* Function: loadSongs()                                      *
* Date Created: 20 September 2022                            *
* Date Last Modified: 25 September                           *
* Description: Loads songs from the file to a linked list    *
* Input parameters: file and the list                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void loadSongs(Node** pList, FILE *infile)
{
	char line[200] = " ";
	int success = 0;
	int i;

	while (fgets(line, 200, infile))
	{
		Record copy = { " ", " ", " ", " ",{0, 0}, 0, 0 };

		if (line[0] == "\"") //if the artist name is in quotes
		{
			char tempstr[100] = " ";
			strcpy(copy.artist, tempstr);
			strtok(line,",");
			strtok(NULL, ",");
		}
		else //if the artist name is not in quotations
		{
			strcpy(copy.artist, strtok(line, ","));
		}

		strcpy(copy.albumTitle, strtok(NULL, ","));
		strcpy(copy.song, strtok(NULL, ","));
		strcpy(copy.genre, strtok(NULL, ","));
		copy.length.minutes = atoi(strtok(NULL, ":"));
		copy.length.seconds = atoi(strtok(NULL, ","));
		copy.plays = atoi(strtok(NULL, ","));
		copy.rating = atoi(strtok(NULL, ","));
	}
}


/*************************************************************
* Function: displaySongs()                                   *
* Date Created: 20 September 2022                            *
* Date Last Modified: 27 September                           *
* Description: Display songs on the linekd list based on user choice   *
* Input parameters: linked list                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void displaySongs(Node* pList)
{
	char artist[100] = " ";
	int choice = 0;

	printf("You chose to display songs from the list. What would you like to do?\n");
	printf("(1) Print all records\n");
	printf("(2) Print all records that match an artist\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	system("cls");

	if (choice == 1)
	{
		putchar('\n');
		printList(pList);
		putchar('\n');
	}
	else if (choice == 2)
	{
		searchByArtist(pList);
	}
}

/*************************************************************
* Function: storeSongs()                                      *
* Date Created: 20 September 2022                            *
* Date Last Modified: 25 September                           *
* Description: store any changed made back to the file   *
* Input parameters: file and the list                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void storeSongs(Node* pList, FILE* infile)
{
	while (pList!= NULL)
	{
		fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d\n", pList->data.artist, pList->data.albumTitle, pList->data.song, pList->data.genre, pList->data.length.minutes, pList->data.length.seconds, pList->data.plays, pList->data.rating);
		pList = pList->pNext;
	}
}

/*************************************************************
* Function: rateSong()                                       *
* Date Created: 20 September 2022                            *
* Date Last Modified: 25 September                           *
* Description: rate songs on the linked list                 *
* Input parameters: linked list                              *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void rateSong(Node* pList)
{
	int rating = 0;
	char song[100] = " ";

	getchar();
	printf("You chose to rate a song from the list!\nWhich song would you like to rate?: ");
	fgets(song, 100, stdin);
	
	printf("Give the song a rating (1-5): ");
	scanf("%d", &rating);
	
	while (pList!= NULL)
	{
		if (strcmp(pList->data.song, song) == 0)
		{
			pList->data.rating = rating;
		}
		pList = pList->pNext;
	}
}

/*************************************************************
* Function: delay()                                      *
* Date Created: 25 September 2022                            *
* Date Last Modified: 25 September                           *
* Description: Holds the song playing on the screen for a certain time    *
* Input parameters: int seconds                     *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

//Code referred from www.geeksforgeeks.org
void delay(int seconds)
{
	seconds = 1000 * seconds; //converting into milli seconds
	clock_t delay = clock(); //
	while (clock() < delay + seconds);
}


/*************************************************************
* Function: playSong()                                       *
* Date Created: 24 September 2022                            *
* Date Last Modified: 27 September                           *
* Description: plays song from the records on the list       *
* Input parameters: linked list                              *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void playSong(Node* pList)
{
	char song[100] = " ";
	
	getchar();
	printf("You chose to play a song!\n");
	printf("Which song would you like to play?: ");
	fgets(song, 100, stdin);
	//strtok(song, "\n");
	system("cls");
	int n = 0;

	while (pList!= NULL)
	{
		if (strcmp(pList->data.song, song) == 0)
		{
			n++;
		}
		if (n > 0)
		{
			printf("%s,%s,%s,%s,%d:%d,%d,%d", pList->data.artist, pList->data.albumTitle, pList->data.song, pList->data.genre, pList->data.length.minutes, pList->data.length.seconds, pList->data.plays, pList->data.rating);
			delay(5);
		}
		pList = pList->pNext;
	}
}

/*************************************************************
* Function: searchByArtist()                                      *
* Date Created: 28 September 2022                            *
* Date Last Modified: 28 September                           *
* Description: searches songs as per the artist entered by the user    *
* Input parameters: linked list                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void searchByArtist(Node* pList)
{
	char artist[100] = " ";
	printf("For artists with full name, please enter last name first\n");
	printf("Enter the name of the artist whose records you want to access: ");
	//getchar();
	scanf("%s", &artist);

	while (pList != NULL)
	{
		if (strcmp(pList->data.artist, artist) == 0)
		{
			printList(pList);
		}
		pList = pList->pNext;
	}
}

/*************************************************************
* Function: editSongs()                                      *
* Date Created: 28 September 2022                            *
* Date Last Modified: 28 September                           *
* Description: edit songs from the list                      *
* Input parameters: linked list                              *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void editSongs(Node* pList)
{
	searchByArtist(pList);
	char artist[100] = " ";
	char album[100] = " ";
	char song[100] = " ";
	char genre[100] = " ";
	int minute = 0, seconds = 0, plays = 0, ratings = 0;
	char ans = "\0";
	printf("Is this the record you want to edit? (Y/N):");
	scanf("%c", &ans);

	if (ans == 'N')
	{
		printf("The artist just has one record.\n");
	}
	else
	{
		int choice = 1;
		printf("What do you want to edit?\n");
		printf("(1)Artist name\n(2)Album Title\n(3)Song\n(4)Genre\n(5)Duration\n(6)Plays\n(7)Rating");
		scanf("%d", &choice);
		
		if (choice == 1)
		{
			printf("Enter the new Artist's name: ");
			scanf("%s", &artist);
			strcpy(pList->data.artist, artist);
		}

		else if (choice == 2)
		{
			printf("Enter the new Album's name: ");
			scanf("%s", &album);
			strcpy(pList->data.albumTitle, album);
		}

		else if (choice == 3)
		{
			printf("Enter the new Song's name: ");
			scanf("%s", &song);
			strcpy(pList->data.song, song);
		}

		else if (choice == 4)
		{
			printf("Enter the new genre: ");
			scanf("%s", &genre);
			strcpy(pList->data.genre, genre);
		}

		else if (choice == 5)
		{
			printf("Enter minutes in the song: ");
			scanf("%d", &minute);
			pList->data.length.minutes = minute;
			printf("Enter seconds in the song: ");
			scanf("%d", &seconds);
			pList->data.length.seconds = seconds;
		}

		else if (choice == 6)
		{
			printf("How many times did you plays this song?");
			scanf("%d", &plays);
			pList->data.plays = plays;
		}

		else if (choice == 7)
		{
			printf("What is the new rating?");
			scanf("%d", &ratings);
			pList->data.rating = ratings;
		}
	}
	
}


/*************************************************************
* Function: insert()                                      *
* Date Created: 28 September 2022                            *
* Date Last Modified: 28 September                           *
* Description: collect each detail for the record from the user to insert into the list    *
* Input parameters: data from record                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

void insert(Record *data)
{
	
	char artist[100] = " ";
	char album[100] = " ";
	char song[100] = " ";
	char genre[100] = " ";
	int minute = 0, seconds = 0, plays = 0, ratings = 0;

	printf("Enter the name of artist: ");
	scanf("%c", &artist);
	strtok(artist, "\n");
	printf("Enter the name of album: ");
	scanf("%c", &album);
	strtok(album, "\n");
	printf("Enter the name of song: ");
	scanf("%c", &song);
	strtok(song, "\n");
	printf("Enter the name of genre: ");
	scanf("%c", &genre);
	strtok(genre, "\n");
	printf("Enter the name of length in mutues: ");
	scanf("%d", &minute);
	strtok(minute, "\n");
	printf("Enter the seconds: ");
	scanf("%d", &seconds);
	strtok(seconds, "\n");
	printf("Enter the name of plays: ");
	scanf("%d", &plays);
	strtok(plays, "\n");
	printf("Enter the name of rating: ");
	scanf("%d", &ratings);
	strtok(ratings, "\n");


	strcpy(data->artist, artist);
	strcpy(data->albumTitle, album);
	strcpy(data->song, song);
	strcpy(data->genre, genre);
	data->length.minutes = minute;
	data->length.seconds = seconds;
	data->plays = plays;
	data->rating = ratings;
	
}

/*************************************************************
* Function: FinalInsert()                                      *
* Date Created: 20 September 2022                            *
* Date Last Modified: 25 September                           *
* Description: takes the data and puts it into the insertfront function   *
* Input parameters: file and the list                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

int finalInsert(Node** pList, Record* newData)
{
	int success = 0;
	int success2 = 0;
	Record thisdata = { " "," "," "," ",{0,0},0,0 };
	strcpy(thisdata.artist, newData->artist);
	strcpy(thisdata.albumTitle, newData->albumTitle);
	strcpy(thisdata.song, newData->song);
	strcpy(thisdata.genre, newData->genre);
	thisdata.length.minutes = newData->length.minutes;
	thisdata.length.seconds = newData->length.seconds;
	thisdata.plays = newData->plays;
	thisdata.rating = newData->rating;

	success2 = insertFront(pList, thisdata);
	if (success2 == 1)
	{
		success = 1;
	}
	return success;
}

/*************************************************************
* Function: deleteRecord()                                   *
* Date Created: 20 September 2022                            *
* Date Last Modified: 25 September                           *
* Description:                                               *
* Input parameters: file and the list                        *
* Returns: None                                              *
* Preconditions: None                                        *
* Postconditions: None                                       *
*************************************************************/

int deleteRecord(Node** pList)
{
	char song[] = " ";
	int success = 0;
	printf("Which song do you want to delete?");
	fgets(song, 100, stdin);
	strtok("\n");

	Node* pCurrent = *pList;
	Node* pPrev = NULL;
	Node* pNext = NULL;
	
	while (strcmp(pCurrent->data.song, song)!= 0)
	{
		pPrev = pCurrent;
		pCurrent = pCurrent->pNext;
		pNext = pCurrent->pNext;
	}

	if (pCurrent!= NULL)
	{
		success = 1;
		pPrev->pNext = pCurrent->pNext;
		pNext->pPrev = pPrev;
		free(pCurrent);
	}
	return success;
}