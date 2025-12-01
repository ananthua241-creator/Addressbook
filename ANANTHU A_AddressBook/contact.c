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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//Name validation
int validateName(char name[],AddressBook *addressBook)
{
    int i=0;   
    if(!isalpha(name[0]))//ALPHABET
        return 0;
    while(name[i])
    {
    if(isalpha(name[i]) || name[i] == ' ')
        i++;
    else
        return 0;
    }
    return 1;
}

//Number validation
int validatePhone(char phone[], AddressBook *addressBook)
{
    // length = 10
    if(strlen(phone) != 10)
        return 0;
    // only digits
    for(int i=0; phone[i]!= '\0'; i++)
    {
        if(!isdigit(phone[i]))
            return 0;
    }
    
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 2; // not unique
    }
    return 1;
}

//Email validation
int validateEmail(char email[], AddressBook *addressBook)
{
    int at_count=0,dot_count=0;
    int at=-1,dot=-1;
    int len = strlen(email);
    for(int i=0; email[i]!= '\0'; i++)
    {
        if(email[i] == '@')
        {
            at=i;
            at_count++;
        }
        if(email[i] == '.')
        {
            dot=i;
            dot_count++;
        }
        if(email[i] == ' ')//no space
            return 0;
        if(!islower(email[i]) && email[i] != '@' && email[i] != '.' && !isdigit(email[i]))
            return 0;
    }
 
    if(at<1 || at>dot || at_count!=1 || dot_count!=1)//cannot start with @,dot must come after @,count=1
        return 0;
    if(strcmp(email + len - 4, ".com") != 0) //last .com
        return 0;
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
            return 2; // not unique
    }
    return 1;
}

//Serach by name
int searchname(AddressBook *addressBook, char search[])
{
    int serial = 0;
    int index[100];
    for(int i=0; i < addressBook->contactCount; i++)
    {
        if(strcasestr(addressBook->contacts[i].name,search) != NULL)
        {
            printf("\n%d. %s\t%s\t%s\n", serial+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
            index[serial] = i; 
            serial++;
        }
    }

    if(serial == 0)
    {
        printf(RED"\n\t⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕ No Match found ⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕\n"RESET);
        return -1;
    }
    int choose;
    printf("\nENTER THE SERIAL NUMBER TO CONFIRM : ");
    scanf("%d",&choose);
    if (choose < 1 || choose > serial) 
    {
        printf(RED"\n\tInvalid selection! Returning to menu.\n"RESET);
        return -1;
    }
    choose--;
    int choose_index = index[choose];
    printf("\n%-10s\t\t %-9s\t\t %-2s\n","Name","Mobile Number","Email Id");
    printf("--------------------------------------------------------------------------\n");
    printf("%-10s\t\t %-10s\t\t %-10s\n",
           addressBook->contacts[choose_index].name,
           addressBook->contacts[choose_index].phone,
           addressBook->contacts[choose_index].email);
    return choose_index;
}

//Serach by number
int searchnumber(AddressBook *addressBook, char search[])
{
    int serial = 0;
    int index[100];
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strstr(addressBook->contacts[i].phone, search) != NULL) 
        {
            printf("\n%d. %s\t%s\t%s\n", serial+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
            index[serial] = i; 
            serial++;
        }
    }
    if(serial == 0)
    {
        printf(RED"\n\t⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕ No Match found ⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕\n"RESET);
        return -1;
    }
    int choose;
    printf("\nENTER THE SERIAL NUMBER TO CONFIRM : ");
    scanf("%d",&choose);
    if (choose < 1 || choose > serial) 
    {
        printf(RED"\n\tInvalid selection! Returning to menu.\n"RESET);
        return -1;
    }
    choose--;
    int choose_index = index[choose];
    printf("\n%-10s\t\t %-9s\t\t %-2s\n","Name","Mobile Number","Email Id");
    printf("--------------------------------------------------------------------------\n");
    printf("%-10s\t\t %-10s\t\t %-10s\n",
           addressBook->contacts[choose_index].name,
           addressBook->contacts[choose_index].phone,
           addressBook->contacts[choose_index].email);
    return choose_index;
}

