
#include "customer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

customer c1, c2;//global variable

void addCustomer()
{

    system("cls");
    printf("Add customer screen \n\n");

    int number=0;
    FILE *numPtr = fopen("customerNumbers.dat","a+b");
    while(fread ( &number, sizeof(int), 1, numPtr) != NULL)
    {
    }
    number++;
    fwrite( &number, sizeof(int), 1, numPtr);
    fclose(numPtr);
    c1.ID = number;
    printf("Name - Surname : ");scanf(" %[^\n]s",c1.nameSurname);
    printf("Gender         : ");scanf(" %[^\n]s",&c1.gender);
    printf("Address        : ");scanf(" %[^\n]s",c1.address);
    printf("Phone Number   : ");scanf(" %[^\n]s",c1.phoneNumber);
    printf("Email          : ");scanf(" %[^\n]s",c1.email);
    FILE *ptr = fopen("customers.dat", "a+b");
    fwrite( &c1, sizeof(customer), 1, ptr);
    fclose(ptr);
    system("cls") ;
    printf("\n\nCustomer record number %d has been completed. \n",number);
}
void listCustomer()
{
    system("cls");
    printf("List customer screen \n\n");

    int counter=0;

    printf("%-10s%-30s%-10s%-30s%-20s%-30s\n","NUMBER","NAME-SURNAME","GENDER","ADDRESS","PHONE NUMBER","e-MAIL");

    FILE *ptr = fopen("customers.dat", "r+b");//r+b read mode
    while(fread( &c1, sizeof(customer), 1, ptr) != NULL)
    {
        printf("%-10d%-30s%-10c%-30s%-20s%-30s\n",c1.ID, c1.nameSurname, c1.gender, c1.address, c1.phoneNumber, c1.email);
        counter++;
    }

    fclose(ptr);
    if(counter ==0)
    {
        system("cls");
        printf("\n No customer registration! \n");
    }
    else
    printf("\n\n%d customers are registered. \n",counter);

}
void updateCustomer()
{

}
void deleteCustomer()
{

}

int customerMenu()
{
    int choice;
    printf("\n\t CUSTOMER MANAGEMENT\n\n");
    printf("\t1- Add Customer\n");
    printf("\t2- List Customer\n");
    printf("\t3- Update Customer\n");
    printf("\t4- Delete Customer\n");
    printf("\t0- Return to Main Menu\n");
    printf("\n\tCHOICE : ");scanf("%d",&choice);
    system("cls");//clear screen
    return choice;

}
void customerManage()
{
    int choice = customerMenu();
    while(choice != 0)
    {
        switch(choice)
        {
            case 1: addCustomer();break;
            case 2: listCustomer();break;
            case 3: updateCustomer();break;
            case 4: deleteCustomer();break;
            case 0: printf("Return to Main Menu \n");break;
            default: printf("You made the wrong choice! \n");break;
        }
        choice =customerMenu();//The loop continues as long as the user presses zero.

    }




}
