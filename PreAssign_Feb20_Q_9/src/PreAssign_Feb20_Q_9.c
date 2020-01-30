/*
 ============================================================================
 Name        : PreAssign_Feb20_Q_9.c
 Author      : Shivam Palaskar
 Version     :
 Copyright   : Open source
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct Item{
	int id,quantity;
	char name[20];
	float price;
}ITEM;
ITEM newItem;

void getData();
int getOrderID();
void createItem();
void addItem();
void findItem();
void displayAll();
void editItem();
void getDataEdit(int);
void deleteItem();
void openFile();

FILE *fp,*ft;
// Note : Location of fp is very important in program

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	openFile();
	int choice;
	do {
		printf("\nChoose Operation to Perform");
		printf("\n1) Add Item");
		printf("\n2) Find Item");
		printf("\n3) Display All Items");
		printf("\n4) Edit Item");
		printf("\n5) Delete Item");
		printf("\n6) Exit");
		printf("\n Enter Option : ");
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			addItem();
			break;
		case 2:
			findItem();
			break;
		case 3:
			displayAll();
			break;
		case 4:
			editItem();
			break;
		case 5:
			deleteItem();
			break;
		}
	} while (choice != 6);
	fclose(fp);
	return EXIT_SUCCESS;
}

void deleteItem(){
	int orderID,check=0;
	printf("\n Enter OrderId to Delete Item : ");
	scanf("%d",&orderID);
	ft=fopen("TempBinaryFile.dat","wb");
	rewind(fp);
	while(fread(&newItem,sizeof(newItem),1,fp)){
		if(newItem.id!=orderID){
			fwrite(&newItem,sizeof(newItem),1,ft);
		}
		if(newItem.id==orderID)
			check=1;
	}
	fclose(fp);
	fclose(ft);
	remove("BinaryFile.dat");
	rename("TempBinaryFile.dat","BinaryFile.dat");
	if(check==1)
		printf("\nItem is deleted Successful");
	else
		printf("\nNo such Item is present");
	openFile();
}
void openFile() {
	fp = fopen("BinaryFile.dat", "rb+");
	if (fp == NULL) {
		fp = fopen("BinaryFile.dat", "wb+");
		if (fp == NULL) {
			printf("Can't Open File");
			exit(0);
		}
	}
}
void editItem() {
	int orderID;
	printf("Enter OrderID of Item to edit : ");
	scanf("%d", &orderID);
	int check = 0;
	rewind(fp);
	while (fread(&newItem, sizeof(newItem), 1, fp) == 1) {
		if (newItem.id == orderID) {
			getDataEdit(orderID);
			fseek(fp,-sizeof(newItem),SEEK_CUR);
			fwrite(&newItem,sizeof(newItem),1,fp);
			check = 1;
			break;
		}
	}
	if (check == 0)
		printf("\nNo Such Item Present");
	else
		printf("\nItem order Modified Successfully");
}

void findItem() {
	int orderID;
	printf("Enter OrderID of Desired Order : ");
	scanf("%d", &orderID);
	int check=0;
	rewind(fp);
	while (fread(&newItem, sizeof(newItem), 1, fp) == 1) {
		if(newItem.id==orderID){
			printf("\n%d %2s %.2f %6d",newItem.id,newItem.name,newItem.price,newItem.quantity);
			check=1;
		}
	}
	if(check==0)
		printf("\nNo Such Item Present");
}

void displayAll() {
	rewind(fp);
	printf("\nId Name Price Quantity");
	while (fread(&newItem, sizeof(newItem), 1, fp) == 1){ // 1 is for Number of structures to write at a time
		if(!(newItem.id==0)) // Don't know why program iterate again and again for 0 values
			printf("\n%d %2s %.2f %6d", newItem.id, newItem.name, newItem.price,
				newItem.quantity);
	}
}


void addItem() {
	createItem();
	fseek(fp,0,SEEK_END);
	fwrite(&newItem,sizeof(newItem),1,fp); // 1 is for Number of structures to write at a time
	printf("\n Item added Successfully");
}

void createItem(){
	getData();
}

 void getData(){
	printf("\n Order Id : %d", getOrderID());
	newItem.id = getOrderID();
	printf("\n Enter Name of Item : ");
	scanf("%s", newItem.name);
	printf("\n Enter Price of Item : ");
	scanf("%f", &newItem.price);
	printf("\n Enter Quantity of Item : ");
	scanf("%d", &newItem.quantity);
}

void getDataEdit(int orderID){
	printf("\n Order Id : %d", orderID);
	newItem.id = orderID;
	printf("\n Enter Name of Item : ");
	scanf("%s", newItem.name);
	printf("\n Enter Price of Item : ");
	scanf("%f", &newItem.price);
	printf("\n Enter Quantity of Item : ");
	scanf("%d", &newItem.quantity);
}

int getOrderID() {
	rewind(fp);
	while(fread(&newItem, sizeof(newItem), 1, fp) == 1);
	return (newItem.id+1); // If file is empty then ID is 0
}
