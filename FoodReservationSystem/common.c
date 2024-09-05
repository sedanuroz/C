#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "common.h"
char *foodsTxt = "Foods.txt";
char *ordersTxt = "Orders.txt";
char *closedOrdersTxt = "ClosedOrders.txt";
char *takenOrdersTxt = "TakenOrders.txt";
char *logTtxt = "log.txt";
int numberOfFoods = 4;
void DisplayFoodMenu(){
    FILE *file=fopen(foodsTxt,"rb+");
    Food current;
    fread(&current,sizeof(current),1,file);
    while(!feof(file)){
        printf("Food id :%d\n",current.id);
        printf("Food name :%s\n",current.name);
        printf("Food fee :%f\n",current.fee);
        fread(&current,sizeof(current),1,file);
    }
    fclose(file);

}
void ShowOrderListOfTable(){

}

void CreatingFilePath(const char *dirName, const char *fileName, char *filePath) {
    strcpy(filePath, dirName);
    strcat(filePath, "//");
    strcat(filePath, fileName);
}
