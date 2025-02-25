#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern product p1,p2;

void addProduct()
{
    system("cls");
    printf("Add product screen \n\n");

    int number=0;
    FILE *numPtr = fopen("productNumbers.dat","a+b");
    while(fread ( &number, sizeof(int), 1, numPtr) != NULL)
    {
    }
    number++;
    fwrite( &number, sizeof(int), 1, numPtr);
    fclose(numPtr);
    p1.ID = number;
    printf("Product Name    : ");scanf(" %[^\n]s",&p1.productName);
    printf("Unit Price      : ");scanf(" %d",&p1.unitPrice);
    printf("Product Quantity: ");scanf(" %d",&p1.productQuantity);

    FILE *ptr = fopen("products.dat", "a+b");
    fwrite( &p1, sizeof(product), 1, ptr);
    fclose(ptr);
    system("cls") ;
    printf("\n\nProduct record number %d has been completed. \n",number);
}
void listProduct()
{
    system("cls");
    printf("List product screen \n\n");

    int counter=0;

    printf("%-10s%-30s%-10s%-10s\n","NUMBER"," PRODUCT NAME","UNIT PRICE","PIECE");

    FILE *ptr = fopen("products.dat", "r+b");//r+b read mode
    while(fread( &p1, sizeof(product), 1, ptr) != NULL)
    {
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
    printf("\n\n%d product types registered \n",counter);

}
void updateProduct()
{
    system("cls");
    printf("Product list \n\n");

    int counter=0,number,situation=0;

    printf("%-10s%-30s%-10s%-10s\n","NUMBER"," PRODUCT NAME","UNIT PRICE","PIECE");
    FILE *ptr = fopen("products.dat", "r+b");//r+b read mode
    while(fread( &p1, sizeof(product), 1, ptr) != NULL)
    {
        printf("%-10d%-30s%-10d%-10d\n", p1.ID, p1.productName, p1.unitPrice, p1.productQuantity);
        counter++;
    }
    if(counter ==0)
    {
        system("cls");
        printf("\n No product registration! \n");
    }
    else
    {
        counter=0;
        rewind(ptr);//We put the pointer at the beginning of the file
        printf("\nEnter the product number you want to update : ");scanf("%d",&number);
            while(fread( &p1, sizeof(product), 1, ptr) != NULL)
            {
                if(number == p1.ID)
                {
                        situation = 1;
                        break;
                }
                counter++;
            }
            if(situation == 0)
                printf("No product record found with %d number! \n",number);
            else
            {
                system("cls");
                printf("%-10s%-30s%-10s%-10s\n","NUMBER"," PRODUCT NAME","UNIT PRICE","PIECE");
                printf("\n%-10d%-30s%-10d%-10d\n", p1.ID, p1.productName, p1.unitPrice, p1.productQuantity);
                printf("Enter the data you want to update\n\n");
                printf("Product Name    : ");scanf(" %[^\n]s",&p1.productName);
                printf("Unit Price      : ");scanf(" %d",&p1.unitPrice);
                printf("Product Quantity: ");scanf(" %d",&p1.productQuantity);

                fseek(ptr , (counter) *sizeof(product), 0);
                fwrite( &p1, sizeof(product), 1, ptr);
                printf("Product %d information updated \n",number);
            }
    }
    fclose(ptr);
}
void deleteProduct()
{
    system("cls");
    printf("Product list \n\n");

    int counter=0,number,situation=0;


    printf("%-10s%-30s%-10s%-10s\n","NUMBER"," PRODUCT NAME","UNIT PRICE","PIECE");

    FILE *ptr = fopen("products.dat", "r+b");//r+b read mode
    while(fread( &p1, sizeof(product), 1, ptr) != NULL)
    {
        printf("\n%-10d%-30s%-10d%-10d\n", p1.ID, p1.productName, p1.unitPrice, p1.productQuantity);
        counter++;
    }
    if(counter ==0)
    {
        system("cls");
        printf("\n No product registration! \n");
    }
    else
    {
        counter=0;
        rewind(ptr);//We put the pointer at the beginning of the file
        printf("\nEnter the product number you want to delete : ");scanf("%d",&number);
            while(fread( &p1, sizeof(product), 1, ptr) != NULL)
            {
                if(number == p1.ID)
                {
                        situation = 1;
                        break;
                }
                counter++;
            }
            if(situation == 0)
                printf("No product record found with %d number! \n",number);
            else
            {
                system("cls");
                printf("%-10s%-30s%-10s%-10s\n","NUMBER"," PRODUCT NAME","UNIT PRICE","PIECE");
                printf("\n%-10d%-30s%-10d%-10d\n", p1.ID, p1.productName, p1.unitPrice, p1.productQuantity);
                char choice;
                printf("Are you sure you want to delete product record number %d? (Y/N): \n\n",number);scanf(" %c",&choice);
                if(choice == 'y' || choice == 'Y')
                {
                    FILE *backupPtr = fopen("backup.dat", "w+b");
                    while(fread( &p1, sizeof(product), 1, ptr) != NULL)
                    {
                        if(number != p1.ID)
                        {
                            fwrite( &p1, sizeof(product), 1, backupPtr);
                        }
                    }
                    fclose(ptr);
                    fclose(backupPtr);
                    remove("products.dat");
                    rename("backup.dat","products.dat");
                    system("cls");
                    printf("Product record number %d was deleted\n",number);


                }
                else
                    printf("\nRegistration was cancelled\n");

            }
    }
    fclose(ptr);
}

int productMenu()
{
    int choice;
    printf("\n\t PRODUCT MANAGEMENT\n\n");
    printf("\t1- Add Product\n");
    printf("\t2- List Product\n");
    printf("\t3- Update Product\n");
    printf("\t4- Delete Product\n");
    printf("\t0- Return to Main Menu\n");
    printf("\n\tCHOICE : ");scanf("%d",&choice);
    system("cls");//clear screen
    return choice;
}
void productManage()
{
    int choice = productMenu();
    while(choice != 0)
    {
        switch(choice)
        {
            case 1: addProduct();break;
            case 2: listProduct();break;
            case 3: updateProduct();break;
            case 4: deleteProduct();break;
            case 0: printf("Return to Main Menu \n");break;
            default: printf("You made the wrong choice! \n");break;
        }
        choice =productMenu();//The loop continues as long as the user presses zero.

    }
}
