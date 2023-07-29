#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
/* Date created: 28/11/19
   Written by: Nadia Bhola
   Subject: Computer Science
   Unit 2 IA
   Description: This program stores a catering company's customer list,
		product list, and transactions made.
		It allows information for customer, item and transaction
		information to be added, viewed, searched, edited and
		deleted.
*/

typedef struct customer //record that holds customer's releveant fields
{
  int cid;
  char fname[10];
  char lname[10];
  char phone[8];
} Customer;

typedef struct cnode    //customer's node
{
	Customer cst;
	struct cnode * next;
}CNode, *CNodePtr;

typedef struct item     //record that holds an item's relevant fields
{
  int iid;
  char iname[15];
  char description[30];
  float cost;
} Item;

typedef struct inode    //item's node
{
	Item itm;            //data part of node
	struct inode * next; //pointer part of node
}INode, *INodePtr;

typedef struct purchase //link-entity that links items and customers
{
  int pid;
  int billno;
  int cid;
  int iid;
  int qty;
  char date[8];
  float total;
} Purchase;

typedef struct pnode    //the node for each purchase
{
	Purchase pchs;       //data part of node
	struct pnode * next; //pointer part of node
}PNode, *PNodePtr;

void main()
{
  /*
     MAIN MENU
     Allows the user to: enter the purchase menu
			 enter the customer menu
			 enter the item menu
			 exit the program
  */
  void purchasemenu();   //call function prototypes
  void customermenu();
  void itemmenu();
  clrscr();
  printf ("Welcome to Main Menu\n");
  printf ("Purchases....................1\n");
  printf ("Customers....................2\n");
  printf ("Items........................3\n");
  printf ("EXIT.........................0\n\n");
  int ch;
  printf ("Enter the number corresponding to the menu you wish to access:");
  scanf ("%d", &ch);
  while(ch!=0) //while the user has not chosen to exit
  {
    if (ch==1)
      purchasemenu();//purchases menu
    else if (ch==2)
      customermenu();//customer menu
    else if (ch==3)
      itemmenu();    //item menu
    else             //for invalid choice
    {
      printf("Invalid choice entered");
      getch();
    }
    //Allow user to select new choice
    clrscr();
    printf ("Main Menu\n");
    printf ("Purchases....................1\n");
    printf ("Customers....................2\n");
    printf ("Items........................3\n");
    printf ("EXIT.........................0\n\n");
    printf ("Enter the number corresponding to the menu you wish to access:");
    scanf ("%d", &ch);
  } //end while (ch!=0)
} //end main

void customermenu() //customer menu
{
 /*
    Customer Menu
    Allows the user to: enter the add customer function
			enter the edit customer function
			enter the search customer function
			enter the view customer function
			enter the delete customer function
			return to the main menu
 */
 void addcustomer(); //function prototypes
 void editcustomer();
 void searchcustomer();
 void viewcustomer();
 void deletecustomer();
 clrscr();
 printf("Welcome to Customer menu\n");
 printf("Add....................1\n");
 printf("Edit...................2\n");
 printf("Search.................3\n");
 printf("View...................4\n");
 printf("Delete.................5\n");
 printf("RETURN to main menu....0\n\n");
 int Cch;
 printf("Enter the number corresponding to your choice:");
 scanf("%d", &Cch);
 while(Cch!=0)  //while the user has not chosen to exit
 {
   if (Cch==1)
     addcustomer();   //open add customer function
   else if (Cch==2)
     editcustomer();  //open edit customer function
   else if (Cch==3)
     searchcustomer();//open search customerfunction
   else if (Cch==4)
     viewcustomer();  //open view customer function
   else if (Cch==5)
     deletecustomer();
   else // for invalid choice
   {
     printf("Invalid choice entered");
     getch();
   }
 // Allow user to select new choice
 clrscr();
 printf("Welcome to Customer menu\n");
 printf("Add....................1\n");
 printf("Edit...................2\n");
 printf("Search.................3\n");
 printf("View...................4\n");
 printf("Delete.................5\n");
 printf("RETURN to main menu....0\n\n");
 printf("Enter the number corresponding to your choice:");
 scanf("%d", &Cch);
 }//end while(Cch!=0)
}//end customermenu

void addcustomer()
{
 /*
    Add Customer
    Allows the user to: add a customer
			add another customer or return to the customer menu
 */
 int cont, id;
 cont = 1;
 Customer newcustomer;
 FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","ab+");
 FILE* CID = fopen ("C:\\TURBOC3\\BIN\\IDcustomer.txt","r");
 int num;
 fscanf(CID, "%d", &num );
 while (cont==1)//accept new customer
 {
  num = num++;
  newcustomer.cid = num;
  clrscr();
  printf ("ENTER CUSTOMER INFORMATION\n");
  printf ("First name:");
  scanf ("%s", newcustomer.fname);
  printf ("Last name:");
  scanf ("%s", newcustomer.lname);
  printf ("Phone number:");
  scanf ("%s", newcustomer.phone);
  fwrite (&newcustomer, sizeof(Customer), 1,cstfile); //write customer info to binary file
  printf("Customer successfully added.");
  getch();
  clrscr();
  printf("Enter another customer..............1\n");
  printf("Return to customer menu.............0\n\n");
  printf ("Enter the number corresponding to your choice:");
  scanf ("%d", &cont);
 }//end while (cont=1)
 fclose(cstfile);
 fclose(CID);
 CID = fopen("C:\\TURBOC3\\BIN\\IDcustomer.txt","w"); //write last used cid to text file
 fprintf(CID,"%d", num);
 fclose(CID);
}//end addcustomer

