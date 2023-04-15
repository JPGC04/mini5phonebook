#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "mini5phone.h"

struct PHONE_NODE *head = NULL;

int loadCSV(char *filename) {
	FILE *p = fopen(filename, "rt");
	char buffer[1000];
	int i,j;
	struct PHONE_NODE *prev = NULL;
	if (p == NULL) {
		return 1; // error code
	}

	// otherwise, the file is open, read CSV
	
	fgets(buffer,999,p); // to read the CSV header (we discard it)

	// Changed while loop to reflect to linked list data structure
	
	while(fgets(buffer, 999, p)) {

		// parse the CSV record and create space for the new node

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

		// add the node to the linked list

		if (prev == NULL){
			head = anode;
		}else{
			prev->next = anode;
		}
		prev = anode;
	}

	fclose(p);

	return 0;
}

int saveCSV(char *filename) {
	FILE *p = fopen(filename,"wt");
	struct PHONE_NODE *anode = head;
	
	fprintf(p,"name,birthdate,phone\n");

	if (p == NULL) return 1; // error code

	if (anode == NULL) return 2; // error code
	
	// Saving CSV by printing their names, birthdate, and phone into the phonebook file

	while(anode){
		fprintf(p,"%s,%s,%s\n", anode->name, anode->birthdate, anode->phone);
		anode = anode->next;
	}
	fclose(p);

	return 0;
}

int addRecord(char name[], char birth[], char phone[]) {


    struct PHONE_NODE *anode = (struct PHONE_NODE*) malloc(sizeof(struct PHONE_NODE));
    if (anode == NULL) {
	    return 1;
    } //error code

    strcpy(anode->name, name);
    strcpy(anode->birthdate, birth);
    strcpy(anode->phone, phone);

    anode->next = NULL;

    struct PHONE_NODE *curr = head;
    if (head == NULL){
        head = anode;
    } else {
	struct PHONE_NODE *curr = head;
        while(curr->next){
            curr = curr->next;
	}
	curr->next = anode;
    }
    return 0;
}


struct PHONE_NODE* findRecord(char name[]) {
	struct PHONE_NODE *curr = head;

	// Traversing the linked list to compare if the names match

	while(curr != NULL) {
	       if(strcmp(curr->name, name) == 0) {
		       return curr;
	       }
	       curr = curr -> next;
	}
	return NULL; 	
}

void printHeading() {
	 printf("---- NAME ---- ---- BIRTH DATE ---- ---- PHONE ----\n");
}

void printContent(char *name, char *bith, char *phone) {
	printf("%-14s %-20s %-10s\n", name, bith, phone);
}

int listRecords() {

	if (head == NULL) return 1;

	printHeading();


	struct PHONE_NODE *curr = head;

	// Traversing the linked list starting at the head, and printing the content using the function above

	while(curr != NULL) {
		printContent(curr->name, curr->birthdate, curr->phone);
		curr = curr->next;
	}
	return 0;	
}

int delete(char name[]) {
	if (head == NULL) {
		return 1;
	}

	struct PHONE_NODE *curr = head;
	struct PHONE_NODE *nextNode = curr->next;
	
	// Checks if the head name is null, meaning that the phonebook is empty, and therefore exits out of the funcion

	if (head->name == NULL) {
		return 1;
	}

	// Checks if the head is the one that is meant to be deleted and removes and frees it

	if (strcmp(curr->name, name) == 0) {
		head = nextNode;
		free(curr);
		return 0;
	}

	// Traverses through the next node until the a name matches the input name, and removes and frees that node

	while (nextNode != NULL) {
		if (strcmp(nextNode->name, name) == 0) {
			curr->next = nextNode->next;
			free(nextNode);
			return 0;
		}

		curr = nextNode;
        	nextNode = nextNode->next;
	}

	return 1;
		
}

int clear() {
	struct PHONE_NODE *curr = head;
	struct PHONE_Node *temp;

	// Traverses through all nodes and deletes them and frees the space

	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}

	head = NULL;
}
