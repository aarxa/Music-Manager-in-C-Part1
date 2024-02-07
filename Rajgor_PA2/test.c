#include "test.h"

void testDeleteFunction()
{
	Node* pList = NULL;
	Record testData = { "Perry, katy", "Witness", "Chained to the rythm", "Pop", {4,36}, 3, 5 };
	int success = 0;

	char song[50] = "Chained to the rythm";
	insertFront(&pList, testData);

	if (success == 1)
	{
		printf("It worked!");
	}
	else
	{
		printf("It didnt work");
	}
}

void testInsertFunction()
{
	int success = 0;
	Node* pList = NULL;
	char artist[100] = "Perry, Katy";
	char album[100] = "Wtiness";
	char song[50] = "Chained to the rythm";
	char genre[50] = "Pop";
	int minutes = 4;
	int seconds = 3, plays = -1, ratings = 6;

	Record* thisdata = (Record*)malloc(sizeof(Record));
	strcpy(thisdata->artist, artist);
	strcpy(thisdata->albumTitle, album);
	strcpy(thisdata->song, song);
	strcpy(thisdata->genre, genre);
	thisdata->length.minutes = minutes;
	thisdata->length.seconds = seconds;
	thisdata->plays = plays;
	thisdata->rating = ratings;

	success = finalInsert(&pList, thisdata);

	if (success = 1)
	{
		printf("It worked!");
	}
	else
	{
		printf("It didnt work");
	}
}