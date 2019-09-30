#include<windows.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<direct.h>                     //contains _dos_getdate
#include<time.h>

#define RETURNTIME 15

char categories[][15]={"Computer   ","Electronics","Electrical ","IT         "};
void returnfunc();
void mainmenu();
void addbooks();
void deletebooks();
void editbooks();
void searchbooks();
void issuebooks();
void viewbooks();
void closeapplication();
int  getdata();
int  checkid(int);
int t();
void Password();
void issuerecord();

//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;
//list of global variable
int s;
char findbook;
char password[10]={"codewithc"};

struct Date
{
int mm,dd,yy;
};
struct books
{
int id;
char stname[20];
char name[20];
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
int main()
{
Password();
getch();
return 0;
}
void mainmenu()
{
system("cls");
int i;
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
printf("\xDB\xDB\xDB\xDB\xB2 1. Add Books\n");
printf("\xDB\xDB\xDB\xDB\xB2 2. Delete books\n");
printf("\xDB\xDB\xDB\xDB\xB2 3. Search Books\n");
printf("\xDB\xDB\xDB\xDB\xB2 4. Issue Books\n");
printf("\xDB\xDB\xDB\xDB\xB2 5. View Book list\n");
printf("\xDB\xDB\xDB\xDB\xB2 6. Edit Book's Record\n");
printf("\xDB\xDB\xDB\xDB\xB2 7. Close Application\n");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
t();
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
system("cls");
printf("\tIntegrated Library System");
printf("******************************************");
printf("*******************************************");
printf("*******************************************");
printf("********************************************");
printf("Exiting in 3 second...........>");
Sleep(3000);
exit(0);
}
default:
{
printf("\aWrong Entry!!Please re-entered correct option");
mainmenu();
}

}
}
void addbooks(void)    //funtion that add books
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
mainmenu() ;
system("cls");
fp=fopen("Bibek.dat","ab+");
if(getdata()==1)
{
a.cat=categories[s-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
printf("The record is sucessfully saved");
printf("Save any more?(Y / N):");
if(getch()=='n')
mainmenu();
else
system("cls");
addbooks();
}
}
void deletebooks()    //function that delete items from file fp
{
system("cls");
int d;
char another='y';
while(another=='y')  //infinite loop
{
system("cls");
printf("Enter the Book ID to  delete:");
scanf("%d",&d);
fp=fopen("Bibek.dat","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
printf("The book record is available");
printf("Book name is %s",a.name);
printf("Rack No. is %d",a.rackno);
findbook='t';
}
}
if(findbook!='t')
{
printf("No record is found modify the search");
if(getch())
mainmenu();
}
if(findbook=='t' )
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
fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
}                              //we want to delete
}
fclose(ft);
fclose(fp);
remove("Bibek.dat");
rename("test.dat","Bibek.dat"); //copy all item from temporary file to fp except that
fp=fopen("Bibek.dat","rb+");    //we want to delete
if(findbook=='t')
{
  
printf("The record is sucessfully deleted");
printf("Delete another record?(Y/N)");
}
}
else
mainmenu();
fflush(stdin);
another=getch();
}
}
mainmenu();
}
void searchbooks()
{
system("cls");
int d;
printf("*****************************Search Books*********************************");
printf("\xDB\xDB\xDB\xB2 1. Search By ID");
printf("\xDB\xDB\xDB\xB2 2. Search By Name");
printf("Enter Your Choice");
fp=fopen("Bibek.dat","rb+"); //open file for reading propose
rewind(fp);   //move pointer at the begining of file
switch(getch())
{

case '1':
{
system("cls");
printf("****Search Books By Id****");
printf("Enter the book id:");
scanf("%d",&d);
printf("Searching........");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
Sleep(2);
printf("The Book is available");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\xB2 ID:%d",a.id);
printf("\xB2");
printf("\xB2 Name:%s",a.name);
printf("\xB2");
printf("\xB2 Author:%s ",a.Author);
printf("\xB2");
printf("\xB2 Qantity:%d ",a.quantity);
printf("\xB2");
printf("\xB2");
printf("\xB2 Price:Rs.%.2f",a.Price);
printf("\xB2");
printf("\xB2 Rack No:%d ",a.rackno);
printf("\xB2");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
findbook='t';
}

}
if(findbook!='t')  //checks whether conditiion enters inside loop or not
{
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\xB2");
printf("\xB2");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\aNo Record Found");
}
printf("Try another search?(Y/N)");
if(getch()=='y')
searchbooks();
else
mainmenu();
break;
}
case '2':
{
char s[15];
system("cls");
printf("****Search Books By Name****");
printf("Enter Book Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
{
printf("The Book is available");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\xB2 ID:%d",a.id);
printf("\xB2 Name:%s",a.name);
printf("\xB2 Author:%s",a.Author);
printf("\xB2 Qantity:%d",a.quantity);
printf("\xB2 Price:Rs.%.2f",a.Price);
printf("\xB2");
printf("\xB2 Rack No:%d ",a.rackno);
printf("\xB2");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
d++;
}

}
if(d==0)
{
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\xB2");
printf("\xB2");
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\aNo Record Found");
}
printf("Try another search?(Y/N)");
if(getch()=='y')
searchbooks();
else
mainmenu();
break;
}
default :
getch();
searchbooks();
}
fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
int t;

