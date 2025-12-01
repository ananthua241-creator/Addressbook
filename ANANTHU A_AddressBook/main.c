/*

PROJECT TITLE   : Address Book 
NAME            : Ananthu A
DATE            : 03/11/2025
-------------------------------------------------------------------------------------------------------------------------
DESCRIPTION     : 
The Address Book Management System is a console-based C project designed to help users efficiently store, manage, and retrieve 
contact information. Focused on simplicity it allows users to create and maintain a list of contacts containing a name, phone number,
and email address. Every operation includes input validation to ensure accuracy and consistency, while all data is permanently stored 
in a text file (contacts.txt), ensuring contacts remain accessible even after the program is closed.
-------------------------------------------------------------------------------------------------------------------------
FILES AND THEIR PURPOSE:
1. main.c       – Contains the main function and menu-driven program flow.
2. contact.c    – Implements contact operations (add, edit, search, delete, list).
3. file.c       – Handles file I/O operations for saving and loading contacts.
4. populate.c   – Used for initializing or preloading contact data (optional).
5. contact.h    – Defines data structures and function prototypes for contact handling.
6. file.h       – Declares file operation functions (save/load).
7. populate.h   – Declares initialization-related functions.
8. contacts.txt – Stores contact data permanently in text format.
-------------------------------------------------------------------------------------------------------------------------
FUNCTIONS USED  :
1.	Add a Contact
    1.	Add a contact giving user name .
    2.	Add phone numbers to the newly added contact.
    3.	Add e-mail addresses to the newly added contact.
2.	List All Contacts
3.	Search a Contact
    1.	Search a contact by name.
    2.	Search contact by phone number.
    3.	Search contact by e-mail address.
4.	Edit a Contact
    1.	Edit an existing name.
    2.	Edit an existing phone number.
    3.	Edit an existing email address.
5.	Delete a contact along with all associated phone numbers and email addresses.
6.	Save & Exit the address book.

*/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n\t-------------------------------------------------------------\n");
        printf(GREEN"\t\t\t     ADDRESS BOOK MENU\n"RESET);
        printf("\t-------------------------------------------------------------\n");
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                printf("\n");
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                printf("\n");
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