void editcustomer()
{
 /*
    Edit Customer
    Allows user to: enter a cid and edit customer's info
		    edit another customer's info or return to main menu
 */
 clrscr();
 Customer cst;
 FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb+");
 int n=0;
 int found = 0;
 int idno;
 clrscr();
 printf("Enter the customer's ID Number:");
 scanf("%d", &idno);
 fread(&cst, sizeof(Customer),1,cstfile);
 while ((!feof(cstfile))&&(found==0))//search for customer
 {
   n++;
   if (idno==cst.cid)//do edits
   {
     found=1;
     clrscr();
     int toedit;
     clrscr();
     printf("Current information\n");
     printf("Customer ID:%d\n", cst.cid);
     printf("1)Name: %s %s\n", cst.fname,cst.lname);
     printf("2)Phone number: %s\n", cst.phone);
     printf("0)Return to customer menu\n");
     printf("\nEnter the number corresponding to the information you wish to edit:");
     int edch;
     scanf("%d", &edch);
     while (edch!=0) //while the user has not chosen to return to menu
     {
	if (edch==1)
	{
	  printf("\nEnter new name:");
	  scanf("%s %s",cst.fname,cst.lname);
	}//end if ch=1
	else if (edch==2)
	{
	  printf("\nEnter new phone number:");
	  scanf("%s", cst.phone);
	}//end if edch=2
	else
	{
	  printf("\nInvalid choice\n");
	  getch();
	}//end invalid edch
	printf("\nEnter number corresponding to your choice:");
	scanf("%d", &edch);
     }//end while(edch!=0)
     fseek(cstfile, (n-1)*sizeof(Customer),SEEK_SET); //seeks the record to edit
     fwrite(&cst, sizeof(Customer),1,cstfile);
     clrscr();
     printf("Successfully updated!\n");
     printf("Customer ID:%d\n", cst.cid);
     printf("Name: %s %s\n", cst.fname,cst.lname);
     printf("Phone number: %s\n", cst.phone);
     getch();
  }//end if (idno==cst.id)
  else
  fread(&cst, sizeof(Customer),1,cstfile);
  }//end while((!feof(cstfile))&&(found==0))
  if (found==0)
  {
    printf ("Customer not found.");
    getch();
  }
  fclose(cstfile);
}//end editcustomer

void searchcustomer()
{
 /*
   Search customer
   Allows user to: search for customer by name
		   search for customer by id
		   search for another customer or return to the customer menu
 */
 clrscr();
 int cont=1, id, opt, found=0;
 char first[10], last[10];
 Customer cst;
 while (cont==1)
 {
   clrscr();
   printf("Search by:\n");
   printf("Name......................1\n");
   printf("ID........................2\n");
   printf("Return to customer menu...0\n\n");
   printf("Enter the number corresponding to your choice:");
   scanf("%d", &opt);
   while (opt!=0) //while the user has not chosen to exit
   {
    if(opt==1) //search by name
    {
      clrscr();
      found=0;
      printf("Enter name:");
      scanf("%s %s", first, last);
      FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb+");
      fread(&cst, sizeof(Customer),1,cstfile);
      while ((found == 0) && (!feof(cstfile)))
      {
	if ((strcmp(cst.fname,first)==0)&& (strcmp(cst.lname,last)==0))
	{
	  found = 1;
	  // display customer info
	  printf("Customer ID:%d\n", cst.cid);
	  printf("Name: %s %s\n", cst.fname,cst.lname);
	  printf("Phone number: %s\n", cst.phone);
	  getch();
	}//if ((strcmp(cst.fname,first))&& (srtcmp(cst.lname,last)))
	else
	  fread(&cst, sizeof(Customer),1,cstfile);
      }//end  while ((found == 0) && (!feof(cstfile)))
      fclose(cstfile);
      if (found==0)
      {
	printf ("Customer not found.");
	getch();
      }
      opt=0;
    }//end if opt=1
    else if (opt==2) //search byID
    {
      clrscr();
      found=0;
      printf("Enter ID number:");
      scanf("%d",&id);
      FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb+");
      fread(&cst, sizeof(Customer),1,cstfile);
      while ((found == 0) && (!feof(cstfile)))
      {
	if (cst.cid==id)
	{
	  found = 1;
	  printf("Customer ID:%d\n", cst.cid);
	  printf("Name: %s %s\n", cst.fname,cst.lname);
	  printf("Phone number: %s\n", cst.phone);
	  getch();
	}//if (cst.cid==id)
	else
	  fread(&cst, sizeof(Customer),1,cstfile);
      }//end  while ((found == 0) && (!feof(cstfile)))
      fclose(cstfile);
      if (found==0)
      {
	printf ("Customer not found.");
	getch();
      }
      opt=0;
    }//end if opt=2
    else//invalid choice
    {
      clrscr();
      printf("Current choice is invalid.\n");
      printf("\nSearch by:\n");
      printf("Name......................1\n");
      printf("ID........................2\n");
      printf("Return to customer menu...0\n\n");
      printf("Enter the number corresponding to your choice:");
      scanf("%d", &opt);
    }//end else invalid
   }//end while opt!=0
   clrscr();
   printf("Search for new customer...1\n");
   printf("Return to customer menu...0\n\n");
   printf("Enter the number corresponding to your choice:");
   scanf("%d", &cont);
 }//end while cont==1
}// end searchcustomer

