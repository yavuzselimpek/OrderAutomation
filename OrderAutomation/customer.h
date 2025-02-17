#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

typedef struct Customer {
    int ID;
    char nameSurname[30], gender, address[30], phoneNumber[20], email[30];
} customer ;

void addCustomer();
void listCustomer();
void updateCustomer();
void deleteCustomer();

int customerMenu();
void customerManage();

#endif // CUSTOMER_H_INCLUDED
