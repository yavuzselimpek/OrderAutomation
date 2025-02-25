#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

typedef struct Order {
    int ID, cID, pID, piece, totalAmount;
    char date[30];

} order ;

void addOrder();
void listOrder();
void updateOrder();
void deleteOrder();

int orderMenu();
void orderProcess();
int customerControl(int );
int productControl(int,int);
void productStockUpdate(int,int);

#endif // ORDER_H_INCLUDED