void viewcustomer()
{
 /*
    View Customer
    Allows the user to: view a list of customer information
			the user is then returned to the customer menu
 */
 clrscr();
 Customer cst;
 FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb");
 FILE* csttxt =  fopen("C:\\TURBOC3\\BIN\\customer_list.txt","w");
 printf("CUSTOMERS\n");
 printf("---------------------------------------\n");
 printf("CID  Name                  Phone Number\n");
 printf("----------------------------------------\n");
 //print to text file
 fprintf(csttxt,"CUSTOMERS\n");
 fprintf(csttxt,"---------------------------------------\n");
 fprintf(csttxt,"CID  Name                  Phone Number\n");
 fprintf(csttxt,"---------------------------------------\n");
 fread(&cst, sizeof(Customer),1,cstfile);
 while(!feof(cstfile))//write customer info
 {
   printf("%4d %10s %10s %8s\n",cst.cid,cst.fname,cst.lname,cst.phone);
   fprintf(csttxt,"%4d %10s %10s %8s\n",cst.cid,cst.fname,cst.lname,cst.phone);
   fread(&cst, sizeof(Customer),1,cstfile);
 }//end while(!feof(cstfile))
 fclose(cstfile);
 fclose(csttxt);
 getch();
}//end viewcustomer

void deletecustomer()
{
  /*
     Delete Customer
     Allows user to: delete a customer's info by entering their ID
		     delete another customer or return to the customer menu
  */
  clrscr();
  int id, found=0;
  Customer cst;
  FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb");
  FILE* temp = fopen("C:\\TURBOC3\\BIN\\temp.bin","wb");
  printf("Enter ID for customer to be deleted:");
  scanf("%d", &id);
  fread(&cst, sizeof(Customer),1,cstfile);
  while (!feof(cstfile))
  {
    if (cst.cid==id)
    {
      //skip record to be deleted
      found=1;
      fread(&cst, sizeof(Customer),1,cstfile);
    }
    fwrite(&cst, sizeof(Customer),1,temp);
    fread(&cst, sizeof(Customer),1,cstfile);
  }//end while ((found == 0) && (!feof(cstfile)))
  if (found==1)
    printf("Customer deleted");
  else
    printf("Customer not found");
  getch();
  fclose(cstfile);
  fclose(temp);
  temp = fopen("C:\\TURBOC3\\BIN\\temp.bin","rb");
  cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","wb");
  fread(&cst, sizeof(Customer),1,temp);
  while(!feof(temp)) //write temp file to customer file
  {
    fwrite(&cst, sizeof(Customer),1,cstfile);
    fread(&cst, sizeof(Customer),1,temp);
  }//while(!feof(temp))
  fclose(cstfile);
  fclose(temp);
}//end deletecustomer


void itemmenu()
{
  /*
    Item Menu
    Allows the user to: enter the add item function
			enter the edit item function
			enter the search item function
			enter the view item function
			enter the delete item function
			return to the main menu
 */
 void additem(); //function prototypes
 void edititem();
 void searchitem();
 void viewitem();
 void deleteitem();
 clrscr();
 printf("Welcome to Item menu\n");
 printf("Add....................1\n");
 printf("Edit...................2\n");
 printf("Search.................3\n");
 printf("View...................4\n");
 printf("Delete.................5\n");
 printf("RETURN to main menu....0\n\n");
 int Ich;
 printf("Enter the number corresponding to your choice:");
 scanf("%d", &Ich);
 while(Ich!=0) //while the user has not chosen to exit
 {
   if (Ich==1)      //open add item function
     additem();
   else if (Ich==2) //open edit item function
     edititem();
   else if (Ich==3) //open search item function
     searchitem();
   else if (Ich==4) //open view item function
     viewitem();
   else if (Ich==5) //open delete item function
     deleteitem();
   else // for invalid choice
   {
     printf("Invalid choice entered");
     getch();
   }
 // Allow user to select new choice
 clrscr();
 printf("Welcome to Item menu\n");
 printf("Add....................1\n");
 printf("Edit...................2\n");
 printf("Search.................3\n");
 printf("View...................4\n");
 printf("Delete.................5\n");
 printf("RETURN to main menu....0\n\n");
 printf("Enter the number corresponding to your choice:");
 scanf("%d", &Ich);
 }//end while(Ich!=0)
}//end itemmenu

