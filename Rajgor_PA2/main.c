#include "music_manager.h"

int main(void)
{
	Node* pHead = NULL;
	FILE* infile = fopen("musicPlayList.csv", "r+");
	Record* Data = (Record*)malloc(sizeof(Record));

	if (infile == NULL)
	{
		printf("Cannot open the file");
		return 1;
	}

	int success = 0;
	int choice = 0;
	char line[100] = { '\0' };
	printf("This program will perform multiple functions with a list of songs and if you don't like them, add some, edit some!\n");

	do
	{
		menu();
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: //Load the songs from the file
			printf("Loading....................\n");               
			loadSongs(&pHead, infile);
			printf("Songs loaded successfully\n");
			system("pause");
			system("cls");
			break;

		case 2: //Store the songs
			storeSongs(pHead, infile);
			printf("Songs stored successfully!\n");
			system("pause");
			system("cls");

			break;

		case 3:  //display the songs 
			displaySongs(pHead);
			system("cls");
			break;

		case 4: //insert
			insert(Data);
			finalInsert(&pHead, Data);
			break;

		case 5: //delete
			deleteRecord(&pHead);
			break;

		case 6: //edit
			editSongs(pHead);
			break;

		case 7: //sort
			break;

		case 8: //rate
			rateSong(pHead);
			system("cls");
			break;
			
		case 9: //play
			playSong(pHead);
			break;

		case 10: //shuffle
			break;

		case 11: //Exit
			storeSongs(pHead, infile);
			printf("GoodBye!\n");
			break;
		}
	} while (choice != 11);


	fclose(infile);
	return 0;
}


