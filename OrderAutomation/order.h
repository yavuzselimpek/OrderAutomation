#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

typedef struct Order {
    int ID, cID, pID, piece, totalAmount;
    char date[20];

} order ;

void addOrder();
void listOrder();
void updateOrder();
void deleteOrder();

int orderMenu();
void orderProcess();

#endif // ORDER_H_INCLUDED
