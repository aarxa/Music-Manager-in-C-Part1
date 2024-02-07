#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//a struct Duration type consisting of seconds and minutes, both integers
typedef struct duration 
{
	unsigned int seconds;
	unsigned int minutes;
}Duration;

typedef struct record  //a struct record that will be used for the artists name, album title, song title, genre, song length, number of times played etc
{
	char artist[100];
	char albumTitle[100];
	char genre[50];
	char song[50];
	Duration length;  //from the struct Distance
	unsigned int plays;
	int rating; //between 1-5
	struct record* pNext; //pointer to the next node
	struct record* pPrev; //pointer to the previous node
}Record;

typedef struct node
{
	Record data;
	struct Node* pNext;
	struct Node* pPrev;
}Node;

//Functions declarations 

//Prints the menu
void menu(void);

Node* makeNode(Record newData);
int insertFront(Node** pList, Record newData);
void printList(Node* pList);
void delay(int seconds);
void loadSongs(Node** pList, FILE* infile);
void displaySongs(Node* pList);
void searchByArtist(Node* pList);
void storeSongs(Node* pList, FILE* infile);
void editSongs(Node* pList);
void rateSong(Node* pList);
void playSong(Node* pList);

//PA3
void insert(Record* data);
int finalInsert(Node** pList, Record* newData);
void deleteRecord(Node** pList);


#endif
