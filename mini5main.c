#include<stdio.h>
#include<string.h>
#include "mini5phone.h"

int menu() {
	// Prints the menu and returns the selected menu option
	
	int selection;
	char garbage[5];

	printf("Phonebook Menu: (1)Add, (2)Delete/Clear, (3)Find, (4)List (5)Quit > ");
	scanf("%d", &selection);
	fgets(garbage,5,stdin);

	return selection;
}

int main() {
	// declares variables to hold exit codes, data, and selections
	// loads CSV file
	
	int choice;
	int exitCode;
	struct PHONE_NODE *record;
	char name[50], birth[50], phone[50];

	loadCSV("phonebook.csv");

	do {
		choice = menu();

		switch(choice) {
			case 1:
				// Option to add entry to CSV file

				printf("Name: ");  fgets(name,49,stdin);  name[strlen(name)-1]   = '\0';
				printf("Birth: "); fgets(birth,12,stdin); birth[strlen(birth)-1] = '\0';
				printf("Phone: "); fgets(phone,14,stdin); phone[strlen(phone)-1] = '\0';

				exitCode = addRecord(name, birth, phone);
				if (exitCode != 0) printf("CSV if out of space\n");

				break;

			case 2:
				// Option to remove entry or clear CSV file

				char select2;
				int choice2;
				char garbage[5];

				printf("(D)elete or (C)lear > "); scanf("%c", &select2); fgets(garbage,5,stdin);
				
				if (select2 == 'D') {
					choice2 = 1;
				} else if (select2 == 'C') {
					choice2 = 2;
				} else {
					choice2 = 3;
				}

				switch(choice2) {
					case 1:
						// Opttion to delete an entry from CSV file

						printf("Name to delete: "); fgets(name, 49, stdin); name[strlen(name)-1] = '\0';
						exitCode = delete(name);
						if (exitCode != 0) printf("Sorry not found\n");
						
						break;

					case 2:
						// Option to clear CSV file

						char select3[2];

						printf("Are you sure (Y/N) > "); scanf("%1s", select3); fgets(garbage, 5, stdin);

						if (strcmp(select3, "Y") == 0) {
							clear();
							break;
						} else if(strcmp(select3, "N") == 0) {
							break;
						}

						break;

					default:
						// Option to handle invalid selections

						printf("Invalid menu selection\n");
						
						break;

				}

				break;

			case 3:
				// Option to find name in CSV file

				printf("Find name: "); fgets(name,49,stdin); name[strlen(name)-1] = '\0';

                                record = findRecord(name);

                                if (record == NULL) {
					printf("Does not exist\n");
				} else {
                                        printHeading();
                                        printContent(record->name, record->birthdate, record->phone);
                                }

                                break;

			case 4:
				// Option to list entires of CSV file

				exitCode = listRecords();

                                if (exitCode != 0) printf("Phonebook.csv does not exist\n");
                                
				break;

			case 5:
				// Break out of loop if 5 is selected
				
				break;

			default:
				// Default to handle invalid options

				printf("Invalid menu selection\n");
		}

	} while(choice != 5);

	saveCSV("phonebook.csv");

	printf("End of phonebook program\n");

	return 0;
}
