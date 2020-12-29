#include<iostream.h>
#include<fstream.h>
#include<dos.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

class product                                 //product class
  {public:
  int id;
  char pname[50];
  int cat;
  float price;
  void get();
  void show();
  };


void product::get()                             //get details of product
  {
  cout<<"\nEnter category no: "; cin>>cat;
  cout<<"\nEnter product id: "; cin>>id;
  cout<<"\nEnter product name: "; gets(pname);
  cout<<"\nEnter price: "; cin>>price;
  cout<<"\n\n";
  }

void product::show()                          //to display all products
  {
  cout<<"\nProduct Id: "<<id;
  cout<<"\nProduct name: "<<pname;
  cout<<"\nProduct price: "<<price;
  }


class user                                      //user class
   {
   public:
   char fname[30], lname[30], dob[12], add[50], email[50], pass[10];
   char usname[20];
   long phno;
   void uget();
   };

void user::uget()                                   //get details of user
  {cout<<"\nEnter first name: "; cin>>fname;
  cout<<"\nEnter last name: "; cin>>lname;
  cout<<"\nEnter username: "; cin>>usname;
  cout<<"\nEnter address: "; cin>>add;
  cout<<"\nEnter date of birth: "; cin>>dob;
  cout<<"\nEnter email id: "; cin>>email;
  cout<<"\nEnter phone no: "; cin>>phno;
  passw: cout<<"\n\nEnter password: "; cin>>pass;
  char p[10];
  cout<<"\nConfirm password: "; cin>>p;
  if(strcmp(pass,p)==0)
  cout<<"\n\n\t\tACCOUNT SUCCESSFULLY CREATED";
  else
   {cout<<"Password does not match. Re enter password.";
   goto passw;
   }
  getch();
  }

void bg()                                    //border
  {for(int i=0;i<80;i++)
  cout<<"$";
  for(i=1;i<=80;i++)
   {gotoxy(i,24);
   cout<<"#";   }
  for(i=1;i<25;i++)
   {gotoxy(80,i);
   cout<<"%";    }
  for(i=1;i<25;i++)
   {gotoxy(1,i);
   cout<<"@";}
  gotoxy(2,2);
  }

void billgen(float &totpr)
  {
  product p;
  totpr=0;
  int no=1;
  fstream fy("cart.dat",ios::binary|ios::in|ios::out);   //BILL GENERATION
  while(!fy.eof())
   {
   fy.read((char*)&p,sizeof(p));
   if(fy.eof())break;
   totpr+=p.price;
   cout<<no++<<"\t "<<p.id<<"\t"<<p.pname<<"\t\t1\t"<<p.price<<"\n";
   }
  }

