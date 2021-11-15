// Prajwal Mondhe
// Billing system TEN LABS task 3


#include <iostream>
#include <conio.h> //console input output
#include <stdio.h> // ?
#include <cstdlib>
#include <fstream> // file stream
#include <iomanip> // for designing
using namespace std;

fstream file, file1; // Global variables

class product
{
private:
  int pno;
  string name;
  float price, qty, tax, dis;

public:
  void create();
  void show();
  void write();
  void display();
  void admin(); // case2
  void order(); // case1
  void menu();
  void del(int n);
  void search(int n);
  void modify(int n);
};

void product::create()
{
  cout << "\t\t\t Please enter the product No: ";
  cin >> pno;

  cout << "\t\t\t Please enter name of the product:  ";
  cin >> name;

  cout << "\t\t\t Please enter the price of the product:  ";
  cin >> price;

  cout << "\t\t\tPlease Enter the discount (%): ";
  cin >> dis;
}

void product::show()
{
  cout << "\t\t\t\n Product No: " << pno;
  cout << "\t\t\t\n Product Name: " << name;
  cout << "\t\t\t\n Product price: " << price;
  cout << "\t\t\t\n Discount:  " << dis << "%";
}

void product::write()
{
  file.open("shop.txt", ios::out | ios::app);// Write mode
  create(); // Function call
  file << " " << pno << " " << name << " " << price << " " << dis;
  file.close();
  cout << "\t\t\t\n The Product has been created:) ";
  
  getch();
}

void product::display()
{
  system("cls");
  cout << "\t\t\t\n DISPLAY ALL RECORD !!! :\n\n";
  file.open("shop.txt", ios::in); // open in reading mode

  if (!file)
  admin(); // Function call
  file >> pno >> name >> price >> dis;
  while (!file.eof())
  {
    show();
    cout << "\n\n\n===================================";
    file >> pno >> name >> price >> dis;
  }

  file.close();
  getch();
}

