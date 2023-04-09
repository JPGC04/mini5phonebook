#include<stdio.h>
#include<string.h>


struct PHONE_RECORD {
	char name[50];
	char birthdate[12];
	char phone[15];
	struct PHONE_NODE *next;
} 

struct PHONE_NODE *head = NULL;

int loadCSV(char *filename) {
	FILE *p = fopen(filename, "rt");
	char buffer[1000];
	int i,j;

	if (p == NULL) {
		return 1; // error code
	}

	// otherwise, the file is open, read CSV
	
	fgets(buffer,999,p); // to read the CSV header (we discard it)

	fgets(buffer,999,p);
	while(!feof(p)) {
		// parse the CSV record
		struct PHONE_NODE *anode = (struct PHONE_NODE*) malloc(sizeof(struct PHONE_NODE));
		for(j=0,i=0;i<999&&buffer[i]!='\0'&&buffer[i]!=',';i++,j++)
			anode->name[j]=buffer[i];

		anode->name[j]='\0';
		i++;

		for(j=0;i<999&&buffer[i]!='\0'&&buffer[i]!=',';i++,j++)
			anode->birthdate[j]=buffer[i];

		anode->birthdate[j]='\0';
		i++;

		for(j=0;i<999&&buffer[i]!='\0'&&buffer[i]!='\n';i++,j++)
			anode->phone[j]=buffer[i];

		anode->phone[j]='\0';
		anode->next = NULL;

		//add node to the linked list 
		if(prev == NULL) {
			head = anode;
		}else {
			prev->next = anode
		}
		prev = anode;
	}

	fclose(p);

	return 0;
}

int saveCSV(char *filename) {
	FILE *p = fopen(filename,"wt");
	struct PHONE_NODE *anode = head;

	if (p == NULL) return 1; // error code

	if (anode == NULL) return 2; // error code

	fprintf(p,"name,birthdate,phone\n");

	while(node)
		fprintf(p,"%s,%s,%s\n", anode->name, anode->birthdate, anode->phone);

	fclose(p);

	return 0;
}

int addRecord(char name[], char birth[], char phone[]) {
	struct PHONE_NODE *anode = (struct PHONE_NODE*) malloc(sizeof(struct PHONE_NODE));
	if (anode == NULL) return 1; //error code

	strcpy(anode->name, name);
	strcpy(anode->birthdate, birth);
	strcpy(anode->phone, phone);
	anode->next = NULL;

	if (head == NULL)
		head = anode;
	else
		struct PHONE_NODE *curr = head;
		while(curr->next)
			curr = curr->next;

		curr->next = anode;


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