void main()                                 //VOID MAIN
  {
  product p;
  user u;
  int choice;
  char pwd[10];
home: clrscr();
  cout<<"\n\n\t\tWELCOME TO VOGUE\n\n";              //HOME
  for(int i=0;i<77;i++)
  cout<<"=";
  cout<<"\n\n\n\t\t1.ADMIN\n\t\t2.USER\n\t\t3.EXIT\n\nEnter your choice: ";
  cin>>choice;
  switch(choice)
      {
      case 1:                             //ADMIN
	 {
passwd:	 cout<<"\n\nEnter admin password: ";          //password
	 int z=0;
	 char pass[10];
	 while(z<10)
	   {pass[z]=getch();
	   if(pass[z]=='\r')
	   {pass[z]='\0';break;}
	   cout<<"*";
	   z++;
	   }
	 if(strcmp(pass,"project")!=0)
	  {
	  cout<<"\n Wrong password,Access denied\n ";
	  goto passwd;
	  }
admin:	 clrscr();
	 int achoice;
	 cout<<"\n\n\tWELCOME ADMIN\n\n";
	 cout<<"\n\t1.Add product\n\t2.Delete product\n\t3.Edit product\n\t4.Go Back";
	 cout<<"\n\n\tEnter your choice: ";
	 cin>>achoice;
	 switch(achoice)
	   {
	   case 1:                                    //ADD PRODUCT
	     {
	     clrscr();
	     ofstream f1("product.dat",ios::binary|ios::app);
	     p.get();
	     f1.write((char*)&p,sizeof(p));
	     cout<<"\n\nProduct successfully added";
	     getch();
	     }
	   goto admin;
	   case 2:                                    //DELETE PRODUCT
	     {
	     int f=0;
	     clrscr();
	     int dchoice,pid;
	     char pn[20];
	     cout<<"\n\n\tDelete by\n\t1.Product id\n\t2.Product name\n\n\tEnter your choice: ";
	     cin>>dchoice;
	     switch(dchoice)
	       {
	       case 1:                                //del by product id
		 {
		 f=0;
		 cout<<"\n\n\tEnter product id of product to be deleted: ";
		 cin>>pid;
		 ifstream f2("product.dat",ios::binary);
		 ofstream f3("tempprod.dat",ios::binary);
		 while(!f2.eof())
		   {
		   f2.read((char*)&p,sizeof(p));
		   if(f2.eof())break;
		   else if(pid!=p.id)
		   f3.write((char*)&p,sizeof(p));
		   else
		   f++;
		   }
		 if(f==0)
		 cout<<"\nProduct id does not exist\n";
		 else
		   {remove("product.dat");
		   rename("tempprod.dat","product.dat");
		   }
		 }
	       cout<<"\n\n\t\tPRODUCT DELETED";
	       getch();
	       goto admin;
	       case 2:                                //del by product name
		 {
		 f=0;
		 cout<<"\n\n\tEnter name of product to be deleted: ";
		 cin>>pn;
		 ifstream f2("product.dat",ios::binary);
		 ofstream f3("tempprod.dat",ios::binary);
		 while(!f2.eof())
		   {
		   f2.read((char*)&p,sizeof(p));
		   if(f2.eof())break;
		   else if(strcmp(pn,p.pname)!=0)
		   f3.write((char*)&p,sizeof(p));
		   else
		   f++;
		   }
		 if(f==0)
		 cout<<"\nProduct name does not exist\n";
		 else
		   {
		   remove("product.dat");
		   rename("tempprod.dat","product.dat");
		   }
		 }
	       cout<<"\n\n\t\tPRODUCT DELETED";
	       getch();
	       }
	     }
	   goto admin;
	   case 3:                                     //EDIT PRODUCT
	     {
	     clrscr();
	     int uchoice;
	     cout<<"\n\n\t1.Update price\n\t2.update product name\n\n\tEnter your choice: ";
	     cin>>uchoice;
	     switch(uchoice)
	       {
	       case 1:                                   //price update
		 {
		 fstream f4("product.dat",ios::binary|ios::in|ios::out);
		 float x;
		 cout<<"\n\n\tEnter change percentage: ";
		 cin>>x;
		 while(!f4.eof())
		    {
		    f4.read((char*)&p,sizeof(p));
		    p.price+=(x/100)*p.price;
		    f4.seekp(f4.tellp()-sizeof(p));
		    f4.write((char*)&p,sizeof(p));
		    }
		 cout<<"\n\n\tPrice of ALL products updated";
		 getch();
		 }
	       break;
	       case 2:                                  //name update
		 {
		 int f=0;
		 char pn[20],rn[20];
		 fstream f4("product.dat",ios::binary|ios::in|ios::out);
		 cout<<"\n\n\tEnter product name to be altered: ";
		 cin>>pn;
		 while(!f4.eof())
		   {
		   f4.read((char*)&p,sizeof(p));
		   if(strcmp(pn,p.pname)==0)
		    {
		    cout<<"\nEnter altered name: ";
		    cin>>rn;
		    strcpy(p.pname,rn);
		    f4.seekp(f4.tellp()-sizeof(p));
		    f4.write((char*)&p,sizeof(p));
		    f++;
		    }
		   }
		 if(f==0)
		 cout<<"\nProduct does not exist\n";
		 }
	       break;
	       }
	     }
	   goto admin;
	   case 4: goto home;
	   default:cout<<"\n\n\tWRONG CHOICE";
	   }
	 }
      case 2:                                      //USER
	{
user:	user u;
	int uschoice;
	clrscr();
	cout<<"\n\n\t\tWELCOME USER\n\n";
	cout<<"\n\t1.Login\n\t2.Register\n\t3.Go back\n\n\tEnter our choice: ";
	cin>>uschoice;
	switch(uschoice)
	  {
	  case 1:                                   //login
	    {
	    int lchoice,z=0;
	    char pwd[10],username[30];
	    clrscr();
	    ifstream f11("user.dat",ios::binary);
	    cout<<"\n\n\tEnter username: ";
	    gets(username);
	    while(!f11.eof())
	      {
	      f11.read((char*)&u,sizeof(u));
	      if(strcmp(username,u.usname)==0)
		{
 passwrd:       cout<<"\n\tEnter password: ";
		z=0;
		while(z<10)
		  {
		  pwd[z]=getch();
		  if(pwd[z]=='\r')
		    {
		    pwd[z]='\0';break;
		    }
		  cout<<"*";
		  z++;
		  }
		if(strcmp(u.pass,pwd)!=0)
		  {
		  cout<<"\n\tpassword incorrect!!Re-enter password";
		  goto passwrd;
		  }
		else goto shop;
		}
	      }
	    cout<<"Account does not exist for given username. Please register.\n";
	    getch();
	    goto user;
     shop:  clrscr();
	    cout<<"\n\n\t1.View\n\t2.Search\n\t3.Purchase\n\t4.Go back\n\n\tEnter your choice: ";
	    cin>>lchoice;
	    switch(lchoice)
	      {
	      case 1:                                      //view
		 {
		 int vchoice;
		 clrscr();
		 cout<<"\n\n\tCATEGORIES:\n\t\t1.Stationery\n\t\t2.Books\n\t\t3.Electronics\n\n\tEnter category no: ";
		 cin>>vchoice;
		 ifstream f5("product.dat",ios::binary|ios::in);
		 while(!f5.eof())
		    {
		    f5.read((char*)&p,sizeof(p));
		    if(f5.eof())break;
		    else if(vchoice==p.cat)
		      {p.show();
		      cout<<endl;
		      }
		    }
addcart:	 char ychoice;
		 cout<<"\n\tDo you want to purchase any item?<y/n>";
		 cin>>ychoice;
		 if(ychoice=='y'||ychoice=='Y')
		   {
		   int ppid;
		   cout<<"Enter id of product to be purchased: ";
		   cin>>ppid;
		   ifstream fs("product.dat",ios::binary);
		   while(!fs.eof())
		      {fs.read((char*)&p,sizeof(p));
		      if(fs.eof())break;
		      else if(ppid==p.id)
			{
			p.show();
			cout<<"\nAre you sure you want to add to cart?<y/n>";
			cin>>ychoice;
			if(ychoice=='y'||ychoice=='Y')
			 {
			 fs.seekg(fs.tellg()-sizeof(p));
			 ofstream c1("cart.dat",ios::binary|ios::app);
			 c1.write((char*)&p,sizeof(p));
			 cout<<"\nProduct added to cart";
			 getch();
			 goto addcart;
			 }
			}
		      }
		   cout<<"\nProduct does not exist";
		   getch();
		   }
		 }
	      goto shop;
	      case 2:                                      //search
		 {
		 clrscr();
		 char ppname[29];
		 int fl=0;
		 cout<<"\n\n\t\tSEARCH BY Product name\n\n\t\tEnter product name to be searched: ";
		 gets(ppname);
		 ifstream f6("product.dat",ios::binary|ios::in);
		 while(!f6.eof())
		    {
		    f6.read((char*)&p,sizeof(p));
		    if(strcmp(p.pname,ppname)==0)
		       {
		       f6.seekg(f6.tellg()-sizeof(p));
		       p.show();
		       fl++;
		       getch();
		       goto shop;
		       }
		    }
		 if(fl==0)
		 cout<<"\n\n\t\tProduct does not exist.Search again.";
		 getch();
		 }
	      goto shop;
	      case 3:                                  //purchase
		 {
		 clrscr();
      delprod:	 int pppid;
		 fstream f8("cart.dat",ios::binary|ios::in|ios::out);
		 while(!f8.eof())
		   {
		   f8.read((char*)&p,sizeof(p));
		   if(f8.eof())break;
		   p.show();
		   cout<<endl;
		   }
		 cout<<"\n\n\tDo you want to delete any product<y/n>?";
		 char choice2;
		 int f=0;
		 cin>>choice2;
		 if(choice2=='y'||choice2=='Y')
		     {
		     cout<<"\nenterid of product to be deleted";
		     cin>>pppid;
		     fstream fy("cart.dat",ios::binary|ios::in|ios::out);
		     fstream f9("tempcart.dat",ios::binary,ios::in);
		     while(!fy.eof())
		      {
		      fy.read((char*)&p,sizeof(p));
		      if(fy.eof())break;
		      else if(p.id!=pppid)
		      f9.write((char*)&p,sizeof(p));
		      else
		      f++;
		      }
		     if(f==0)
		     cout<<"\nProduct id does not exist\n";
		     else
		      {
		      remove("cart.dat");
		      rename("tempcart.dat","cart.dat");
		      cout<<"\n\tproduct removed from cart";
		      getch();
		     }
		     goto delprod;
		     }
		 char choice3;
		 cout<<"\n\n\tDo you want to proceed to checkout?<y/n>";
		 cin>>choice3;
		 if(choice3=='y'||choice3=='Y')
		     {
		     clrscr();
		     cout<<"\n\n\t\t\tBILL\n";
		     for(i=0;i<80;i++)
		     cout<<"*";
		     cout<<endl;
		     for(i=0;i<80;i++)
		     cout<<"-";
		     cout<<endl;
		     cout<<"S.No\tProdId\tProdName\tQty\tPrice\n";
		     for(i=0;i<80;i++)
		     cout<<"-";
		     cout<<endl;
		     float totpr=0;
		     billgen(totpr);
		     for(i=0;i<80;i++)
		     cout<<"*";
		     cout<<endl<<"\t\tTotal(without tax):"<<totpr;
		     cout<<"\n\tTAX: 8%";
		     totpr+=0.08*totpr;
		     cout<<"\t\tTOTAL PRICE: "<<totpr<<endl;
		     for(i=0;i<80;i++)
		     cout<<"*";
		     cout<<endl;
		     cout<<"\n\tProceed to checkout";
		     getch();
		     remove("cart.dat");
		     goto exit;
		     }
		 else goto shop;
		 }
	      break;
	      case 4:goto home;
	      default:cout<<"\n\n\tWRONG CHOICE";
	      }
	    }
	  goto user;
	  case 2:                                       //register
	      {
	      ofstream f10("user.dat",ios::binary);
	      cout<<"\n\n\tREGISTER";
	      u.uget();
	      f10.write((char*)&u,sizeof(u));
	      }
	  goto user;
	  case 3:
	  goto home;
	  default:cout<<"\n\n\tWRONG CHOICE";
	  }
     case 3:
exit:clrscr();                                          //EXIT
     cout<<"done by\n\n\t\tKEERTHANA SANKAR\n\n\t\tXII-A";
     getch();
     default:cout<<"\n\n\tWRONG CHOICE";
     }
}   }





























