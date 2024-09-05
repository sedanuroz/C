#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
int main()
{
    int selection, amount, foodId;
    char tableId[250];
    do{
        printf("Display food menu (1)\n");
        printf("Place a new order(2)\n");
        printf("Show order list of table (3)\n");
        printf("Update amount (4)\n");
        printf("Pay the bill (5)\n");
        printf("Cancel order (6)\n");
        printf("Exit (7)\n");
        printf("Enter your selection : ");
        scanf("%d",&selection);
        switch(selection){
           case 1:
               DisplayFoodMenu();
               break;
          case 2:
                printf("Enter table ID :");
                scanf("%s", tableId);
                printf("Enter food ID :");
                scanf("%d",&foodId);
                printf("Enter amount :");
                scanf("%d",&amount);
                PlaceNewOrder(tableId,foodId,amount);
                break;
            case 3:
                //ShowOrderList();
                break;
            case 4:
                 printf("Enter table ID :");
                 scanf("%s",&tableId);
                 printf("Enter food ID to update:");
                 scanf("%d",&foodId);
                 printf("Enter new amount :");
                 scanf("%d",&amount);
                 UpdateQuantity(tableId,foodId,amount);
                break;
            case 5:
                 printf("Enter table ID to pay the bill :");
                 scanf("%s",&tableId);
                 PayTheBill(tableId);
                break;
            case 6:
                 printf("Enter table ID :");
                 scanf("%s",&tableId);
                 printf("Enter food ID to cancel :");
                 scanf("%d",&foodId);
                 CancelOrder(tableId,foodId);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid selection\n");
                break;

        }
    }while(selection !=7);
    return 0;
}

