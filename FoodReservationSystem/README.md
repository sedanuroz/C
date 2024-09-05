Software Requirements
The basic operation that the restaurant expects from the software is as follows:
 Customers coming to the restaurant should be seated at a table. Here, each table has an ID.
 The restaurant owner should be able to add new tables or remove existing one in the restaurant.
 The food menu should be presented to the customer so that customer can order. The menu must include the ID, name and fee
of each food.
 The restaurant owner should be able to update the fee for an existing food later.
 When ordering, the customer must provide table ID, food ID and how many of this food customer wants.
 The order must be submitted to the business's request and, if the order is approved by the business, it must be added to the
table's order list.
 Orders must be taken from only one table at a time and must be submitted for approval.
 The customer should be able to cancel the order later if customer wishes.
 The customer should be able to change the quantity of the order if customer wishes.
 Both the customer and the restaurant owner should be able to instantly view the order list for a table.
 At the end of the food the customer must pay the total amount. For this, customer is asked for the table ID. Only foods that
have not been canceled must be paid for at checkout.
 After payment is made, the order list for the table must be deleted and the table must be made ready for new customers.
 The restaurant owner should be able to check the total payment amounts on the screen at the end of the day.


Software Design

The restaurant owner requires two separate software programs from you to perform the specified tasks: admin and customer panels. The
functionalities required on both panels are given in table 1.

![image](https://github.com/user-attachments/assets/f7b09d8f-711b-4097-be4b-68a1325d3b50)

1. A folder should be created for each table. The folder name must be the same as the table ID. The type of table ID is char array
and its length is 250. The created folder should be able to be written/read/executed only by the user who created it and the
users in the same group.
2. Orders for a table must be kept in the Orders.txt file within the folder. This file must also be created when creating the table.
3. The foods on the menu are included in the Foods.txt file. This file contains a fixed number of foods (4) and new ones cannot be
added.
4. Food information stored in the Foods.txt file is in a struct form. The UML diagram of Food Struct is as follows:

![image](https://github.com/user-attachments/assets/6e05f86d-8ee0-46b8-b0d6-bfa6e7e82233)

5. Orders placed by the customer must first be written in the TakenOrders.txt file in a struct form. The UML diagram of Struct is
as follows:

![image](https://github.com/user-attachments/assets/493c7c51-bd00-44cc-91f3-808595225457)

Attribute meanings are as follows:
 f: ordered food
 quantity: the number of foods ordered
 tableId: ID of the table that placed the order
 isConfirmed: shows whether the order is confirmed or not. It takes the false value when the first order is placed. It is set to
true after the order is confirmed by admin.
 isActive: Indicates whether the order is active or passive. It gets the true value when the customer places the first order. If
the customer cancels the order, it returns false.
6. Once the order is confirmed, the order in TakenOrders.txt should be written to the Orders.txt file of the relevant table.

7. After the customer pays, only the total amount should be written to the ClosedOrders.txt (ex: 250.99) file.
8. In order to follow up the operations within the restaurant, all steps taken should be written to the log.txt file. You can check
the logged information for each step by running the .exe files shared with you for sample log file output.


Software Implementation Details

1. Admin Panel
Create table: The new table ID is received from the user. If there is no table with the entered ID, a folder and an Orders.txt file for this
table must be created.
Delete table: The table ID is obtained from the user. If there is a table with the entered ID, the folder and Orders.txt file belonging to this
table must be deleted.
Check new order: It should be checked whether there is a new order in takeOrders.txt.
 If there is, it must be submitted to the admin whether the order is approved or not.
 If the admin approves, this order should be added to the Orders.txt file of the table that placed the order.
 Afterwards, the content of the takenOrders.txt file should be reset.
Show all invoices: All payment information in ClosedOrders.txt should be printed on the screen.
Update food: Food ID and new fee should be entered by the user. If there is a food with the entered ID, the fee of the food must be
changed in Foods.txt.
2. Customer Panel
Place a new order: Table ID of the table placing the order, food ID of the food to be ordered, and order quantity information must be
obtained from the customer.
 If there is a table with the entered table ID and a food with the entered food ID, a new takenOrder (see the takenOrder struct)
must be created.
 However, in order for an order to be received, an order that has been previously taken and has not yet been confirmed
must not be in the takenOrders.txt file. If this file is empty, a new order must be processed and written to the
takenOrders.txt file.
 A table may order the same dish more than once.
Update quantity: The table ID of the table that will update the order, the food ID of the food to be updated, and the new order quantity
information must be obtained from the customer.
 If there is a table with the entered table ID and the food with the entered food ID is included in the Orders.txt file of this table,
the quantity information for this order must be updated.
 However, in order for an order to be updated, this order must be active.
 If there are two active orders with the same food ID, the first order must be updated.
Cancel order: The table ID of the table to cancel the order and the food ID of the food to be canceled must be obtained from the
customer.
 If there is a table with the entered table ID and the food with the entered food ID is included in the Orders.txt file of this table,
this order must be deactivated.
 If there are more than one active orders with the same food ID, the first order must be cancelled.
Pay the bill: The table ID that will make the payment must be obtained from the customer.
 The total cost of active orders for this table must be calculated and written to the ClosedOrders.txt file.
 The Orders.txt file of the relevant table must be emptied.
 Even if there is no order, the total payment amount should be recorded as 0.
3. Common functions that both panels should have
Display food menu: Each food information in Foods.txt should be displayed on the screen.
Show order list of table: The table ID of the table whose order information will be shown on the screen must be obtained from the
customer. Then, the order information in Orders.txt for this table should be displayed on the screen.