void additem()
{
 /*
    Add Item
    Allows the user to: add an item
			add another item or return to the item menu
 */
 clrscr();
 int cont, id;
 cont = 1;
 Item newitem;
 FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","ab+");
 FILE* IID = fopen ("C:\\TURBOC3\\BIN\\IDitem.txt","r");
 int num;
 fscanf(IID, "%d", &num );//read ID
 while (cont==1)//accept new item
 {
  num = num++;
  newitem.iid = num;
  clrscr();
  printf ("ENTER ITEM INFORMATION\n");
  printf ("Item name:");
  scanf ("%s", newitem.iname);
  printf ("Description:");
  scanf ("%s", newitem.description);
  printf ("Cost:$");
  scanf ("%f", &newitem.cost);
  fwrite (&newitem, sizeof(Item), 1,itmfile);//write item to binary file
  printf("Item successfully added.");
  getch();
  clrscr();
  printf("Enter another item...............1\n");
  printf("Return to item menu..............0\n\n");
  printf ("Enter the number corresponding to your choice:");
  scanf ("%d", &cont);
 }//end while (cont=1)
 fclose(itmfile);
 fclose(IID);
 IID = fopen("C:\\TURBOC3\\BIN\\IDitem.txt","w");
 fprintf(IID,"%d", num);
 fclose(IID);
}//end additem

void edititem()
{
 /*
    Edit Item
    Allows user to: enter Iid and edit item's info
		    edit another item's info or return to item menu
 */
 clrscr();
 Item itm;
 FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb+");
 int n=0;
 int found = 0;
 int idno;
 clrscr();
 printf("Enter the item's ID Number:");
 scanf("%d", &idno);
 fread(&itm, sizeof(Item),1,itmfile);
 while ((!feof(itmfile))&&(found==0))//search for item
 {
   n++;
   if (idno==itm.iid)//do edits
   {
     found=1;
     clrscr();
     int toedit;
     clrscr();
     printf("Current information\n");
     printf("Item ID:%d\n", itm.iid);
     printf("1)Name: %s \n", itm.iname);
     printf("2)Description: %s\n", itm.description);
     printf("3)Cost: $%6.2f\n",itm.cost);
     printf("0)Return to item menu\n");
     printf("\nEnter the number corresponding to the information you wish to edit:");
     int edch;
     scanf("%d", &edch);
     while (edch!=0) //while user has not chosen to return to menu
     {
	if (edch==1)
	{
	  printf("\nEnter new name:");
	  scanf("%s ",itm.iname);
	}//end if ch=1
	else if (edch==2)
	{
	  printf("\nEnter new description:");
	  scanf("%s", itm.description);
	}//end if edch=2
	else if (edch==3)
	{
	  printf("\nEnter new price:$");
	  scanf("%f", &itm.cost);
	}//end if edch=3
	else
	{
	  printf("\nInvalid choice\n");
	  getch();
	}//end invalid edch
	printf("\nEnter number corresponding to your choice:");
	scanf("%d", &edch);
     }//end while(edch!=0)
     fseek(itmfile, (n-1)*sizeof(Item),SEEK_SET); //find record to be rewritten
     fwrite(&itm, sizeof(Item),1,itmfile);
     clrscr();
     printf("Successfully updated!\n");
     printf("\nItem ID:%d\n", itm.iid);
     printf("Name: %s \n", itm.iname);
     printf("Description: %s\n", itm.description);
     printf("Cost: $%6.2f",itm.cost);
     getch();
  }//end if (idno==cst.id)
  else
  fread(&itm, sizeof(Item),1,itmfile);
  }//end while((!feof(itmfile))&&(found==0))
  if (found==0)
  {
    printf ("Item not found.");
    getch();
  }
  fclose(itmfile);
}//end edititem

