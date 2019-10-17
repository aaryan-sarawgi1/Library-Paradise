#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>//contains strcmp(),strcpy(),strlen()
#include<time.h>

#define RETURNTIME 15

char categories[][15]={"Computer   ","Electronics","Electrical ","IT         "};
int time1();
void returnfunc();
void main();
void addbooks();
void deletebooks();
void editbooks();
void searchbooks();
void issuebooks();
void viewbooks();
void closeapplication();
int  getdata();
int  checkid(int);
void issuerecord();

//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;
//list of global variable
int s;
char findbook='d';

struct Date
{
	int mm,dd,yy;
};
struct books
{
	int id;
	char stname[20];
	char name[25];
	char Author[20];
	int quantity;
	float Price;
	int count;
	int rackno;
	char *cat;
	struct Date issued;
	struct Date duedate;
};
struct books a;
void main()
{
	system("cls");
	int i;
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("\xDB\xDB\xDB\xDB\xB2 1. Addition of  Books\n");
	printf("\xDB\xDB\xDB\xDB\xB2 2. Deletion of books\n");
	printf("\xDB\xDB\xDB\xDB\xB2 3. Searching Books\n");
	printf("\xDB\xDB\xDB\xDB\xB2 4. Issuing Books\n");
	printf("\xDB\xDB\xDB\xDB\xB2 5. View Book list\n");
	printf("\xDB\xDB\xDB\xDB\xB2 6. Edit Book's Record\n");
	printf("\xDB\xDB\xDB\xDB\xB2 7. Exit\n");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	time1();
	printf("Enter your choice:");
	switch(getch())
	{
		case '1':
		addbooks();
		break;
		case '2':
		deletebooks();
		break;
		case '3':
		searchbooks();
		break;
		case '4':
		issuebooks();
		break;
		case '5':
		viewbooks();
		break;
		case '6':
		editbooks();
		break;
		case '7':
		{
			int b=3;
			for(b=3;b>=1;b--)
			{
				system("cls");
				printf("\tIntegrated Library System\n");
				printf("Made by Aaryan , Amey , Chetan");
				printf("Exiting in %d.............",b);
				Sleep(1000);
			}
			exit(0);
		}
		default:
		{
			printf("\aWrong Entry!!Please re-entered correct option");
			main();
		}

	}
}
void addbooks()    //funtion that add books
{
	system("cls");
	int i;
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGORIES\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("\xDB\xDB\xDB\xDB\xB2 1. Computer\n");
	printf("\xDB\xDB\xDB\xDB\xB2 2. Electronics\n");
	printf("\xDB\xDB\xDB\xDB\xB2 3. Electrical\n");
	printf("\xDB\xDB\xDB\xDB\xB2 4. IT\n");
	printf("\xDB\xDB\xDB\xDB\xB2 5. Back to main menu\n");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("Enter your choice:\n");
	scanf("%d",&s);
	if(s==5)
		main() ;

	else if(s>0&&s<5)
	{
		system("cls");
		fp=fopen("Bookdata.dat","ab+");
		if(getdata()==1)
		{
			a.cat=categories[s-1];
			fseek(fp,0,SEEK_END);
			fwrite(&a,sizeof(a),1,fp);
			fclose(fp);
			printf("The record is sucessfully saved");
			printf("\nSave any more?(Y / N):");
			if(getch()=='n')
				main();
			else
				system("cls");
			addbooks();
		}
	}
	else
	{
		printf("\nInvalid Input\nPress any key to continue");
		getch();
		main();
	}
}

