#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
struct client
{
char no[20];
char name[50];
float amt; //To be calculated
int type;
int min;
}s;
void insert();
void display();
void modify();
void modify1();
void del(char *);
void search();
float pack1(int);
float pack2(int);
float pack3(int);
int selectpack();
int n=0;
void main()
{
   system("cls");
   printf("\n\n\n**************************************************************");
   printf("\n\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM------");
   printf("\n\t\t****************************************************************");
   printf("\n\t\t\t\t\t\t\t\t\t\t By : Keerthana S - 132");
   printf("\n\t\t\t\t\t\t\t\t\t\t By : Subha R - 112");
   printf("\n\t\t\t\t\t\t\t\t\t\t By : Shruti S.P - 107");
   Sleep(2000);
   getch();
   system("cls");
   int z,ch;
   FILE *f;
   f=fopen("ab.bin","wb");
   fclose(f);
   char password[20],no[20];
   do{ 
   printf("\n\n\n 1.LOGIN as ADMIN \n\n\n 2.LOGIN as USER \n\n\n 3.EXIT \n\n\n Enter choice: ");
   scanf("%d",&z);
   switch(z)
   {
      case 1:
             passwd:
             printf("\n Enter password:"); 
             int p=0; 
             do{ 
                     password[p]=getch(); 
                     if(password[p]!='\r')
                     { 
                         printf("*"); 
                     } 
                     p++; 
                }while(password[p-1]!='\r'); 
              password[p-1]='\0'; 
              if(strcmp(password,"pass")!=0)
              {
                  printf("\n Wrong password..Access denied!!Try again..");
                  goto passwd;
              }
              else
              {
                  do
                  {
                     system("cls");
		     printf("\n 1 : For adding new records.\n 2 : for list of records");
		     printf("\n 3 : for modifying records.");
		     printf("\n 4 : for searching records.");
		     printf("\n 5 : for deleting records.\n 6 : To log out \n Enter choice:");
                     scanf("%d",&ch);
                     switch(ch)
		     {
			case 1:
				insert();break;
			case 2:
				display();break;
			case 3:
				modify1();break;
			
			case 4:
                                search();
                                break;
			case 5:
                                printf("\n Enter phone number to delete: ");
                                scanf("%s",no);
				del(no);break;
			case 6:
				system("cls");
				printf("\n\n\t\t\t\tTHANK YOU");
                                getch();
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
                       }
                    }while(ch!=6);
                 }
                 break;
      case 2:
                  do
                  {
                     system("cls");
	             printf("\n 1 : For name and pack modification");
		     printf("\n 2 : Display user details");
	             printf("\n 3 : Exit \n Enter choice:");
	             scanf("%d",&ch);
                     switch(ch)
		     {
			case 1:
				modify();break;
			
			case 2: 
			        search();
                                break;
			case 3:
                                system("cls");
				printf("\n\n\t\t\t\tTHANK YOU");
				printf("\n\n\n\n\tFOR USING OUR SERVICE");
                                getch();
				break;

			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
                      }
                 }while(ch!=3);
                 break;
       case 3:
		system("cls");
		printf("\n\n\t\t\t\tTHANK YOU");
		break;
      default:
		system("cls");
		printf("Incorrect Input");
		printf("\nAny key to continue");
		getch();
  }}while(z!=3);
}
void insert()
{
	FILE *f;
	char test;
	f=fopen("ab.bin","ab+");
	if(f==0)
	{       f=fopen("ab.bin","wb+");
		system("cls");
		printf("please wait while we configure your computer");
		printf("/npress any key to continue");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Enter phone number:");
		scanf("%s",s.no);
                printf("\n Enter name:");
		fflush(stdin);      
		scanf("%[^\n]",&s.name);  //Inputting a line
		printf("\n Enter pack type:");
		s.type=selectpack();
		printf("\n Enter talk-time minutes:");
		scanf("%d",&s.min);
                if(s.type==1)
                    s.amt=pack1(s.min);
                if(s.type==2)
                    s.amt=pack2(s.min);
                if(s.type==3)
                    s.amt=pack3(s.min); 
		fwrite(&s,sizeof(s),1,f);
                n+=1;
               	fflush(stdin);
		system("cls");
		printf("Record added");
		printf("\n Press esc key to exit, any other key to add other record:");
		test=getche();
		if(test==27)   //Ascii value of escape character
			break;
	}
	fclose(f);
}
void display()
{
	FILE *f;
	int i;
	if((f=fopen("ab.bin","rb"))==NULL)
		exit(0);
	system("cls");
	printf("Phone Number\tUser Name\tPack Type\tTalk-time Minutes\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
        
	for(i=0;i<n;i++)
	{
                fread(&s,sizeof(s),1,f);
		printf("\n%-10s\t%-10s\tPack %d\t\t%d minutes     \tRs.%.2f \n",s.no,s.name,s.type,s.min,s.amt);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}
void del(char *no)
{
        system("cls");
	FILE *f;
        f=fopen("ab.bin","rb+");
        int i,fl=0;
        for(i=0;i<n;i++)
        {
            fread(&s,sizeof(s),1,f);
            if(strcmp(s.no,no)==0)
            {
               for(int j=i+1;j<n;j++)
               {
                  fread(&s,sizeof(s),1,f);
                  fseek(f,-2*sizeof(s),SEEK_CUR);
                  fwrite(&s,sizeof(s),1,f);
                  fseek(f,sizeof(s),SEEK_CUR);
               }
               printf("\n Successfully deleted!!");
               fl=1;
               n-=1;
               break;
            }
         }
         if(fl==0)
            printf("\n No such record found ");
        fclose(f);
        getch(); 
}
void search()
{
	FILE *f;
	int flag=1;
        char no[20];
        printf("\n Enter number to get details: ");
        scanf("%s",no);
	f=fopen("ab.bin","rb+");
	for(int i=0;i<n;i++)
	{
                
                fread(&s,sizeof(s),1,f);
		if(strcmp(s.no,no)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhone no: %s\nName: %s\nPack type: %d\nTalk-time: %dminutes\nAmount: Rs.%0.2f\n",s.no,s.name,s.type,s.min,s.amt);
                        getch();
			flag=0;
                        fclose(f);
			break;
		}
         }
            if(flag==1)
	    {	system("cls");
		printf("Phone Number Not found in database");
                getch();
                fclose(f);
	    }
}
void modify1()    //For Admin
{
	FILE *f;
	char no[20];
	long int size=sizeof(s);
	if((f=fopen("ab.bin","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the client to modify:");
	scanf("%s",no);
	fflush(stdin);
	for(int i=0;i<n;i++)
	{
                fread(&s,sizeof(s),1,f);
		if(strcmp(s.no,no)==0)
		{
			system("cls");
			printf("\n Phone number being modified:%s",s.no);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter package type:");
			s.type=selectpack();
                        printf("\n Enter Talk-time minutes: ");
			scanf("%d",&s.min);
			if(s.type==1)
                             s.amt=pack1(s.min);
                       	if(s.type==2)
                             s.amt=pack2(s.min);
                       	if(s.type==3)
                             s.amt=pack3(s.min);
                        printf("\n New record modified and written!!");
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
                        getch();
			break;
		}
	}
	fclose(f);
}

void modify()    //For User
{
	FILE *f;
	char no[20];
	long int size=sizeof(s);
	if((f=fopen("ab.bin","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter your phone number:");
	scanf("%s",no);
	for(int i=0;i<n;i++)
	{
                fread(&s,sizeof(s),1,f);
		if(strcmp(s.no,no)==0)
		{
			system("cls");
			printf("\n Phone number being modified:%s",s.no);
			printf("\n Enter name: ");
                        fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter package type");
			s.type=selectpack();
			if(s.type==1)
                             s.amt=pack1(s.min);
                       	if(s.type==2)
                             s.amt=pack2(s.min);
                       	if(s.type==3)
                             s.amt=pack3(s.min);
                        printf("\n After modification:");
                        printf("\n\nPhone no: %s\nName: %s\nPack type: %d\nTalk-time: %dminutes\nAmount: Rs.%0.2f\n",s.no,s.name,s.type,s.min,s.amt);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
                        getch();
			break;
		}
	}
	fclose(f);
}


float pack1(int talktime)
{
float price=0;
if(talktime<=100)                         	price=200;
else if(talktime>100 &&talktime<=200)
{
price=200+(talktime-100)*0.5;
}
else if(talktime>200)
{
price=250+(talktime-200)*0.4;
}
return price;
}
 
float pack2(int talktime)
{
float price=0;
if(talktime<=300)                         	price=250;
else if(talktime>300 &&talktime<=500)
{
price=250+(talktime-300)*0.4;
}
else if(talktime>500)
{
price=320+(talktime-200)*0.3;
}
return price;
}
 
 
 
float pack3(int talktime)
{
float price=0;
if(talktime<=360)                         	price=talktime*0.5;
else if(talktime>360)
{
price=180+(talktime-360)*0.4;
}
return price;
}

int selectpack()
{
printf("\n The packs are based on talk time!!\n The packs are as follows:");
printf("\n Pack 1 \n Rs 200 for first 100 minutes \n Rs 0.5 for each minute for next 100 minutes\n Rs 0.4 for every minute afterwards\n");
printf("\n Pack 2 \n Rs 250 for first 300 minutes \n Rs 0.4 for each minute for next 200 minutes\n Rs 0.3 for every minute afterwards\n");
printf("\n Pack 3 For first 360 minutes- Rs 0.5 per minute\n Rs 0.4 for every following minute\n");
printf(" Select 1,2,3 accordingly: ");
int ch;  
scanf("%d",&ch);
return ch;
} 

