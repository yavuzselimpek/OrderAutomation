#include "order.h"
#include "product.h"
#include "customer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

order o1,o2;
product p1;
customer c1;
void productStockUpdate(int id, int count)
{
    int counter = 0;

    FILE *ptr = fopen("products.dat", "r+b");//r+b read mode
    while(fread( &p1, sizeof(product), 1, ptr) != NULL)
    {
        if(id == o1.ID)
        {
            break;
        }
        counter++;
    }
    p1.productQuantity += count;
    fseek(ptr , (counter) *sizeof(product), 0);
    fwrite( &p1, sizeof(product), 1, ptr);

    fclose(ptr);
}
int customerControl(int number)
{
    int situation = 0;
    FILE *ptr = fopen("customers.dat", "r+b");
    while(fread( &c1, sizeof(customer), 1, ptr) != NULL)
    {
        if(number == c1.ID)
        {
                situation = 1;
                break;
        }
    }
    fclose(ptr);
    return situation;


}
int productControl(int number, int count)
{
    int situation = 0;
    FILE *ptr = fopen("products.dat", "r+b");
    while(fread( &p1, sizeof(product), 1, ptr) != NULL)
    {
        if(number == p1.ID)
        {
                situation = 1;
                if(p1.productQuantity < count)
                    situation = -1;
                break;
        }
    }
    fclose(ptr);
    if(situation == 1)
        return p1.unitPrice;
    else
        return situation;

}


void createOrder()
{
    system("cls");
    printf("Create order screen \n\n");

    int number=0;
    FILE *numPtr = fopen("orderNumbers.dat","a+b");
    while(fread ( &number, sizeof(int), 1, numPtr) != NULL)
    {
    }
    number++;
    fwrite( &number, sizeof(int), 1, numPtr);
    fclose(numPtr);
    o1.ID = number;

    system("cls");
    printf("Costomer list  \n\n");

    int counter=0;

    printf("\n%-10s%-30s%-10s%-30s%-20s%-30s\n","NUMBER","NAME-SURNAME","GENDER","ADDRESS","PHONE NUMBER","e-MAIL");

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
    {
        printf("Customer number  : ");scanf(" %d", &o1.cID);
        system("cls");
        printf("Product list \n\n");
        counter=0;

        printf("\n%-10s%-30s%-10s%-10s\n","NUMBER"," PRODUCT NAME","UNIT PRICE","PIECE");

        ptr = fopen("products.dat", "r+b");//r+b read mode
        while(fread( &p1, sizeof(product), 1, ptr) != NULL)
        {
            if(!p1.productQuantity <=0)
            printf("%-10d%-30s%-10d%-10d\n", p1.ID, p1.productName, p1.unitPrice, p1.productQuantity);
            counter++;
        }

        fclose(ptr);
        if(counter ==0)
        {
            system("cls");
            printf("\n No product registration! \n");
        }
        else
        {
            printf("Product number  : ");scanf(" %d", &o1.pID);
            printf("Piece           : ");scanf(" %d", &o1.piece);

            int cResult = customerControl(o1.cID);
            int pResult = productControl(o1.pID,o1.piece);

            if(cResult == 0)
                printf("\nCustomer record number %d not found, review the data again! \n",o1.cID);
            else if(pResult == 0)
                printf("\nProduct record number %d not found, review the data again! \n",o1.pID);
            else if(pResult == -1)
                printf("\nNot enough product number %d ! \n",o1.pID);
            else if(o1.piece <=0)
                printf("\nYou have entered the wrong quantity. Please enter again ! \n");

            else
            {
                fclose(ptr);
                o1.totalAmount = pResult *o1.piece;
                time_t date = time(NULL);
                strcpy(o1.date, ctime(&date));
                ptr = fopen("orders.dat","a+b");
                fwrite( &o1, sizeof(order), 1, ptr) ;
                fclose(ptr);
                system("cls");

                printf("Order record number %d has been created",o1.ID);

                productStockUpdate(o1.pID, -o1.piece);

            }






        }

    }


}
void listOrder()
{
    system("cls");
    printf("List order screen \n\n");

    int counter=0;

    printf("%-10s%-15s%-15s%-10s%-20s%-30s\n","NUMBER","Customer ID","Product ID","PIECE","Amount( TL )","Date");

    FILE *ptr = fopen("orders.dat", "r+b");//r+b read mode
    while(fread( &o1, sizeof(order), 1, ptr) != NULL)
    {
        printf("%-10d%-15d%-15d%-10d%-20d%-30s\n",o1.ID, o1.cID, o1.pID, o1.piece, o1.totalAmount, o1.date);
        counter++;
    }

    fclose(ptr);
    if(counter ==0)
    {
        system("cls");
        printf("\n No order registration! \n");
    }
    else
    printf("\n\n%d order registered \n",counter);

}

