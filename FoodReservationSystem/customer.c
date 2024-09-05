#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "customer.h"
extern char *foodsTxt;
extern char *ordersTxt;
extern char *closedOrdersTxt;
extern char *takenOrdersTxt;
extern char *logTtxt;

void PlaceNewOrder(char tableId[250],int foodId,int  amount){

    bool existFood=false;
    FILE *file=fopen(foodsTxt,"rb+");
    Food food;
    fread(&food,sizeof(food),1,file);
    while(!feof(file)){
        if(food.id==foodId){
          existFood=true;
          break;
        }
        fread(&food,sizeof(food),1,file);
    }
    fclose(file);


    DIR *dir;
    if((  dir=opendir(tableId)  )==NULL){
        printf("There is no table with the given id !!!\n");

    }else{

         if(existFood){
            FILE *file=fopen(takenOrdersTxt,"rb+");
            takenOrder current;
            size_t result =fread(&current,sizeof(current),1,file);

            if(result == 0){//demekki takensOrder.txtnin i i bo
                takenOrder order;
                order.f=food;
                order.quantity=amount;
                strcpy(order.tableId,tableId);
                order.isConfirmed=false;//ilk spari  verildi inde false de erini al r
                order.isActive=true;//musteri ilk spari i verdi inde true de erini al r
                fwrite(&order,sizeof(order),1,file);
                fclose(file);
                printf("New order is added successfully....\n");


            }else{
                printf("We are so busy right now, please try ordering again soon.\n");

            }

         }else{
             printf("There is no food with the given id !!!\n");
         }


    }

    closedir(dir);

}
void UpdateQuantity(char tableId[250],int foodId,int  amount){


    DIR *dir;
    bool findFood=false;
    char filePath[250]="";
    CreatingFilePath(tableId,ordersTxt,filePath);

    FILE *file=fopen(filePath,"rb+");
    takenOrder current;

    if((  dir=opendir(tableId)  )==NULL){
        printf("There is no table with the given id !!!\n");

    }else{


          size_t result =fread(&current,sizeof(current),1,file);
          while(!feof(file) && result==1){
               if(current.f.id==foodId){
                   findFood=true;
                   break;
               }
          fread(&current,sizeof(current),1,file);
          }

          if (findFood) {
              current.quantity = amount;
              fseek(file, -sizeof(current), SEEK_CUR);
              fwrite(&current, sizeof(current), 1, file);
              printf("Amount is updated ....\n");
          } else {
             printf("Order not found!\n");
          }



    }

    fclose(file);
    closedir(dir);



}

void CancelOrder(char tableId[250],int foodId){
    DIR *dir;
    bool findFood=false;
    char filePath[250]="";
    char tempfileName[20]="tempFileName.txt";
    CreatingFilePath(tableId,ordersTxt,filePath);
    CreatingFilePath(tableId,ordersTxt,tempfileName);

    FILE *file=fopen(filePath,"rb+");
    FILE *tempFile=fopen(tempfileName,"rb");
    takenOrder current;

    if((  dir=opendir(tableId)  )==NULL){
        printf("There is no table with the given id !!!\n");

    }else{


          size_t result =fread(&current,sizeof(current),1,file);
          while(!feof(file) && result==1){
               if(current.f.id==foodId){
                   findFood=true;
                   break;
               }
          fread(&current,sizeof(current),1,file);
          }


          if (findFood) {
             size_t result =fread(&current,sizeof(current),1,file);

             while(!feof(file) && result==1){
                 fwrite(&current,sizeof(current),1,tempFile);
                 fread(&current,sizeof(current),1,file);
             }
             fwrite(&current,sizeof(current),1,tempFile);
             remove(filePath);
             fclose(file);
             rename(tempfileName,filePath);
             fclose(file);
             printf("cancel oldu");



          } else {
             printf("Order not found!\n");
          }



    }


    closedir(dir);






}

void PayTheBill(char tableId[250]){

    DIR *dir;
    FILE *file;
    FILE *f1;
    FILE *f2;
    float cost=0;
    if((  dir=opendir(tableId)  )==NULL){
        printf("There is no table with the given id !!!\n");

    }else{

        char filePath[250]="";
        CreatingFilePath(tableId,ordersTxt,filePath);

        takenOrder current;
        file=fopen(filePath,"rb+");
        size_t result =fread(&current,sizeof(current),1,file);

        while(!feof(file) && result==1){
            cost=cost+((current.f.fee)*(current.quantity));
            fread(&current,sizeof(current),1,file);
       }
       printf("TOTAL FEE :%.2f\n",cost);
       printf("Payment received successfully....\n");
       //dosya i i silme fonksiyonu




       f2=fopen(closedOrdersTxt,"w+");
       fprintf(f2,"TOTAL FEE :%.2f\n",cost);
       fclose(f2);


    }
    closedir(dir);
}



