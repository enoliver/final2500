#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
 
double calorieAvg(int counter, double groupCalorie);
 
int main(int argc, char ** argv)
{
    FILE * infile;
    Food * foodHead = NULL;
    Food * foodDiary;
    char buffer[500];
    char name[26];
    char group[9];
    double calories, meatAvg, fatAvg, vegAvg, dairyAvg, grainAvg;
    double meatCalorie, fatCalorie, vegCalorie, dairyCalorie, grainCalorie;
    char type;
    int meatCounter, fatCounter, vegCounter, dairyCounter, grainCounter;
    int calTotal=0;
    char * delim = ",\n";
    int i;
    enum values {NAME, GROUP, CALORIES, TYPE};
 
    meatCounter = 0;
    fatCounter = 0;
    vegCounter = 0;
    dairyCounter = 0;
    grainCounter = 0;
    meatCalorie = 0;
    fatCalorie = 0;
    vegCalorie = 0;
    dairyCalorie = 0;
    grainCalorie = 0;
 
    infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Cannot open %s\n", argv[1]);
        exit(0);
    }
 
    //foodHead = malloc(sizeof(Food));
 
    while (fgets(buffer,500,infile) != NULL)
    {
        char * token = strtok(buffer,delim);
 
        for (i=0;((token != NULL) && (i<4));i++)
        {
            switch (i)
            {
                case NAME:
                    strcpy(name,token);
                    break;
                case GROUP:
                    strcpy(group,token);
                    break;
                case CALORIES:
                    sscanf(token, "%lf",&calories);
                    switch (group[0])
                    {
                        case 'v':
                            vegCounter++;
                            vegCalorie = calories + vegCalorie;
                            break;
                        case 'm':
                            meatCounter++;
                            meatCalorie = calories + meatCalorie;
                            break;
                        case 'd':
                            dairyCounter++;
                            dairyCalorie = calories + dairyCalorie;
                            break;
                        case 'g':
                            grainCounter++;
                            grainCalorie = calories + grainCalorie;
                            break;
                        case 'f':
                            fatCounter++;
                            fatCalorie = calories + fatCalorie;
                            break;
                    }
                    break;
                case TYPE:
                    sscanf(token, "%c", &type);
                    break;
            }
            token = strtok(NULL, delim);
        }
        //printf("%s %s\n",name,group);
        foodDiary = createRecord(name,group,calories,type);
        calTotal = calories + calTotal;
        switch (type)
        {
            case 'h':
                foodHead = addToFront(foodHead, foodDiary);
                break;
            case 'j':
                foodHead = addToBack(foodHead, foodDiary);
                break;
            default:
                printf("error\n");
                break;
        }
    }
 
    vegAvg = calorieAvg(vegCounter, vegCalorie);
    meatAvg = calorieAvg(meatCounter, meatCalorie);
    dairyAvg = calorieAvg(dairyCounter, dairyCalorie);
    grainAvg = calorieAvg(grainCounter, grainCalorie);
    fatAvg = calorieAvg(fatCounter, fatCalorie);
    printf("%d\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n",calTotal,vegAvg, meatAvg, dairyAvg, grainAvg, fatAvg);
    printList(foodHead);
    destroyList(foodHead);
 
    return 0;
}
 
double calorieAvg(int counter, double groupCalorie)
{
    double avg=0;
 
    if (counter != 0)
    {
        avg = (groupCalorie / counter);
    }
    return avg;
}