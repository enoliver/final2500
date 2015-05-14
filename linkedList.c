#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
 
/*Takes in two elements for food record and returns pointer*/
Food * createRecord(char * name, char * group, double calories, char theType)
{
    Food * listRecord;
 
    listRecord = malloc(sizeof(Food));
    listRecord->name = malloc(sizeof(char)*(strlen(name)+1));
    strcpy(listRecord->name,name);
    //listRecord->name = name;
    listRecord->foodGroup = malloc(sizeof(char)*(strlen(group)+1));
    //listRecord->foodGroup = group;
    strcpy(listRecord->foodGroup,group);
    listRecord->calories = calories;
    //printf("createRecord complete\n");
    switch (theType)
    {
        case 'h':
            listRecord->type = 'h';
            break;
        case 'j':
            listRecord->type = 'j';
            break;
        default:
            printf("You have entered an incorrect type. Please enter h for healthy or j for junk.\n");
            break;
    }
 
    return listRecord;
}
 
/*Forms string from entered element, returns pointer*/
char * printRecord(Food * toPrint)
{
    char * recordPtr;
 
    //printf("in function?\n");
    recordPtr = malloc(sizeof(char)*200);
    sprintf(recordPtr,"%s (%s):%.2f[%c]",toPrint->name, toPrint->foodGroup, toPrint->calories, toPrint->type);
    //Put string into recordPtr, it should not include nextline
    //printf("printRecord complete:%s\n", recordPtr);
    return recordPtr;
}
 
void destroyElement(Food * theElement) //Frees elements of struct but not struct intself
{
    free(theElement);
}
 
/*Adds element to head of list*/
Food * addToFront(Food * theList, Food * toBeAdded)
{
    Food * temp;
    temp = theList;
 
    toBeAdded->next = temp;
    theList = toBeAdded;
 
    return theList;
}
 
/*Adds element to end of list*/
Food * addToBack(Food * theList, Food * toBeAdded)
{
    Food * temp;
 
    temp = theList;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
 
    temp->next = toBeAdded;
    toBeAdded->next = NULL;
 
    return theList;
}
 
/*Removes the first element of the list*/
Food * removeFromFront(Food * theList)
{
    if (isEmpty(theList))
    {
        return NULL;
    }
    else
    {
        theList = theList->next;
        return theList;
    }
}
 
/*Removes the list element of the list*/
Food * removeFromBack(Food * theList)
{
    if (isEmpty(theList))
    {
        return NULL;
    }
    else
    {
        while (theList->next->next != NULL)
        {
            theList = theList->next;
        }
        theList->next = NULL;
        return theList;
    }
}
 
/*Returns pointer to last element in list*/
Food * getLastItem(Food * theList)
{
 
    if (isEmpty(theList))
    {
        return NULL;
    }
    else
    {
        while (theList->next != NULL)
        {
            theList = theList->next;
        }
        return theList;
    }
}
 
/*Checks of the list is empty*/
bool isEmpty(Food * theList)
{
    if (theList == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
 
/*Prints all elements*/
void printList(Food * theList)
{
    char * printPtr;
 
    while (theList != NULL)
    {
        printPtr = printRecord(theList);
        printf("%s\n",printPtr);
        theList = theList->next;
    }
}
 
/*Frees all elements and the list itself*/
void destroyList(Food * theList)
{
    while (theList != NULL)
    {
        destroyElement(theList);
        theList = theList->next;
    }
}