void deletebooks()
{
	findbook='d';
	system("cls");
	int d;
	char another='y';
	while(another=='y') 
	{
		system("cls");
		printf("Enter the Book ID to be delete:");
		scanf("%d",&d);
		fp=fopen("Bookdata.dat","rb+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(a.id==d)
			{
				printf("The book record is available\n");
				printf("Book name is %s\n",a.name);
				printf("Rack No. is %d\n",a.rackno);
				findbook='t';
			}
		}
		if(findbook=='d')
		{
			printf("\nNo record is found \n");
			printf("Returning to main.....");
			Sleep(3000);
			main();
		}
		else
		{
			printf("Do you want to delete it?(Y/N):");
			if(getch()=='y')
			{
				ft=fopen("test.dat","wb+");  //temporary file for delete
				rewind(fp);
				while(fread(&a,sizeof(a),1,fp)==1)
				{
					if(a.id!=d)
					{
						fseek(ft,0,SEEK_CUR);
						fwrite(&a,sizeof(a),1,ft); //write all in tempory file except deleted
					}
				}
				fclose(ft);
				fclose(fp);
				remove("Bookdata.dat");
				rename("test.dat","Bookdata.dat"); //copy all item from temporary file to fp except that
				//fp=fopen("Bookdata.dat","rb+");    //we want to delete
				printf("\nThe record is sucessfully deleted");
				printf("\nDelete another record?(Y/N)");
				if(getch()=='y')
					deletebooks();


				else
					main();
			}
		}
	}
}
void searchbooks()
{
	system("cls");
	int d;
	printf("*****************************Search Books*********************************\n");
	printf("\xDB\xDB\xDB\xB2 1. Search By ID\n");
	printf("\xDB\xDB\xDB\xB2 2. Search By Name\n");
	printf("Enter Your Choice\n");
	fp=fopen("Bookdata.dat","rb+"); 
	rewind(fp);
	switch(getch())
	{

		case '1':
		{
			system("cls");
            findbook='d';
			printf("****Search Books By Id****\n");
			printf("Enter the book id:\n");
			scanf("%d",&d);
			int i=0;
			printf("Searching");
			for(i=0;i<15;i++)
			{
				Sleep(45);
				printf(".");
			}
			printf("\n");
			while(fread(&a,sizeof(a),1,fp)==1)
			{
				if(a.id==d)
				{
					Sleep(2);
					printf("The Book is available\n");
					printf("ID:%d\n",a.id);
					printf("Name:%s\n",a.name);
					printf("Author:%s\n",a.Author);
					printf("Quantity:%d\n",a.quantity);
					printf("Price:Rs.%.2f\n",a.Price);
					printf("Rack No:%d\n ",a.rackno);
					findbook='t';
				}

			}
			if(findbook!='t')
	           printf("No Record Found\n");
			printf("\nTry another search?(Y/N)");
			if(getch()=='y')
				searchbooks();
			else
				main();
			break;
		}
		case '2':
		{
			char s[25];
			system("cls");
			printf("****Search Books By Name****\n");
			printf("Enter Book Name:");
			scanf("%s",s);
			int d=0;int i=0;
			printf("Searching");
			for(i=0;i<15;i++)
			{
				Sleep(45);
				printf(".");
			}
			while(fread(&a,sizeof(a),1,fp)==1)
			{
				if(strcmp(a.name,s)==0)
				{
					printf("\nThe Book is available\n");
					printf("ID:%d\n",a.id);
					printf("Name:%s\n",a.name);
					printf("Author:%s\n",a.Author);
					printf("Quantity:%d\n",a.quantity);
					printf("Price:Rs.%.2f\n",a.Price);
					printf("Rack No:%d\n ",a.rackno);
					d++;
				}

			}
			if(d==0)
				printf("\nNo Record Found\n");
			printf("\nTry another search?(Y/N)");
			if(getch()=='y')
				searchbooks();
			else
				main();
			break;
		}
		default:
		searchbooks();
	}
	fclose(fp);
}
void issuebooks()  //function that issue books from library
{
	int t;char another;

	system("cls");
	printf("********************************ISSUE SECTION**************************");
	printf("\n\xDB\xDB\xDB\xDb\xB2 1. Issue a Book");
	printf("\n\xDB\xDB\xDB\xDb\xB2 2. View Issued Book");
	printf("\n\xDB\xDB\xDB\xDb\xB2 3. Search Issued Book");
	printf("\n\xDB\xDB\xDB\xDb\xB2 4. Remove Issued Book");
	printf("\nEnter a Choice:");
	switch(getch())
	{
		case '1':  //issue book
		system("cls");
		int c=0;
		another='y';
		while(another=='y')
		{
			system("cls");
			printf("***Issue Book section***\n");
			printf("Enter the Book Id:");
			scanf("%d",&t);
			fp=fopen("Bookdata.dat","rb");
			fs=fopen("Issue.dat","ab+");
			if(checkid(t)==0)
			{
				printf("The book record is available\n");
				printf("There are %d unissued books in library\n",a.quantity);
				printf("The name of book is %s\n",a.name);
				printf("Enter student name:");
				scanf("%s",a.stname);
				time_t now; //for current datimte
				struct tm *local=localtime(&now);
				a.issued.dd=local->tm_mday;
				a.issued.mm=local->tm_mon;
				a.issued.yy=local->tm_year+1900;
				printf("Issued date=%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
				printf("The BOOK of ID %d is issued\n",a.id);
				a.duedate.dd=a.issued.dd+RETURNTIME;
				a.duedate.mm=a.issued.mm;
				a.duedate.yy=a.issued.yy;
				if(a.duedate.dd>30)
				{
					a.duedate.mm+=a.duedate.dd/30;
					a.duedate.dd-=30;

				}
				if(a.duedate.mm>12)
				{
					a.duedate.yy+=a.duedate.mm/12;
					a.duedate.mm-=12;

				}
				printf("To be return:%d-%d-%d\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);
				fseek(fs,sizeof(a),SEEK_END);
				fwrite(&a,sizeof(a),1,fs);
				fclose(fs);
				c=1;
			}
			if(c==0)
			{
				printf("No record found");
			}
			printf("\nIssue any more(Y/N):");
			fflush(stdin);
			another=getch();
		}
		break;
		case '2':  //show issued book list
		system("cls");
		printf("*******************************Issued book list*******************************\n");
		printf("STUDENT NAME\t\t CATEGORY    ID     BOOK NAME\t\t    ISSUED DATE       RETURN DATE\n");
		fs=fopen("Issue.dat","rb");
		while(fread(&a,sizeof(a),1,fs)==1)
		{
			printf("%-25s",a.stname);
			printf("%s ",a.cat);
			printf("%-7d",a.id);
			printf("%-25s",a.name);
			printf("%d-%d-%d\t      ",a.issued.dd,a.issued.mm,a.issued.yy );
			printf("%d-%d-%d\t",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			time_t now;
			struct tm *local=localtime(&now);
			printf("Current date=%d-%d-%d\n",local->tm_mday,local->tm_mon,local->tm_year+1900);
		}
		fclose(fs);
		returnfunc();
		break;

		case '3':   //search issued books by id
		system("cls");
		c=0;another='y';
		while(another=='y')
		{
			printf("Enter Book ID:");
			int p;
			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==p)
				{
					issuerecord();
					printf("Press any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
		    //fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				printf("No Record Found\n");
			}
			printf("Try Another Search?(Y/N)");
			another=getch();
		}
		break;
		case '4':  //remove issued books from list
		system("cls");
		int b;
		FILE *fg;  //declaration of temporary file for delete
		another='y';
		findbook='d';
		while(another=='y')
		{
			printf("Enter book id to remove:");
			scanf("%d",&b);
			findbook='d';
			fs=fopen("Issue.dat","rb+");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==b)
				{
					issuerecord();
					findbook='t';
				}
				if(findbook=='t')
				{
					printf("Do You Want to Remove it?(Y/N)");
					if(getch()=='y')
					{
						fg=fopen("record.dat","wb+");
						rewind(fs);
						while(fread(&a,sizeof(a),1,fs)==1)
						{
							if(a.id!=b)
							{
								fseek(fs,0,SEEK_CUR);
								fwrite(&a,sizeof(a),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						printf("\nThe issued book is removed from list");

					}

				}
				else
				{
					printf("No Record Found\n");
					break;
				}
			}
			printf("\nDelete any more?(Y/N)");
			another=getch();
		}
		break;
		default:
		printf("\nWrong Entry!!\n");
		getch();
		issuebooks();
	}
	returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
	int i=0,j;
	system("cls");
	printf("*********************************Book List************************************\n");
	printf("CATEGORY    ID    BOOKNAME\t\t  AUTHOR\t\t   QTY\tPRICE\t RackNo\n");
	fp=fopen("Bookdata.dat","rb");
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		printf("%s ",a.cat);
		printf("%-6d",a.id);
		printf("%-24s",a.name);
		printf("%-25s",a.Author);
		printf("%-5d",a.quantity);
		printf("%-9.2f",a.Price);
		printf("%-2d",a.rackno);
		printf("\n");
		i=i+a.quantity;
	}
	printf("Total Books =%d",i);
	fclose(fp);
	returnfunc();
}
void editbooks(void)  //edit information about book
{
	system("cls");
	int c=0;
	int d,e;
	printf("****Edit Books Section****");
	char another='y';
	while(another=='y')
	{
		system("cls");
		printf("Enter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("Bookdata.dat","rb+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("The book is available\n");
				printf("The Book ID:%d",a.id);
				printf("\nEnter new name:");scanf("%s",a.name);
				printf("\nEnter new Author:");scanf("%s",a.Author);
				printf("\nEnter new quantity:");scanf("%d",&a.quantity);
				printf("\nEnter new price:");scanf("%f",&a.Price);
				printf("\nEnter new rackno:");scanf("%d",&a.rackno);
				printf("The record is modified\n");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
				printf("\nNo record found");
		}
		printf("Modify another Record?(Y/N)");
		//fflush(stdin);
		another=getch() ;
	}
	returnfunc();
}
void returnfunc(void)
{
	printf("\nPress ENTER to return to main menu");
	while(1)
	{
		if(getch()==13)
		{
			main();
			break;
		}
	}
}
int getdata()
{
	int t;char name[50];char author[30];
	printf("Enter the Information Below:\n");
	printf("Category:");
	printf("%s",categories[s-1]);
	printf("\nBook ID:");
	scanf("%d",&t);
	if(t>10000||t<0||checkid(t) == 0)
	{
		printf("\aThe book id already exists or invalid book id\nPress any key to continue");
		getch();
		main();
		return 0;
	}
	a.id=t;
	printf("\nBook Name:");
	scanf("%s",&a.name);
	if(strlen(name)>25)
	{
		printf("\aThe book name is too long \nPress any key to continue");
		getch();
		main();
		return 0;
	}
	printf("Author:");
	scanf("%s",&a.Author);
	if(strlen(author)>20)
	{
		printf("\aThe author name is too long \nPress any key to continue");
		getch();
		main();
		return 0;
	}

	printf("Quantity:");
	scanf("%d",&a.quantity);
	printf("Price:");
	scanf("%f",&a.Price);
	printf("Rack No:");
	scanf("%d",&a.rackno);
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
		if(a.id==t)
       return 0;  //returns 0 if book exists
return 1; //return 1 if it not
}
int time1() //for time
{
	time_t t;
	time(&t);
	printf("Date and time:%s\n",ctime(&t));

	return 0 ;
}


void issuerecord() 
{
	system("cls");
	printf("The Book was taken by Mr. %s\n",a.stname);
	printf("Issued Date:%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
	printf("Returning Date:%d-%d-%d\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