//Serach by email
int searchemail(AddressBook *addressBook, char search[])
{
    int serial=0;
    int index[100];
    for(int i = 0; i<addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email,search)!=NULL)
            {
            printf("\n%d. %s\t%s\t%s\n", serial+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
            index[serial] = i; 
            serial++;
            }
        }  
    if(serial == 0)
    {
        printf(RED"\n\t⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕ No Match found ⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕⁕\n"RESET);
        return -1;
    }

    int choose;
    printf("\nENTER THE SERIAL NUMBER TO CONFIRM : ");
    scanf("%d",&choose);
    if (choose < 1 || choose > serial) 
    {
        printf(RED"\n\tInvalid selection! Returning to menu.\n"RESET);
        return -1;
    }
    choose--;
    int choose_index = index[choose];
    printf("\n%-10s\t\t %-9s\t\t %-2s\n","Name","Mobile Number","Email Id");
    printf("--------------------------------------------------------------------------\n");
    printf("%-10s\t\t %-10s\t\t %-10s\n",
           addressBook->contacts[choose_index].name,
           addressBook->contacts[choose_index].phone,
           addressBook->contacts[choose_index].email);
    return choose_index;
}

// List contacts based on the chosen criteria
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    int count=0;
    // Sort contacts based on the chosen criteria
    if(sortCriteria == 1)
    {
        for(int i = 0; i<(addressBook->contactCount)-1; i++)
        {
            for(int j = 0; j<(addressBook->contactCount)-i-1; j++)
            {
                if((strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0))
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
       printf("  %-10s\t%-10s\t\t %-8s\t\t %-2s\n","sl.no","Name","Mobile Number","Mail Id");
       printf("-----------------------------------------------------------------------------------------------\n");
       for(int i = 0; i<(addressBook->contactCount); i++)
       {
        count++;
        printf("  %d.\t",count);
        printf("\t%-10s\t\t",addressBook->contacts[i].name );
        printf(" %-10s\t\t",addressBook->contacts[i].phone);
        printf(" %-10s\n",addressBook->contacts[i].email);
        printf("-----------------------------------------------------------------------------------------------\n");
       }
    }
    else if(sortCriteria == 2)
    {
        for(int i = 0; i<(addressBook->contactCount)-1; i++)
        {
            for(int j = 0; j<(addressBook->contactCount)-i-1; j++)
            {
                if((strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0))
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("  %-10s\t%-10s\t\t %-8s\t\t %-2s\n","sl.no","Name","Mobile Number","Mail Id");
        printf("-----------------------------------------------------------------------------------------------\n");
        for(int i = 0; i<(addressBook->contactCount); i++)
        {
            count++;
            printf("  %d.\t",count);
            printf("\t%-10s\t\t",addressBook->contacts[i].name );
            printf(" %-10s\t\t",addressBook->contacts[i].phone);
            printf(" %-10s\n",addressBook->contacts[i].email);
            printf("-----------------------------------------------------------------------------------------------\n");
        }
    }
    else if(sortCriteria == 3)
    {
        for(int i = 0; i<(addressBook->contactCount)-1; i++)
        {
            for(int j = 0; j<(addressBook->contactCount)-i-1; j++)
            {
                if((strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0))
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("  %-10s\t%-10s\t\t %-8s\t\t %-2s\n","sl.no","Name","Mobile Number","Mail Id");
        printf("-----------------------------------------------------------------------------------------------\n");
        for(int i = 0; i<(addressBook->contactCount); i++)
        {
            count++;
            printf("  %d.\t",count);
            printf("\t%-10s\t\t",addressBook->contacts[i].name );
            printf(" %-10s\t\t",addressBook->contacts[i].phone);
            printf(" %-10s\n",addressBook->contacts[i].email);
            printf("-----------------------------------------------------------------------------------------------\n");
        }
    }
    else
    printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Invalid Choice ⨳⨳⨳⨳⨳⨳\n"RESET);  
}

// Initialize address book
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Save contacts and exit program
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Create new contact
void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[20];
    char email[50];

    int result;
    do {
    printf("\nENTER THE NAME:");
    scanf(" %[^\n]",name);
    result=validateName(name, addressBook);
    if(result == 0)
    printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Entered Name is Invalid ⨳⨳⨳⨳⨳⨳\n"RESET);
    } while(result == 0);

    do {
    printf("\nENTER THE NUMBER:");
    scanf(" %[^\n]",phone);
    result=validatePhone(phone, addressBook);
    if(result == 0)
    printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Entered Number is Invalid ⨳⨳⨳⨳⨳⨳\n"RESET);
    if(result==2)
    printf(RED"\n\t<········· Number Already Exist ·········>\n"RESET);
    } while(result == 0 || result == 2);

    do {
    printf("\nENTER THE EMAIL:");
    scanf(" %[^\n]",email);
    result=validateEmail(email, addressBook);
    if(result == 0)
    printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Entered Email is Invalid ⨳⨳⨳⨳⨳⨳\n"RESET);
    if(result==2)
    printf(RED"\n\t<········· Email Already Exist ·········>\n"RESET);
    } while(result == 0 || result == 2);


    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    (addressBook->contactCount)++;
    printf(GREEN"\n\t⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝ Contact is Added Successfully ⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝\n"RESET);
}

// Search for a contact
int searchContact(AddressBook *addressBook) 
{
    printf("Select search criteria:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("\nEnter your choice: ");
    int searchChoice;
    scanf("%d",&searchChoice);
    char search[100];
        
    if(searchChoice == 1)
    {
        printf("ENTER THE NAME:");
        scanf(" %[^\n]",search);
        return searchname(addressBook, search);
    }

    else if(searchChoice == 2)
    {
        printf("ENTER THE NUMBER:");
        scanf(" %[^\n]",search);
        return searchnumber(addressBook, search);
    }

    else if(searchChoice == 3)
    {
        printf("ENTER THE EMAIL:");
        scanf(" %[^\n]",search);
        return searchemail(addressBook, search);
    }

    else
    {
        printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : INVALID CHOICE ⨳⨳⨳⨳⨳⨳\n"RESET);
        return -1;
    }
}

// Edit existing contact
void editContact(AddressBook *addressBook)
{
    int index = searchContact(addressBook);
    if(index < 0) 
    return;
    int choice,valid;

    // Get correct choice
    while(1)
    {
        printf("\nSelect field to edit:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice >=1 && choice <=3)
        break;
        printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Invalid Option! Try again ⨳⨳⨳⨳⨳⨳\n"RESET);
    }

    // Edit name
    if(choice == 1)
    {
        char newName[100];
        while(1)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]",newName);
            valid=validateName(newName, addressBook);
            if(valid == 1)
            {
                strcpy(addressBook->contacts[index].name, newName);
                break; 
            }
            else
            printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Invalid Name! Try again ⨳⨳⨳⨳⨳⨳\n"RESET);
        }
    }

    // Edit phone
    else if(choice == 2)
    {
        char newPhone[100];
        while(1)
        {
            printf("\nEnter new phone: ");
            scanf(" %[^\n]",newPhone);

            valid=validatePhone(newPhone, addressBook);
            if(valid==1)
            {
            strcpy(addressBook->contacts[index].phone, newPhone);
            break;
            }
            else if(valid==2)
            printf(RED"\n\t<········· Number Already Exist ·········>\n"RESET);
            else
            printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Invalid Number! Try again ⨳⨳⨳⨳⨳⨳\n"RESET);
        }
    }

    // Edit email
    else if(choice == 3)
    {
        char newEmail[100];
        while(1)
        {
            printf("\nEnter new email: ");
            scanf(" %[^\n]",newEmail);
            valid=validateEmail(newEmail, addressBook);
            if(valid==1)
            {
            strcpy(addressBook->contacts[index].email, newEmail);
            break;
            }
            else if(valid==2)
            printf(RED"\n\t<········· Email Already Exist ·········>\n"RESET);
            else
            printf(RED"\n\t⨳⨳⨳⨳⨳⨳ Error : Invalid Email! Try again ⨳⨳⨳⨳⨳⨳\n"RESET);
        }
    }
    printf("\n%-10s\t\t %-9s\t\t %-2s\n","Name","Mobile Number","Email Id");
    printf("--------------------------------------------------------------------------\n");
    printf("%-10s\t\t",addressBook->contacts[index].name );
    printf(" %-10s\t\t",addressBook->contacts[index].phone);
    printf(" %-10s\n",addressBook->contacts[index].email);
    printf(GREEN"\n\t⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝ Contact Updated Successfully ⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝\n"RESET);       
}

// Delete contact
void deleteContact(AddressBook *addressBook)
{
    int delete=searchContact(addressBook);
    if(delete<0)
    {
        return;
    }
    for(int i = delete; i<(addressBook->contactCount)-1; i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf(GREEN"\n\t⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝ Contact Deleted Successfully ⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝\n"RESET);
}
