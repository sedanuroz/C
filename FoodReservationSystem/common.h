#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <stdbool.h>
typedef struct Food{
   int id;
   char name[50];
   float fee;
}Food;

typedef struct takenOrder{
   Food f;
   int quantity;
   char tableId[250] ;
   bool isConfirmed;
   bool isActive;
}takenOrder;

void DisplayFoodMenu();
void ShowOrderListOfTable();
void CreatingFilePath(const char *dirName, const char *fileName, char *filePath);



#endif // COMMON_H_INCLUDED