void searchitem()
{
 /*
   Search Item
   Allows user to: search for item by name
		   search for item by id
		   search for another item or return to the item menu
 */
 clrscr();
 int cont=1, id, opt, found=0;
 char name[15];
 Item itm;
 while (cont==1)
 {
   clrscr();
   printf("Search by:\n");
   printf("Name..................1\n");
   printf("ID....................2\n");
   printf("Return to item menu...0\n\n");
   printf("Enter the number corresponding to your choice:");
   scanf("%d", &opt);
   while (opt!=0)
   {
    if(opt==1)//search by name
    {
      clrscr();
      found=0;
      printf("Enter name:");
      scanf("%s", name);
      FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb+");
      fread(&itm, sizeof(Item),1,itmfile);
      while ((found == 0) && (!feof(itmfile)))
      {
	if (strcmp(itm.iname,name)==0)
	{
	  found=0;
	  //ptint item info
	  printf("Item ID:%d\n", itm.iid);
	  printf("Name: %s \n", itm.iname);
	  printf("Description: %s\n", itm.description);
	  printf("Cost: $%6.2f",itm.cost);
	  getch();
	}//if ((strcmp(itm.iname,name)
	else
	  fread(&itm, sizeof(Item),1,itmfile);
      }//end  while ((found == 0) && (!feof(itmfile)))
      fclose(itmfile);
      if (found==0)
      {
	printf ("Item not found.");
	getch();
      }
      opt=0;
    }//end if opt=1
    else if (opt==2) //search by id
    {
      clrscr();
      printf("Enter ID number:");
      scanf("%d",&id);
      FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb+");
      fread(&itm, sizeof(Item),1,itmfile);
      while ((found == 0) && (!feof(itmfile)))
      {
	if (itm.iid==id)
	{
	  found = 1;
	  //print item info
	  printf("Item ID:%d\n", itm.iid);
	  printf("Name: %s \n", itm.iname);
	  printf("Description: %s\n", itm.description);
	  printf("Cost: $%6.2f",itm.cost);
	  getch();
	}//if (itm.iid==id)
	else
	  fread(&itm, sizeof(Item),1,itmfile);
      }//end  while ((found == 0) && (!feof(itmfile)))
      if (found==0)
      {
	printf ("Item not found.");
	getch();
      }
      opt=0;
    }//end if opt=2
    else//invalid
    {
      clrscr();
      found=0;
      printf("Current choice is invalid.");
      printf("\nSearch by:\n");
      printf("Name.................1\n");
      printf("ID...................2\n");
      printf("Return to item menu..0\n\n");
      printf("Enter the number corresponding to your choice:");
      scanf("%d", &opt);
    }//end else invalid
   }//end while opt!=0
   clrscr();
   printf("Search for new item.............1\n");
   printf("Return to item menu.............0\n\n");
   printf("Enter the number corresponding to your choice:");
   scanf("%d", &cont);
 }//end while cont==1
}//end searchitem

void viewitem()
{
 /*
    View Item
    Allows the user to: view a list of item information
			the user is then returned to the item menu
 */
 clrscr();
 Item itm;
 FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb");
 FILE* itmtxt =  fopen("C:\\TURBOC3\\BIN\\item_list.txt","w");
 printf("ITEMS\n");
 printf("-------------------------------------------------------\n");
 printf("IID  Name          Description                    Cost\n");
 printf("-------------------------------------------------------\n");
 //print to text file
 fprintf(itmtxt,"ITEMS\n");
 fprintf(itmtxt,"--------------------------------------------------------\n");
 fprintf(itmtxt,"IID  Name            Description                   Cost\n");
 fprintf(itmtxt,"--------------------------------------------------------\n");
 fread(&itm, sizeof(Item),1,itmfile);
 while(!feof(itmfile))//write item info
 {
   printf("%4d %10s %30s   $%6.2f\n",itm.iid,itm.iname, itm.description, itm.cost);
   fprintf(itmtxt,"%4d %10s %30s   $%6.2f\n",itm.iid,itm.iname, itm.description, itm.cost);
   fread(&itm, sizeof(Item),1,itmfile);
 }//end while(!feof(itmfile))
 fclose(itmfile);
 fclose(itmtxt);
 getch();
}//end viewitem

void deleteitem()
{
  /*
     Delete Item
     Allows user to: delete item info by entering ID
		     delete another item or return to the item menu
  */
  clrscr();
  int id, found=0;
  Item itm;
  FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb");
  FILE* temp = fopen("C:\\TURBOC3\\BIN\\temp.bin","wb");
  printf("Enter ID for item to be deleted:");
  scanf("%d", &id);
  fread(&itm, sizeof(Item),1,itmfile);
  while (!feof(itmfile))
  {
    if (itm.iid==id)
    {
      //skip item to be deleted
      fread(&itm, sizeof(Item),1,itmfile);
      found=1;
    }
    fwrite(&itm, sizeof(Item),1,temp);
    fread(&itm, sizeof(Item),1,itmfile);
  }//end while ((found == 0) && (!feof(itmfile)))
  if (found==1)
    printf("Item deleted");
  else
    printf("Item not found");
  getch();
  fclose(itmfile);
  fclose(temp);
  temp = fopen("C:\\TURBOC3\\BIN\\temp.bin","rb");
  itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","wb");
  fread(&itm, sizeof(Item),1,temp);
  while(!feof(temp))//write temp file to item file
  {
    fwrite(&itm, sizeof(Item),1,itmfile);
    fread(&itm, sizeof(Item),1,temp);
  }//while(!feof(temp))
  fclose(itmfile);
  fclose(temp);
}//end deleteitem



