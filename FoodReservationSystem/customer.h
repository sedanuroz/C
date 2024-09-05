#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include "common.h"
void PlaceNewOrder(char tableId[250],int foodId,int  amount);
void UpdateQuantity(char tableId[250],int foodId,int  amount);
void CancelOrder(char tableId[250],int foodId);
void PayTheBill(char tableId[250]);
#endif // CUSTOMER_H_INCLUDED

