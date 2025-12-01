#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("contacts.txt","w");
    if (fptr == NULL) 
    {
        printf("\n\tError : No File Found");
        return;
    }
    fprintf(fptr,"#%d\n",addressBook->contactCount);
    for(int i = 0; i<addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("contacts.txt","r");
    if(fptr == NULL)
    {
        printf("\n\tError : No File Found");
    }
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    for(int i = 0; i<addressBook->contactCount; i++)
    {
        fscanf(fptr,"%[^,],%[^,],%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}