void purchasemenu()
{
 /*
    Purchase manu
    Allows the user to: enter add purchase function
			enter search purchase function
			enter view purchase function
			return to main menu
 */
 void addpurchase();   //call prototypes
 void searchpurchase();
 void viewpurchase();
 clrscr();
 printf("Welcome to Purchase menu\n");
 printf("Add....................1\n");
 printf("Search.................2\n");
 printf("View...................3\n");
 printf("RETURN to main menu....0\n\n");
 int Pch;
 printf("Enter the number corresponding to your choice:");
 scanf("%d", &Pch);
 while(Pch!=0)
 {
   if (Pch==1)        //open add purchase function
     addpurchase();
   else if (Pch==2)   //open search purchase function
     searchpurchase();
   else if (Pch==3)   //open view purchase function
     viewpurchase();
   else // for invalid choice
   {
     printf("Invalid choice entered");
     getch();
   }
 // Allow user to select new choice
 clrscr();
 printf("Welcome to Purchase menu\n");
 printf("Add....................1\n");
 printf("Search.................2\n");
 printf("View...................3\n");
 printf("RETURN to main menu....0\n\n");
 printf("Enter the number corresponding to your choice:");
 scanf("%d", &Pch);
 }//end while(Pch!=0)
}//end purchasemenu

Purchase initpchs()
{
  //intitaializes all fields of the purchase record
  Purchase x;
  x.pid=0;
  x.billno=0;
  x.cid=0;
  x.iid=0;
  x.qty=0;
  x.total=0;
  strcpy(x.date,"--/--/--");
  return x;
}//end initpchs()

CNodePtr makecst( Customer c)
{
  //creates and enters info into customer node
  CNodePtr node = (CNodePtr) malloc (sizeof (CNode));
  node->cst.cid = c.cid;
  strcpy(node->cst.fname,c.fname);
  strcpy(node->cst.lname,c.lname);
  strcpy(node->cst.phone,c.phone);
  node->next=NULL;
  return node;
}//end makecst

INodePtr makeitm( Item i)
{
  //creates ande enters information into item node
  INodePtr node = (INodePtr) malloc (sizeof (INode));
  node->itm.iid = i.iid;
  strcpy(node->itm.iname,i.iname);
  strcpy(node->itm.description,i.description);
  node->itm.cost=i.cost;
  node->next=NULL;
  return node;
}//end makecst

void addpurchase()
{
  /*
    Add purchase
    Allows user to: add an new purchase
		    add additional items to a bill
		    add another purchase or return to the purchase menu
  */
  Purchase initpchs();
  CNodePtr makecst( Customer );
  clrscr();
  FILE*pchsfile=fopen("C:\\TURBOC3\\BIN\\purchases.bin","ab+");
  //load cstfile into linked list
  CNodePtr C_top=NULL,C_curr,C_last=NULL;
  Customer c;
  FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb");
  fread(&c, sizeof(Customer),1,cstfile);
  while (!feof(cstfile))
  {
    C_curr=makecst(c);
    if (C_top==NULL)
      C_top=C_curr;
    else
      C_last->next = C_curr;
    C_last=C_curr;
    fread(&c, sizeof(Customer),1,cstfile);
  }//end while !feof(cstfile)
  fclose(cstfile);
  //load item file into linked list
  INodePtr I_top=NULL,I_curr,I_last=NULL;
  Item i;
  FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb");
  fread(&i, sizeof(Item),1,itmfile);
  while (!feof(itmfile))
  {
    I_curr=makeitm(i);
    if (I_top==NULL)
      I_top=I_curr;
    else
      I_last->next = I_curr;
    I_last=I_curr;
    fread(&i, sizeof(Item),1,itmfile);
  }//end while !feof(itmfile)
  fclose(itmfile);
  //Enter purchase info
  int CID;
  Purchase pchs= initpchs();
  printf("Enter the customer ID:");
  scanf("%d", &CID);
  //search for customer
  CNodePtr cstart;
  cstart=C_top;
  int cfound=0;
  while ( (cstart != NULL) && (cfound == 0) )
    {
      if (cstart->cst.cid == CID)
	{
	  cfound = 1;
	  pchs.cid=CID;
	}
      else
	cstart = cstart->next;
    }
  if (cfound==1) //process purchase
  {
    FILE* BN = fopen ("C:\\TURBOC3\\BIN\\Billno.txt","r");
    FILE* PN = fopen ("C:\\TURBOC3\\BIN\\Pno.txt","r");
    int bill, pno;
    fscanf(BN, "%d", &bill );
    fscanf(PN, "%d", &pno );
    bill++;
    pchs.billno=bill;
    printf("Enter date(dd/mm/yy):");
    scanf("%s", pchs.date);
    int cont=1;
    while (cont!=0)
    {
      int IID;
      printf("Enter item ID:");
      scanf("%d", &IID);
      //search for item
      INodePtr istart;
      istart=I_top;
      int Ifound=0;
      while ( (istart != NULL) && (Ifound == 0) )
      {
	if (istart->itm.iid == IID)
	  {
	    Ifound = 1;
	    pchs.iid=IID;
	  }
	else
	  istart = istart->next;
      }
      if(Ifound==1)
      {
	pno++;
	pchs.pid=pno;
	printf("Enter quantity purchased:");
	scanf("%d", &pchs.qty);
	pchs.total=pchs.qty* istart->itm.cost;
	fwrite(&pchs, sizeof(Purchase),1,pchsfile);//write purchase to file
	printf("\n\n1) Add new Item\n");
	printf("0)Return to Purchase menu\n");
	printf("Enter number corresponding to your choice:");
	scanf("%d", &cont);
      }//end if Ifound=1
      else//enter new ID
      {
	printf("Item not found. Enter new ID:");
	scanf("%d", IID);
      }//end else
    }//end while cont!=0
    fclose(PN);
    fclose(BN);
    fclose(pchsfile);
    BN = fopen ("C:\\TURBOC3\\BIN\\Billno.txt","w");
    PN = fopen ("C:\\TURBOC3\\BIN\\Pno.txt","w");
    fprintf(BN,"%d", bill);
    fprintf(PN,"%d", pno);
    fclose(PN);
    fclose(BN);
    clrscr();
    printf("Transaction complete");
  }//end if found=1
  else
  {
    printf("Customer not found. Enter new ID:");
    scanf("%d", CID);
  }//end else
  getch();
}//end addpurchase



