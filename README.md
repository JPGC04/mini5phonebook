# mini5phonebook

This repository contains the mini5phonebook assignment for COMP 206 - Introduction to Software Systems at McGill University.

This simple phonebook program, implemented in C, manages phonebook entries using a linked list data structure. The program provides a menu-based interface for users to add, delete, find, list, and clear entries in the phonebook. The program stores the phonebook data in a CSV file.

## Usage

### Compilation

To compile the program, use the provided `makefile`. Open a terminal and run:

```bash
make
```

This will generate the executable phonebook.

### Running the Program
Execute the compiled program:
```bash
./phonebook
```

Follow the on-screen menu to perform various operations on the phonebook.

### Menu Options
1. Add Entry: Add a new entry to the phonebook.
2. Delete/Clear Entry: Delete a specific entry or clear the entire phonebook.
3. Find Entry: Search for an entry by name.
4. List Entries: Display all entries in the phonebook.
5. Quit: Exit the program.

## File Structure
1. `mini5main.c`: Contains the main program logic and user interface.
2. `mini5phone.c`: Implements phonebook operations using a linked list.
3. `mini5phone.h`: Defines structures and function prototypes used in mini5phone.c.
4. `makefile`: Defines compilation rules for the program.