void product::order() // void className:: functionName(){}
{
  int order_arr[50], quan[50];
  int c = 0; // counter
  float amt = 0, damt = 0, total = 0;
  char ch;

  file.open("shop.txt", ios::in); // to display the list

  if(file)// If file milti hai
  {

    file.close();
    menu(); // Calling menu function with out p.menu
    //Same class ka function USSI class ke dusre function ko direct call kar sakta


    cout << "\t\t\t\n==========================================================";
    cout << "\t\t\t\n                   PLACE ORDER";
    cout << "\t\t\t\n==========================================================";

    do{
      cout << "\t\t\t\n\n Enter the product no. of your product: ";
      cin >> order_arr[c];
      cout << "\t\t\t\n   Quantity in numbers: ";
      cin >> quan[c];
      c++;

      cout << "\t\t\t\n Do you want to order another product (y/n)?";
      cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "\t\t\t\n Thanks for placing order";
    getch();
    system("cls");
    cout << "\t\t\t\n**********************INVOICE***********************************";
    cout << "\t\t\t\n Pr No. \tPr Name  \tQuantity \tPrice  \tAmount  \tAmount after discount \n";

    for (int x = 0; x <= c; x++)
    {
      file.open("shop.txt", ios::in);
      file>>pno>>name>>price>>dis;

      while(!file.eof())
      {
        if (pno == order_arr[x])
        {
          amt = price * quan[x];
          damt = amt - (amt / 100 * dis);
          cout << "\n" << order_arr[x] << "\t" << name; //
          total += damt;
        }
        file >> pno >> name >> price >> dis;
      }

      file.close();
    }
    cout << "\t\t\t\n TOTAL = " << total;
    getch();
  }
}

void product::admin()
{
  system("cls");
  int choice;
  cout << "\t\t\t\n ADMIN MENU";
  cout << "\t\t\t\n [1] CREATE PRODUCT";
  cout << "\t\t\t\n [2] DISPLAY ALL PRODUCTS";
  cout << "\t\t\t\n [3] SEARCH PRODUCT";
  cout << "\t\t\t\n [4] MODIFY PRODUCT";
  cout << "\t\t\t\n [5] DELETE PRODUCT";
  cout << "\t\t\t\n [6] VIEW PRODUCT MENU";
  cout << "\t\t\t\n [7] BACK TO MAIN MENU";
  cout << "\t\t\t\n----------------------------------------------";
  cout << "\n\n\t\t\t\n Please Enter your choice(1-7): ";

  cin >> choice;
  switch (choice) // faster than if else
  {
  case 1:system("cls");
        write(); // Function call
        break;
  case 2: display(); // Function call
          break;
  case 3:system("cls");
    int num;
    cout << "\t\t\t\n Please enter the product No: ";
    cin >> num;
    search(num); // function call
    break;

  case 4:system("cls");
    cout << "\t\t\t\n Please enter the product No to modify: ";
    cin >> num;
    modify(num);
    break;

  case 5:system("cls");
    cout << "\t\t\t\n Delete record ";
    cout << "\t\t\t\n Please enter the product No to delete: ";
    cin >> num;
    del(num);
    break;

  case 6:menu();
    getch();
    break;

  case 7:break;
  default: cout << "\a";
    admin();
  }
}

void product::search(int n)
{
  int found = 0;
  file.open("shop.txt", ios::in);
  if (!file) // if file no avaliable goto admin
  admin(); // Function call

  file >> pno >> name >> price >> dis;
  while (!file.eof())
  {
    if (pno == n)
    {
      system("cls");
      show(); // Function call
      found = 1;
    }
    file >> pno >> name >> price >> dis;
  }
  file.close();
  if (found == 0)
    cout << "\t\t\t\n Record does not exist";
  getch();
}

void product::modify(int n)
{
  int found = 0;
  system("cls");
  cout << "\t\t\t\n To Modify: ";
  file.open("shop.txt", ios::in); // 1st ope in reading mode

  if (!file)
    admin();
  file1.open("shop1.txt", ios::out | ios::app);
  file >> pno >> name >> price >> dis;

  while (!file.eof())
  {
    if (pno == n)
    {
      show(); // Function call
      cout << "\n\t\t\t\n Please enter new details: \n";
      create();
      file1 << " " << pno << " " << name << " " << price << " " << dis;
      cout << "\t\t\t\n Record updated: ";
      found = 1;
      //exit;
    }
    else
      file1 << " " << pno << " " << name << " " << price << " " << dis;
      file >> pno >> name >> price >> dis;
    
  }
  file.close();
  file1.close();
  remove("shop.txt");
  rename("shop1.txt", "shop.txt");

  if (found == 0)
  cout << "\t\t\t\n Record Not found: ";
  getch();
}

void product::del(int n)
{
  int found = 0;
  file.open("shop.txt", ios::in);
  if (!file)
    admin(); // function call

  file1.open("shop1.txt", ios::out);
  file >> pno >> name >> price >> dis;

  while (!file.eof())
  {
    if (pno == n)
    {
      //show(); // Function call
      cout << "\t\t\t\n Record deleted";
      found = 1;
    }
    else
      file1 << " " << pno << " " << name << " " << price << " " << dis;
      file >> pno >> name >> price >> dis;
  }
  file.close();
  file1.close();
  remove("shop.txt");
  rename("shop1.txt", "shop.txt");

  if (found == 0)
    cout << "\t\t\t\n Record Not found: ";
  getch();
}

void product::menu()
{
  //cout<<"demo text";
  
  system("cls");
  file.open("shop.txt", ios::in);
  cout << "\n\n\t\t\t\n PRODUCT MENU\n";
  cout << "\n\n\t\t\t\n====================================================";
  cout << "\t\t\t\n P. NO\t\t\tNAME\t\t\tPRICE";
  cout << "\t\t\t\n =======================================================\n";
  

  //cout << pno << "\t\t\t" << name << "\t\t\t" << price << "\n";
  file >> pno >> name >> price;
  
  while (!file.eof())
  {
   cout << pno << "\t\t\t" << name << "\t\t\t" << price << "\n";
    file >> pno >> name >> price>>dis;
    getch();
  }

  file.close();
  
}

main()
{
  product p; // Object p of student class

  /* menustart:
       xyzzz
   goto menustart;     */

// Label to repeat this loop untill i exit
menustart:
  int choice;
  system("cls");

  cout << "\t\t\t\n\n\n MAIN MENU:   ";
  cout << "\t\t\t\n\n\n [1] CUSTOMER";
  cout << "\t\t\t\n\n\n [2] ADMIN    ";
  cout << "\t\t\t\n\n\n [3] EXIT     \n";
  cout << "\t\t\t\n\n\n Please Enter your option(1-3) : ";
  cin >> choice;

  switch (choice)
  {
  case 1:system("cls");
    p.order();
    getch();
    break;
  case 2:p.admin();
    break;
  case 3: exit(0);
  default: cout << "\a";
  }

  goto menustart;
}