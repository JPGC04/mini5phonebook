#include<stdio.h>
#include "mini5phone.c"


int menu() {
	int selection;
	char garbage[5];

	printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit > ");
	scanf("%d", &selection);
	fgets(garbage,4,stdin);

	return selection;
}

int main() {
	struct PHONE_NODE *head = NULL;
	int choice, record;
	char name[50], birth[50], phone[50];

	loadCSV("phonebook.csv");

	do {
		choice = menu();

		switch(choice) {
			case 1:
				printf("Name: ");  fgets(name,49,stdin);  name[strlen(name)-1]   = '\0';
				printf("Birth: "); fgets(birth,12,stdin); birth[strlen(birth)-1] = '\0';
				printf("Phone: "); fgets(phone,14,stdin); phone[strlen(phone)-1] = '\0';

				record = addRecord(name, birth, phone);
				if (record != 0) printf("CSV if out of space\n");

				break;

			case 2:
				printf("Find name: "); fgets(name,49,stdin); name[strlen(name)-1] = '\0';
				
				record = findRecord(name);

				if (record == NULL) printf("Does not exist\n");
				else {
					printHeading();
					printContent(record->name, record->birthdate, record->phone);
				}
				break;

			case 3:
				record = listRecords();

				if (record != 0) printf("Phonebook.csv does not exist\n");
				break;

			case 4:
				break;

			default:
				printf("Invalid menu selection\n");
		}
	} while(choice != 4);

	saveCSV("phonebook.csv");

	printf("End of phonebook program\n");

	return 0;
}