void searchpurchase()
{
  /*
    Search Purchase
    Allows user to: search for purchase by bill number
		    search for another purchase or return to purchase menu
  */
  clrscr();
  CNodePtr makecst( Customer );
  //load cstfile into linked list
  CNodePtr C_top=NULL,C_curr,C_last=NULL;
  Customer c;
  FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb");
  fread(&c, sizeof(Customer),1,cstfile);
  while (!feof(cstfile))
  {
    C_curr=makecst(c);
    if (C_top==NULL)
      C_top=C_curr;
    else
      C_last->next = C_curr;
    C_last=C_curr;
    fread(&c, sizeof(Customer),1,cstfile);
  }//end while !feof(cstfile)
  fclose(cstfile);
  //load item file into linked list
  INodePtr I_top=NULL,I_curr,I_last=NULL;
  Item i;
  FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb");
  fread(&i, sizeof(Item),1,itmfile);
  while (!feof(itmfile))
  {
    I_curr=makeitm(i);
    if (I_top==NULL)
      I_top=I_curr;
    else
      I_last->next = I_curr;
    I_last=I_curr;
    fread(&i, sizeof(Item),1,itmfile);
  }//end while !feof(itmfile)
  fclose(itmfile);
  int cont=1, bill;
  Purchase pchs;
  while (cont!=0)
  {
    clrscr();
    int found=0;
    FILE* pchsfile = fopen("C:\\TURBOC3\\BIN\\purchases_info.bin","rb");
    printf("Enter bill number to search for:");
    scanf("%d", &bill);
    fread(&pchs, sizeof(Purchase),1,pchsfile);
    while ((found ==0)&&(!feof(pchsfile)))//search file
    {
       if (pchs.billno==bill)
       {
	 found=1;
	 CNodePtr ccurr;
	 ccurr=C_top;
	 int Cfound=0;
	 //find customer info for purchase
	 while ( (ccurr != NULL) && (Cfound == 0) )
	 {
	   if (ccurr->cst.cid == pchs.cid)
	     Cfound = 1;
	   else
	     ccurr = ccurr->next;
	 }
	 clrscr();
	 float total = 0;
	 printf("____________________________________________________________\n");
	 printf("Bill no.     :%d\n",pchs.billno);
	 printf("Date         :%s\n",pchs.date);
	 printf("Customer ID  :%d\n", pchs.cid);
	 printf("Customer Name:%s %s\n", ccurr->cst.fname,ccurr->cst.lname);
	 printf("------------------------------------------------------------\n");
	 printf("Purchase ID  Item ID  Item name        Quantity    Cost   \n");
	 printf("------------------------------------------------------------\n");
	 while ((pchs.billno==bill)&&(!feof(pchsfile)))//write all purchases on the bill
	 {
	  // Find itminfo
	   INodePtr icurr;
	   icurr=I_top;
	   int Ifound=0;
	   while ( (icurr!= NULL) && (Ifound == 0) )
	   {
	     if (icurr->itm.iid == pchs.iid)
	       Ifound = 1;
	     else
	       icurr = icurr->next;
	   }
	   printf("%4d          %4d     %15s     %d     $%4.2f\n", pchs.pid, pchs.iid,icurr->itm.iname,pchs.qty,pchs.total );
	   total = total + pchs.total;
	   fread(&pchs, sizeof(Purchase),1,pchsfile);
	 }//end while pchs.billno = bill
	 printf("------------------------------------------------------------\n");
	 printf("Total:                                         $%8.2f\n", total);
	 printf("------------------------------------------------------------\n");
	 getch();
       }// end if (pchs.billno==bill)
       else
	 fread(&pchs, sizeof(Purchase),1,pchsfile);
    }//end while ((found ==0)&&(!feof(pchsfile)))
    fclose(pchsfile);
    if (found == 0)
      {
	printf("Bill not found");
	getch();
      }
    clrscr();
    printf("Search for new bill.............1\n");
    printf("Return to purchase menu.........0\n\n");
    printf("Enter the number corresponding to your choice:");
    scanf("%d", &cont);
  }//end while cont!=0
}//end searchpurchase