system("cls");
printf("********************************ISSUE SECTION**************************");
printf("\xDB\xDB\xDB\xDb\xB2 1. Issue a Book");
printf("\xDB\xDB\xDB\xDb\xB2 2. View Issued Book");
printf("\xDB\xDB\xDB\xDb\xB2 3. Search Issued Book");
printf("\xDB\xDB\xDB\xDb\xB2 4. Remove Issued Book");
printf("Enter a Choice:");
switch(getch())
{
case '1':  //issue book
{
system("cls");
int c=0;
char another='y';
while(another=='y')
{
system("cls");
printf("***Issue Book section***");
printf("Enter the Book Id:");
scanf("%d",&t);
fp=fopen("Bibek.dat","rb");
fs=fopen("Issue.dat","ab+");
if(checkid(t)==0) //issues those which are present in library
{
printf("The book record is available");
printf("There are %d unissued books in library ",a.quantity);
printf("The name of book is %s",a.name);
printf("Enter student name:");
scanf("%s",a.stname);
//struct dosdate_t d; //for current date
//_dos_getdate(&d);
//a.issued.dd=d.day;
//a.issued.mm=d.month;
//a.issued.yy=d.year;
printf("Issued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
printf("The BOOK of ID %d is issued",a.id);
a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
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
printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
fseek(fs,sizeof(a),SEEK_END);
fwrite(&a,sizeof(a),1,fs);
fclose(fs);
c=1;
}
if(c==0)
{
printf("No record found");
}
printf("Issue any more(Y/N):");
fflush(stdin);
another=getch();
fclose(fp);
}

break;
}
case '2':  //show issued book list
{
system("cls");
int j=4;
printf("*******************************Issued book list*******************************\n");
printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
fs=fopen("Issue.dat","rb");
while(fread(&a,sizeof(a),1,fs)==1)
{
printf("%s",a.stname);
printf("\t\t\t\t\t%s\t",a.id);
printf("%s\t",a.name);
printf("%d-%d-%d\t",a.issued.dd,a.issued.mm,a.issued.yy );
printf("%d-%d-%d\t",a.duedate.dd,a.duedate.mm,a.duedate.yy);
//struct dosdate_t d;
//_dos_getdate(&d);
//            printf("Current date=%d-%d-%d",d.day,d.month,d.year);
j++;

}
fclose(fs);
returnfunc();
}
break;
case '3':   //search issued books by id
{
system("cls");
printf("Enter Book ID:");
int p,c=0;
char another='y';
while(another=='y')
{

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
fflush(stdin);
fclose(fs);
if(c==0)
{
printf("No Record Found");
}
printf("Try Another Search?(Y/N)");
another=getch();
}
}
break;
case '4':  //remove issued books from list
{
system("cls");
int b;
FILE *fg;  //declaration of temporary file for delete
char another='y';
while(another=='y')
{
printf("Enter book id to remove:");
scanf("%d",&b);
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
printf("The issued book is removed from list");

}

}
if(findbook!='t')
{
printf("No Record Found");
}
}
printf("Delete any more?(Y/N)");
another=getch();
}
}
default:
printf("\aWrong Entry!!");
getch();
issuebooks();
break;
}
returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
int i=0,j;
system("cls");
printf("*********************************Book List************************************\n");
printf(" CATEGORY\tID\tBOOKNAME\t\t\t\tAUTHOR\t\tQTY\tPRICE\tRackNo\n ");
fp=fopen("Bibek.dat","rb");
while(fread(&a,sizeof(a),1,fp)==1)
{
printf("%s\t",a.cat);
printf("%d\t",a.id);
printf("%s\t\t\t\t",a.name);
printf("%s\t\t",a.Author);
printf("%d\t",a.quantity);
printf("%.2f\t",a.Price);
printf("%d\t",a.rackno);
printf("\n\n");
j++;
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
fp=fopen("Bibek.dat","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
printf("The book is availble");
printf("The Book ID:%d",a.id);
printf("Enter new name:");scanf("%s",a.name);
printf("Enter new Author:");scanf("%s",a.Author);
printf("Enter new quantity:");scanf("%d",&a.quantity);
printf("Enter new price:");scanf("%f",&a.Price);
printf("Enter new rackno:");scanf("%d",&a.rackno);
printf("The record is modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
 (15,9);
printf("No record found");
}
}
 (15,16);
printf("Modify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
returnfunc();
}
void returnfunc(void)
{
{
printf(" Press ENTER to return to main menu");
}
a:
if(getch()==13) //allow only use of enter
mainmenu();
else
goto a;
}
int getdata()
{
int t;
printf("Enter the Information Below:\n");
printf("Category:");
printf("%s",categories[s-1]);
printf("\nBook ID:");
scanf("%d",&t);
if(checkid(t) == 0)
{
printf("\aThe book id already exists\a");
getch();
mainmenu();
return 0;
}
a.id=t;
printf("Book Name:");
scanf("%s",a.name);
printf("Author:");
scanf("%s",a.Author);
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
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
void Password(void) //for password option
{

system("cls");
char d[25]="Password Protected";
char ch,pass[10];
int i=0,j;
for(j=0;j<20;j++)
{
Sleep(50);
printf("*");
}
for(j=0;j<20;j++)
{
Sleep(50);
printf("%c",d[j]);
}
for(j=0;j<20;j++)
{
Sleep(50);
printf("*");
}
printf("\n");
printf("Enter Password:");

while(ch!=13)
{
ch=getch();

if(ch!=13 && ch!=8)
{
putch('*');
pass[i] = ch;
i++;
}
}
pass[i] = '\0';
if(strcmp(pass,password)==0)
{
printf("\n");
printf("Password match\n");
printf("Press any key to countinue.....");
getch();
mainmenu();
}
else
{
printf("\n");
printf("\aWarning!! Incorrect Password");
getch();
Password();
}
}
void issuerecord()  //display issued book's information
{
system("cls");
printf("The Book has taken by Mr. %s",a.stname);
printf("Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
printf("Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
/*void loaderanim()
{
int loader;
system("cls");
printf("LOADING........");
printf("\n\n");
for(loader=1;loader<20;loader++)
{
Sleep(100);printf("%c",219);}
}*/
//End of program
