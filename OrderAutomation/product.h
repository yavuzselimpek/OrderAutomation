#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

typedef struct Product {
    int ID;
    char productName[20];
    int unitPrice, productQuantity;
} product ;

void addProduct();
void listProduct();
void updateProduct();
void deleteProduct();

int productMenu();
void productManage();




#endif // PRODUCT_H_INCLUDED