void viewpurchase()
{
  /*
    View Purchase
    Allows the user to: view a list of all purchases
			return to the purchase menu
  */
  clrscr();
  CNodePtr makecst( Customer );
  //load cstfile into linked list
  CNodePtr C_top=NULL,C_curr,C_last=NULL;
  Customer c;
  FILE* cstfile = fopen("C:\\TURBOC3\\BIN\\customer_info.bin","rb");
  fread(&c, sizeof(Customer),1,cstfile);
  while (!feof(cstfile))
  {
    C_curr=makecst(c);
    if (C_top==NULL)
      C_top=C_curr;
    else
      C_last->next = C_curr;
    C_last=C_curr;
    fread(&c, sizeof(Customer),1,cstfile);
  }//end while !feof(cstfile)
  fclose(cstfile);
  //load item file into linked list
  INodePtr I_top=NULL,I_curr,I_last=NULL;
  Item i;
  FILE* itmfile = fopen("C:\\TURBOC3\\BIN\\item_info.bin","rb");
  fread(&i, sizeof(Item),1,itmfile);
  while (!feof(itmfile))
  {
    I_curr=makeitm(i);
    if (I_top==NULL)
      I_top=I_curr;
    else
      I_last->next = I_curr;
    I_last=I_curr;
    fread(&i, sizeof(Item),1,itmfile);
  }//end while !feof(itmfile)
  fclose(itmfile);
  Purchase pchs;
  FILE* pchsfile = fopen("C:\\TURBOC3\\BIN\\purchases_info.bin","rb");
  FILE* pchstxt =  fopen("C:\\TURBOC3\\BIN\\purchases_list.txt","w");
  printf("                          PURCHASES\n");
  printf("-----------------------------------------------------------\n");
  printf("-----------------------------------------------------------\n");
  fprintf(pchstxt,"                             PURCHASES\n");
  fprintf(pchstxt,"------------------------------------------------------------\n");
  fprintf(pchstxt,"------------------------------------------------------------\n");
  fread(&pchs, sizeof(Purchase),1,pchsfile);
  while(!feof(pchsfile))//write customer info
  {
    CNodePtr ccurr;
    ccurr=C_top;
    int found=0;
    while ( (ccurr != NULL) && (found == 0) )
    {
      if (ccurr->cst.cid == pchs.cid)
	found = 1;
      else
	ccurr = ccurr->next;
    }
    int bill=pchs.billno;
    float total=0;
    printf("___________________________________________________________\n");
    printf("Bill no.     :%d",pchs.billno);
    printf("\nDate         :%s",pchs.date);
    printf("\nCustomer ID  :%d", pchs.cid);
    printf("\nCustomer Name:%s %s", ccurr->cst.fname,ccurr->cst.lname);
    printf("\n-----------------------------------------------------------\n");
    printf("Purchase ID  Item ID  Item name        Quantity      Cost   \n");
    printf("-----------------------------------------------------------\n");
    fprintf(pchstxt, "___________________________________________________________\n");
    fprintf(pchstxt, "Bill no.     :%d",pchs.billno);
    fprintf(pchstxt, "Date         :%s\n",pchs.date);
    fprintf(pchstxt, "\nCustomer ID  :%d", pchs.cid);
    fprintf(pchstxt, "\nCustomer Name:%s %s", ccurr->cst.fname,ccurr->cst.lname);
    fprintf(pchstxt, "\n------------------------------------------------------------\n");
    fprintf(pchstxt, "Purchase ID  Item ID  Item name      Quantity      Cost   \n");
    fprintf(pchstxt, "-----------------------------------------------------------\n");
    while ((pchs.billno==bill)&&(!feof(pchsfile)))// write all purchases on the bill
    {
      // Find itminfo
      INodePtr icurr;
      icurr=I_top;
      int found=0;
      while ( (icurr!= NULL) && (found == 0) )
      {
	if (icurr->itm.iid == pchs.iid)
	  found = 1;
	else
	  icurr = icurr->next;
      }
      printf("%4d          %4d     %15s %4d          $%4.2f\n", pchs.pid, pchs.iid,icurr->itm.iname,pchs.qty,pchs.total );
      fprintf(pchstxt,"%4d          %4d     %15s %4d          $%4.2f\n", pchs.pid, pchs.iid,icurr->itm.iname,pchs.qty,pchs.total );
      total = total+ pchs.total;
      fread(&pchs, sizeof(Purchase),1,pchsfile);
    }//end while pchs.billno = bill
    printf("-----------------------------------------------------------\n");
    printf("Total:                                            $%8.2f\n", total);
    printf("-----------------------------------------------------------\n");
    fprintf(pchstxt,"-----------------------------------------------------------\n");
    fprintf(pchstxt,"Total:                                            $%8.2f\n", total);
    fprintf(pchstxt,"-----------------------------------------------------------\n");
  }//end while(!feof(pchsfile))
  fclose(pchsfile);
  fclose(pchstxt);
  getch();

}//end viewpurchase