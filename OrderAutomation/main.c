#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
#include "product.h"
#include "order.h"

int menu()
{
    int choice;
    printf("\n\t ORDER MANAGEMENT\n\n");
    printf("\t1- CUSTOMER MANAGEMENT\n\n");
    printf("\t2- PRODUCT MANAGEMENTS\n\n");
    printf("\t3- ORDER PROCESSING\n\n");
    printf("\t0- CLOSE PROGRAM\n\n");
    printf("\tCHOICE : ");scanf("%d",&choice);
    system("cls");//clear screen
    return choice;

}

int main(int argc, char *argv[])
{
    int choice = menu();
    while(choice != 0)
    {
        switch(choice)
        {
            case 1: customerManage();break;
            case 2: productManage();break;
            case 3: orderProcess();break;
            case 0: break;
            default: printf("You made the wrong choice! \n");break;
        }
        choice =menu();//The loop continues as long as the user presses zero.

    }



    return 0;
}