void deleteOrder()
{
    system("cls");
    printf("Order list \n\n");

    int counter=0,number,situation=0;


    printf("%-10s%-15s%-15s%-10s%-20s%-30s\n","NUMBER","Customer ID","Product ID","PIECE","Amount( TL )","Date");


    FILE *ptr = fopen("orders.dat", "r+b");//r+b read mode
    while(fread( &o1, sizeof(order), 1, ptr) != NULL)
    {
        printf("%-10d%-15d%-15d%-10d%-20d%-30s\n",o1.ID, o1.cID, o1.pID, o1.piece, o1.totalAmount, o1.date);
        counter++;
    }
    if(counter ==0)
    {
        system("cls");
        printf("\n No order registration! \n");
    }
    else
    {
        counter=0;
        rewind(ptr);//We put the pointer at the beginning of the file
        printf("\nEnter the order number you want to delete : ");scanf("%d",&number);
            while(fread( &o1, sizeof(order), 1, ptr) != NULL)
            {
                if(number == o1.ID)
                {
                        situation = 1;
                        break;
                }
                counter++;
            }
            if(situation == 0)
                printf("No order record found with %d number! \n",number);
            else
            {
                system("cls");
                printf("%-10s%-15s%-15s%-10s%-20s%-30s\n","NUMBER","Customer ID","Product ID","PIECE","Amount( TL )","Date");
                printf("%-10d%-15d%-15d%-10d%-20d%-30s\n",o1.ID, o1.cID, o1.pID, o1.piece, o1.totalAmount, o1.date);
                char choice;
                printf("Are you sure you want to delete order record number %d? (Y/N): \n\n",number);scanf(" %c",&choice);
                if(choice == 'y' || choice == 'Y')
                {
                    FILE *backupPtr = fopen("backup.dat", "w+b");
                    while(fread( &o1, sizeof(order), 1, ptr) != NULL)
                    {
                        if(number != o1.ID)
                        {
                            fwrite( &o1, sizeof(order), 1, backupPtr);
                        }
                    }
                    fclose(ptr);
                    fclose(backupPtr);
                    remove("orders.dat");
                    rename("backup.dat","orders.dat");
                    system("cls");
                    printf("Order record number %d was deleted\n",number);

                    productStockUpdate(o1.pID, o1.piece);


                }
                else
                    printf("\nRegistration was cancelled\n");

            }
    }
    fclose(ptr);
}

int orderMenu()
{
    int choice;
    printf("\n\t ORDER MANAGEMENT\n\n");
    printf("\t1- Add Order\n");
    printf("\t2- List Order\n");
    printf("\t3- Delete Order\n");
    printf("\t0- Return to Main Menu\n");
    printf("\n\tCHOICE : ");scanf("%d",&choice);
    system("cls");//clear screen
    return choice;
}
void orderProcess()
{
    int choice = orderMenu();
    while(choice != 0)
    {
        switch(choice)
        {
            case 1: createOrder();break;
            case 2: listOrder();break;
            case 3: deleteOrder();break;
            case 0: printf("Return to Main Menu \n");break;
            default: printf("You made the wrong choice! \n");break;
        }
        choice =orderMenu();//The loop continues as long as the user presses zero.

    }

}

