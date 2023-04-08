#include<stdio.h>
#include<string.h>

#define MAX_RECORDS 10

struct PHONE_RECORD {
	char name[50];
	char birthdate[12];
	char phone[15];
} phonebook[MAX_RECORDS];

int nextIndex = 0; // assumes phonebook is empty
int isEmptyCSV = 1; // assume empty

int loadCSV(char *filename) {
	FILE *p = fopen(filename, "rt");
	char buffer[1000];
	int i,j;

	if (p == NULL) {
		isEmptyCSV = 1; // make true
		return 1; // error code
	}

	// otherwise, the file is open, read CSV
	
	fgets(buffer,999,p); // to read the CSV header (we discard it)
	isEmptyCSV = 0; // it is not empty

	nextIndex = 0;
	fgets(buffer,999,p);
	while(!feof(p)) {
		// parse the CSV record

		for(j=0,i=0;i<999&&buffer[i]!='\0'&&buffer[i]!=',';i++,j++)
			phonebook[nextIndex].name[j]=buffer[i];

		phonebook[nextIndex].name[j]='\0';
		i++;

		for(j=0;i<999&&buffer[i]!='\0'&&buffer[i]!=',';i++,j++)
			phonebook[nextIndex].birthdate[j]=buffer[i];

		phonebook[nextIndex].birthdate[j]='\0';
		i++;

		for(j=0;i<999&&buffer[i]!='\0'&&buffer[i]!='\n';i++,j++)
			phonebook[nextIndex].phone[j]=buffer[i];

		phonebook[nextIndex].phone[j]='\0';

		// Get the next record
		fgets(buffer,999,p);
		nextIndex++;
	}

	fclose(p);

	return 0;
}

int saveCSV(char *filename) {
	FILE *p = fopen(filename,"wt");
	int i;

	if (p == NULL) return 1; // error code

	if (nextIndex <= 0) return 2; // error code

	fprintf(p,"name,birthdate,phone\n");

	for(i=0; i<nextIndex; i++)
		fprintf(p,"%s,%s,%s\n", phonebook[i].name, phonebook[i].birthdate, phonebook[i].phone);

	fclose(p);

	return 0;
}

int addRecord(char name[], char birth[], char phone[]) {
	if (nextIndex >= MAX_RECORDS) return 1; //error code

	strcpy(phonebook[nextIndex].name, name);
	strcpy(phonebook[nextIndex].birthdate, birth);
	strcpy(phonebook[nextIndex].phone, phone);

	nextIndex++;
	isEmptyCSV = 0;

	return 0;
}

int findRecord(char name[]) {
	int i;

	for(i=0; i<MAX_RECORDS; i++) {
		if (strcmp(phonebook[i].name, name) == 0) return i;
	}

	return -1;
}

void printHeading() {
	 printf("---- NAME ---- ---- BIRTH DATE ---- ---- PHONE ----\n");
}

void printContent(char *name, char *bith, char *phone) {
	printf("%-14s %-20s %-10s\n", name, bith, phone);
}

int listRecords() {
	int i;

	if (nextIndex == 0 || isEmptyCSV) return 1;

	printHeading();

	for(i=0; i<nextIndex; i++)
		printContent(phonebook[i].name, phonebook[i].birthdate, phonebook[i].phone);

	return 0;	
}
