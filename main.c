/*
Assigned by:
shmuel shmueli 308458298
*/

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>                
#include<ctype.h>                  
#include<dos.h>                  
#include<time.h>

#define USERS_PATH "users.dat"
#define ITEMS_PATH "items.txt"
#define LOG_PATH "log.txt"
#define BUFFER_SIZE 1000

#define MAX_USER 1000
#define MAX_STR  99

FILE *fp, *ft, *fs;
COORD coord = { 0, 0 };

void getDateTime(int *day, int *month, int *year, int *hours, int *mins);
void delay(int j);
void first_menu(void);
void second_menu(void);
void third_menu(void);
void addbook(void);
void deletbook(void);
void viewbooks(void);
void viewusers(void);
void editbook(void);
void sort();
void searchbook();
void addbook(void);
void gotoxy(int x, int y);
int login();
void loadusers(struct users* item, FILE* data);
//void swap(books* xp, books* yp);

typedef struct books
{
	char Catalog_number[20];
	char name[20];
	char author[20];
	char price[20]; //%f
	char Publication_day[20];
	char Publication_month[20];
	char Publication_year[20];
	char Units_in_Stock[20];
	char Bestseller[20];
	int ID; // for sorting
}books;
typedef struct users
{
	char username[20];
	char password[20];
	char level[10];
	char fullname[100];
}users;

void registe_r() {
	FILE *log;
	log = fopen("users.dat", "a+");
	struct users I;
	printf("enter full name:");
	gets(I.fullname);
	gets(I.fullname);
	printf("enter username:");
	scanf("%s", I.username);
	printf("enter password:");
	scanf("%s", I.password);
	printf("enter level:");
	scanf("%s", I.level);
	fprintf(log, "\n%s\t%s\t%s\t%s", I.fullname, I.username, I.password, I.level);
	fclose(log);
	printf("\n\now login with username and password");
	printf("\npress any key to continue......");
	_getch();
	system("cls");
	login();
}

void loadusers(struct users* users, FILE* data) {
	int i, j = 0;
	char temp[100];
	if (feof(data))
		return;
	fgets(temp, 100, data);
	for (i = 0; temp[i] != '\0' && temp[i] != '\t'; i++)
		(users->fullname)[i] = temp[i];
	(users->fullname)[i] = '\0';
	for (i += 1; temp[i] != '\0' && temp[i] != '\t'; i++)
		(users->username)[j++] = temp[i];
	(users->username)[j] = '\0';
	j = 0;
	for (i += 1; temp[i] != '\0' &&temp[i] != '\t'; i++)
		(users->password)[j++] = temp[i];
	(users->password)[j] = '\0';
	j = 0;
	for (i += 1; temp[i] != '\0' && temp[i] != '\n'; i++)
		(users->level)[j++] = temp[i];
	(users->level)[j] = '\0';
}

void loadbooks(struct books* books, FILE* data) {
	int i, j = 0;
	char temp[100];
	if (feof(data)) {
		return(0);
	}
	else {
		fgets(temp, 100, data);
		for (i = 0; temp[i] != '\0' && temp[i] != '\t' /*&& temp[i]!= '\n'*/; i++)
			(books->Catalog_number)[i] = temp[i];
		(books->Catalog_number)[i] = '\0';
		for (i += 1; temp[i] != '\0' && temp[i] != '\t'; i++)
			(books->name)[j++] = temp[i];
		(books->name)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' &&temp[i] != '\t'; i++)
			(books->author)[j++] = temp[i];
		(books->author)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' &&temp[i] != '\t'; i++)
			(books->price)[j++] = temp[i];
		(books->price)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' &&temp[i] != '\t'; i++)
			(books->Publication_day)[j++] = temp[i];
		(books->Publication_day)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' &&temp[i] != '\t'; i++)
			(books->Publication_month)[j++] = temp[i];
		(books->Publication_month)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' &&temp[i] != '\t'; i++)
			(books->Publication_year)[j++] = temp[i];
		(books->Publication_year)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' && temp[i] != '\t'; i++)
			(books->Units_in_Stock)[j++] = temp[i];
		(books->Units_in_Stock)[j] = '\0';
		j = 0;
		for (i += 1; temp[i] != '\0' &&temp[i] != '\n'; i++)
			(books->Bestseller)[j++] = temp[i];
		(books->Bestseller)[j] = '\0';
		j = 0;
	}
}

int login() {
	char user1[20], password1[20];
	int i, j = 0, k, t, m, n, b;
	int day, month, year, hours, mins;
	getDateTime(&day, &month, &year, &hours, &mins);
	FILE *fr = fopen("log.txt", "a+");
	FILE *fi;
	struct users I;
	char level1[] = "1", level2[] = "2", level3[] = "3";
	fi = fopen("users.dat", "r");
	if (fi == NULL) {
		fclose(fi);
		fi = fopen("users.dat", "a+");
		fprintf(fi, "system manager\tadmin\tadmin\t3\n");
	}
	else {
		fseek(fi, 0, SEEK_SET);
		for (k = 0; k < 3; k++)
		{
			system("cls");
			printf("ENTER YOUR USER ID:\n");
			scanf("%s", user1);
			printf("ENTER YOUR PASSWORD:\n");
			scanf("%s", password1);
			fseek(fi, 0, SEEK_SET);
			for (i = 0; i<20; i++)
			{
				loadusers(&I, fi);
				if (strcmp(user1, I.username) == 0 && strcmp(password1, I.password) == 0)
				{
					m = (strcmp(I.level, level1));
					n = (strcmp(I.level, level2));
					b = (strcmp(I.level, level3));
					if (m == 0) {
						system("cls");
						fprintf(fr, "%s logged in. time:%02d/%02d/%d, %02d:%02d\n", I.fullname, day, month, year, hours, mins);
						printf("Succcesful login\npermission level 1\n");
						printf("Loading\n");
						for (j = 0; j <= 6; j++) {
							delay(100000000);
							printf(".");
						}
						first_menu();
					}
					if (n == 0)	{
						system("cls");
						fprintf(fr, "%s logged in. time:%02d/%02d/%d, %02d:%02d\n", I.fullname, day, month, year, hours, mins);
						printf("Succcesful login\npermission level 2\n");
						printf("Loading\n");
						for (j = 0; j <= 6; j++)
						{
							delay(100000000);
							printf(".");
						}
						second_menu();
					}
					if (b == 0) {
						system("cls");
						fprintf(fr, "%s logged in. time:%02d/%02d/%d, %02d:%02d\n", I.fullname, day, month, year, hours, mins);
						printf("Succcesful login\npermission level 3\n");
						system("PAUSE");
						printf("Loading\n");
						for (j = 0; j <= 6; j++)
						{
							delay(100000000);
							printf(".");
						}
						third_menu();
					}
				}
			}

			printf("username or password wrong - try again:-(\n");
			system("PAUSE");
		}
		system("cls");
		printf("username or password wrong 3 times.\nprogram break :-(\n");
		for (j = 0; j <= 6; j++) {
			delay(100000000);
			printf(".");
		}
		fclose(fi);
		exit(0);
	}
}

int main() {
	int cho;
	printf("Press '1' for log in to the system \nPress '2' for exit\n ");
	scanf("%d", &cho);
	if (cho == 1) {
		system("cls");
		login();
	}
	else if (cho == 2) {
		exit(0);
	}
}

void gotoxy(int x, int y) {
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void first_menu() {
	int choice;
	system("cls");
	gotoxy(20, 2);
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd STORE SYSTEM \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 3);
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd MAIN MENU \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 5); printf("1. Add New Book\n");
	gotoxy(20, 7); printf("2. Search Book\n");
	gotoxy(20, 9); printf("3. View Books\n");
	gotoxy(20, 11); printf("4. Close application\n");
	gotoxy(20, 13); printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 27);
	printf("Enter Your Choice: ");
	switch (_getch()) 	{
	case '1':
		system("cls");
		addbook();
		first_menu();
		break;
	case '2':
		system("cls");
		searchbook();
		first_menu();
		break;
	case '3':
		system("cls");
		viewbooks();
		system("PAUSE");
		first_menu();
		break;
	case '4':
		system("cls");
		gotoxy(16, 3);
		printf("\t STORE SYSTEM MANAGMENT\n");
		gotoxy(16, 5);
		printf("THANK YoU FOR USING MY PROGRAM");
		printf("\n\n*****************************************************************************\n");
		system("PAUSE");
		exit(0);
	default: {
		gotoxy(20, 22);
		printf("Wrong!!Correct Option");
		if (_getch())
		{
			first_menu();
		}
	}
	}
}

void second_menu() {
	int choice;
	system("cls");
	gotoxy(20, 2);
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd STORE SYSTEM \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 3);
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd MAIN MENU \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 5); printf("1. Add New Book\n");
	gotoxy(20, 7); printf("2. Delete Book\n");
	gotoxy(20, 9); printf("3. Search Book\n");
	gotoxy(20, 11); printf("4. View Books\n");
	gotoxy(20, 17); printf("5. Close application\n");
	gotoxy(20, 18); printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 23);
	printf("Enter Your Choice: ");
	switch (_getch())
	{
	case '1':
		system("cls");
		addbook();
		second_menu();
		break;
	case '2':
		system("cls");
		deletbook();
		second_menu();
		break;
	case '3':
		system("cls");
		searchbook();
		second_menu();
		break;
	case '4':
		system("cls");
		viewbooks();
		system("PAUSE");
		second_menu();
		break;
	case '5': 
		system("cls");
		gotoxy(16, 3);
		printf("\tSTORE Management System\n");
		gotoxy(16, 5);
		printf("THANK YoU FOR USING MY PROGRAM");
		printf("\n\n*****************************************************************************");
		exit(0);
	default: {
		gotoxy(20, 22); printf("Wrong!!Correct Option");
		if (_getch())
		{
			second_menu();
		}
	}
	}
}

void third_menu() {
	int choice;
	sort();
	system("cls");
	gotoxy(20, 2);
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd HELLO MANAGER \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 3);
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd MAIN MENU \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 5); printf("1. Add New Book\n");
	gotoxy(20, 7); printf("2. Delete Book\n");
	gotoxy(20, 9); printf("3. Search Book\n");
	gotoxy(20, 11); printf("4. View Books\n");
	gotoxy(20, 13); printf("5. A New User\n");
	gotoxy(20, 15); printf("6. Edit book info\n");
	gotoxy(20, 17); printf("7. view users\n");
	gotoxy(20, 18); printf("8. Close Application\n");
	gotoxy(20, 19); printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	gotoxy(20, 24);
	printf("Enter Your Choice: ");
	switch (_getch()) {
	case '1':
		system("cls");
		addbook();
		third_menu();
		break;
	case '2':
		system("cls");
		deletbook();
		third_menu();
		break;
	case '3':
		system("cls");
		searchbook();
		third_menu();
		break;
	case '4':
		system("cls");
		viewbooks();
		system("PAUSE");
		third_menu();
		break;
	case '5':
		system("cls");
		registe_r();
		third_menu();
		break;
	case'6':
		system("cls");
		editbook();
		third_menu();
		break;
	case'7':
		system("cls");
		viewusers();
		third_menu();
		break;
	case '8': 
		system("cls");
		printf("THANK YoU FOR USING MY PROGRAM");
		exit(0);
	default:
	{
		printf("Wrong!!Correct Option");
		if (_getch())
		{
			third_menu();
		}
	}
	}
}

void addbook(void) {
	system("cls");
	int day, month, year, hours, mins;
	getDateTime(&day, &month, &year, &hours, &mins);
	FILE *fr = fopen("log.txt", "a+");
	char price1[20];
	int m = 0;
	char temp[100], ar[10];
	struct books I;
	printf("\xcd\xcd\xcd\xcd Add book INFO \xcd\xcd\xcd\n");
	FILE *fp, *data;
	fp = fopen(ITEMS_PATH, "a+");
	if (fp == NULL)	{
		printf("Error in Opening file");
	}
	else	{
		gets(temp);
		fflush(stdin);
		printf("Catalog number:\n ");
		gets(I.Catalog_number);
		printf("Name of the book:\n ");
		gets(I.name);
		printf("Author's name: \n");
		gets(I.author);
		printf("Price: \n");
		scanf("%s", &price1);
		printf("Publication day:\n ");
		scanf("%s", I.Publication_day);
		printf("Publication month:\n ");
		scanf("%s", I.Publication_month);
		printf("Publication year: \n");
		scanf("%s", I.Publication_year);
		printf("Units in Stock: \n");
		scanf("%s", I.Units_in_Stock);
		printf("Bestseller?:(yes/no)\n ");
		scanf("%s", I.Bestseller);
		fprintf(fp, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", I.Catalog_number, I.name, I.author, price1, I.Publication_day, I.Publication_month, I.Publication_year, I.Units_in_Stock, I.Bestseller);
	}
	fclose(fp);
	fprintf(fr, "book name %s created. time:%02d/%02d/%d, %02d:%02d\n", I.name, day, month, year, hours, mins);
	printf("The book is sucessfully added");
	printf("Add another one y/n");
	scanf("%s", ar);
	if (strcmp(ar, "y") == 0)
		addbook();
	else	{
		fflush(stdin);
		sort();
		return(0);
	}
}

void deletbook() {
	system("cls");
	gotoxy(26, 2);
	printf("\xcd\xcd\xcd\xcd Delete a book  \xcd\xcd\xcd");
	int day, month, year, hours, mins;
	getDateTime(&day, &month, &year, &hours, &mins);
	FILE *fr = fopen("log.txt", "a+");
	int i, k, p, m = 0;
	char book[20], newname[] = "item.txt", co[] = "\n",yes[10];
	char tempo[100];
	char infinite = 'y';
	while (infinite == 'y')	{
		FILE *fp, *ft;
		system("cls");
		struct books I;
		gotoxy(26, 2);
		printf("\xcd\xcd\xcd\xcd Delete a book  \xcd\xcd\xcd");
		gotoxy(10, 5);
		printf("Enter the book number to  delete:\n");
		scanf("%s", book);
		fp = fopen("items.txt", "r+");
		rewind(fp); ///reposition file pointer to sream's beggining
		for (i = 0; i < 50; i++){
			loadbooks(&I, fp);
			if (strcmp(book, I.Catalog_number) == 0)	{
				printf("The details about the book are:\nCatalog number:%s\nName:%s\nAuthor:%s\nPrice:%s\nPublication date:%s.%s.%s\nUnits in Stock:%s\nBestseller:%s\n\n", I.Catalog_number, I.name, I.author, I.price, I.Publication_day, I.Publication_month, I.Publication_year, I.Units_in_Stock, I.Bestseller);
				printf("Do you want to delete it?(y/n)\n:");
				scanf("%s", yes);
				if (strcmp(yes,"y")==0)	{
					//fseek(fp, 0, SEEK_SET);
					rewind(fp);
					fprintf(fr, "book name %s deleted. time:%02d/%02d/%d, %02d:%02d\n", I.name, day, month, year, hours, mins);
					ft = fopen("hello.txt", "w+");  //temporary file for delete
					for (k = 0; k < 20; k++)		{
						if (feof(fp) != 1)			{
							loadbooks(&I, fp);
							if (strcmp(book, I.Catalog_number) != 0)				{
								if (m == 0)			{
									fprintf(ft, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", I.Catalog_number, I.name, I.author, I.price, I.Publication_day, I.Publication_month, I.Publication_year, I.Units_in_Stock, I.Bestseller); //write all in tempory file except that we want to delete
									m = 1;
								}
								else				{
									fprintf(ft, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", I.Catalog_number, I.name, I.author, I.price, I.Publication_day, I.Publication_month, I.Publication_year, I.Units_in_Stock, I.Bestseller); //write all in tempory file except that we want to delete
								}
							}
						}
					}
					fclose(ft);
					fclose(fp);
					remove("items.txt");
					p = rename("hello.txt", "items.txt");
					if (p == 0)				{
						if (fp = fopen("items.txt", "r+") != NULL)					{
							printf("The item is sucessfully deleted\n");
							sort();
							system("PAUSE");
							fflush(stdin);
							return(0);
						}
					}
				}
			}
		}
		printf("No book is found in LIST\n");
		printf("Search again?(Y/N)\n ");
		if (_getch() == 'y')		{
			deletbook();
		}
		else		{
			sort();
			fflush(stdin);
			return(0);
		}
		return(0);
	}
}

void searchbook() {
	system("cls");
	int s, i, p = 0, d, y, m, day1, year1, month1, k, x;
	float q, pricee;
	char temp[100], *day, *year, *month, *ptr,*prt,*price;
	int day2, month2, year2, hours2, mins2;
	getDateTime(&day2, &month2, &year2, &hours2, &mins2);
	FILE *fr = fopen("log.txt", "a+");
	struct books I;
	FILE *fp, *ft;
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd SEARCH BOOK \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("Enter 1 to search the book by his number\n");
	printf("Enter 2 to search the book by his name\n");
	printf("Enter 3 to search the book by his X< price:\n");
	printf("Enter 4 to search the book by his X< price:\n");
	printf("Enter 5 to search the book by his X> date publication date:\n");
	printf("Enter 6 to search the book by his X< date publication date:\n");
	printf("Enter 7 to search the book by Bestseller: (yes/no)\n");
	fp = fopen("items.txt", "r+");
	rewind(fp);
	gets(temp);
	switch (getch())	{
	case '1':
		printf("enter the book catalog number:\n");
		scanf("%s", temp);
		for (i = 0; i < 50; i++)	{
			loadbooks(&I, fp);
			if (feof(fp))	{
				printf("\n\n");
				fprintf(fr, "book ID %s has been searched. time:%02d/%02d/%d, %02d:%02d\n", I.Catalog_number, day2, month2, year2, hours2, mins2);
				printf("How many books there are =%d\n\n", p);
				system("PAUSE");
				return;
			}
			else if (strcmp(temp, I.Catalog_number) == 0)	{
				printf(" Catalog_number\t name\t author\t price\t Publication_date\t Units_in_Stock");
				printf("%s", I.Catalog_number);
				printf("\t%s", I.name);
				printf("\t%s", I.author);
				printf("\t%s", I.price);
				printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
				printf("\t\t%s", I.Units_in_Stock);
				printf("\t\t%s", I.Bestseller);
				printf("\n\n");
				p++;
				return(0);
			}
		}
		printf("book not found");
		printf("Search again?(Y/N)\n ");
		system("PAUSE");
		if (_getch() == 'y')	{
			searchbook();
		}
		break;
	case '2':
		printf("enter the book name:\n");
		scanf("%s", temp);
		for (i = 0; i < 50; i++)	{
			loadbooks(&I, fp);
			if (feof(fp))		{
				printf("\n\n");
				fprintf(fr, "book name %s has been searched. time:%02d/%02d/%d, %02d:%02d\n", I.name, day2, month2, year2, hours2, mins2);
				printf("How many books there are =%d\n\n", p);
				system("PAUSE");
				return;
			}
			else if (strcmp(temp, I.name) == 0)		{
				printf(" Catalog_number\t name\t author\t price\t Publication_date\t Units_in_Stock");
				printf("%s", I.Catalog_number);
				printf("\t%s", I.name);
				printf("\t%s", I.author);
				printf("\t%s", I.price);
				printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
				printf("\t\t%s", I.Units_in_Stock);
				printf("\t\t%s", I.Bestseller);
				printf("\n\n");
				p++;
				return(0);
			}
		}
		printf("book not found");
		printf("Search again?(Y/N)\n ");
		system("PAUSE");
		if (_getch() == 'y')		{
			searchbook();
		}
		break;
	case '3':
		printf("search the book by his X> price:\n");
		k = 0;
		printf("please enter the day X> price\n");
		scanf("%f", &pricee);
		printf("the number for x > price you choose is %f\n", pricee);
		printf(" ID\t name\t author\t price\t Publication date \t Units in Stock\t Bestseller \n\n");
		for (k = 0; k < 50; k++)		{
			loadbooks(&I, fp);
			q = strtod(I.price, &prt);
			if (feof(fp))
			{
				printf("\n\n");
				printf("How many books there are =%d\n\n", p);
				system("PAUSE");
				return;
			}
			else if (pricee > q)
			{
				printf("%s", I.Catalog_number);
				printf("\t%s", I.name);
				printf("\t%s", I.author);
				printf("\t%s", I.price);
				printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
				printf("\t\t%s", I.Units_in_Stock);
				printf("\t\t%s", I.Bestseller);
				printf("\n\n");
				p++;
			}
		}
		printf("book not found");
		printf("Search again?(Y/N)\n ");
		system("PAUSE");
		if (_getch() == 'y')
		{
			searchbook();
		}
		break;
	case '4':
		printf("search the book by his X< price:\n");
		k = 0;
		printf("please enter the day X< price\n");
		scanf("%f", &pricee);
		printf("the number for x < price you choose is %f\n", pricee);
		printf(" ID\t name\t author\t price\t Publication date \t Units in Stock\t Bestseller \n\n");
		for (k = 0; k < 50; k++)
		{
			loadbooks(&I, fp);
			q = strtod(I.price, &prt);
			if (feof(fp))
			{
				printf("\n\n");
				fprintf(fr, "search book by his price %s . time:%02d/%02d/%d, %02d:%02d\n", I.price, day2, month2, year2, hours2, mins2);
				printf("How many books there are =%d\n\n", p);
				system("PAUSE");
				return;
			}
			else if (pricee < q)
			{
				printf("%s", I.Catalog_number);
				printf("\t%s", I.name);
				printf("\t%s", I.author);
				printf("\t%s", I.price);
				printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
				printf("\t\t%s", I.Units_in_Stock);
				printf("\t\t%s", I.Bestseller);
				printf("\n\n");
				p++;
			}
		}
		printf("book not found");
		printf("Search again?(Y/N)\n ");
		system("PAUSE");
		if (_getch() == 'y')
		{
			searchbook();
		}		break;
	case '5':
			k = 0;
			printf("search book by his under date publication date:X>\n");
			printf("please enter the day X day:(dd)\n");
			scanf("%d", &day1);
			printf("please enter the month:(mm)\n");
			scanf("%d", &month1);
			printf("please enter the year:(yyyy)\n");
			scanf("%d", &year1);
			printf("the date for x > publication date you choose is %d.%d.%d\n", day1, month1, year1);
			printf(" ID\t name\t author\t price\t Publication date \t Units in Stock\t Bestseller \n\n");
			for (k = 0; k < 50; k++)
			{
				loadbooks(&I, fp);
				d = strtod(I.Publication_day, &day);
				m = strtod(I.Publication_month, &month);
				y = strtod(I.Publication_year, &year);
				if (feof(fp))
				{
					printf("\n\n");
					fprintf(fr, "search book by his P.D %s.%s.%s . time:%02d/%02d/%d, %02d:%02d\n", I.Publication_day,I.Publication_month,I.Publication_day, day2, month2, year2, hours2, mins2);
					printf("How many books there are =%d\n\n", p);
					system("PAUSE");
					return;
				}
				else if (year1 > y)
				{
					if (month1 > m)
					{
						if (day1 > d)
						{
							printf("%s", I.Catalog_number);
							printf("\t%s", I.name);
							printf("\t%s", I.author);
							printf("\t%s", I.price);
							printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
							printf("\t\t%s", I.Units_in_Stock);
							printf("\t\t%s", I.Bestseller);
							printf("\n\n");
							p++;
						}
						else
						{
							printf("%s", I.Catalog_number);
							printf("\t%s", I.name);
							printf("\t%s", I.author);
							printf("\t%s", I.price);
							printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
							printf("\t\t%s", I.Units_in_Stock);
							printf("\t\t%s", I.Bestseller);
							printf("\n\n");
							p++;
						}
					}
					else
					{
						printf("%s", I.Catalog_number);
						printf("\t%s", I.name);
						printf("\t%s", I.author);
						printf("\t%s", I.price);
						printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
						printf("\t\t%s", I.Units_in_Stock);
						printf("\t\t%s", I.Bestseller);
						printf("\n\n");
						p++;
					}
				}
			}
			printf("book not found");
			printf("Search again?(Y/N)\n ");
			system("PAUSE");
			if (_getch() == 'y')
			{
				searchbook();
			}
		break;
	case '6':
		k = 0;
		printf("search book by his under date publication date:X<\n");
		printf("please enter the day X day:(dd)\n");
		scanf("%d", &day1);
		printf("please enter the month:(mm)\n");
		scanf("%d", &month1);
		printf("please enter the year:(yyyy)\n");
		scanf("%d", &year1);
		printf("the date for x > publication date you choose is %d.%d.%d\n", day1, month1, year1);
		printf(" ID\t name\t author\t price\t Publication date \t Units in Stock\t Bestseller \n\n");
		for (k = 0; k < 50; k++)
		{
			loadbooks(&I, fp);
			d = strtod(I.Publication_day, &day);
			m = strtod(I.Publication_month, &month);
			y = strtod(I.Publication_year, &year);
			if (feof(fp))
			{
				printf("\n\n");
				printf("How many books there are =%d\n\n", p);
				system("PAUSE");
				return;
			}
			else if (year1 < y)
			{
				if (month1 < m)
				{
					if (day1 < d)
					{
						printf("%s", I.Catalog_number);
						printf("\t%s", I.name);
						printf("\t%s", I.author);
						printf("\t%s", I.price);
						printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
						printf("\t\t%s", I.Units_in_Stock);
						printf("\t\t%s", I.Bestseller);
						printf("\n\n");
						p++;
					}
					else
					{
						printf("%s", I.Catalog_number);
						printf("\t%s", I.name);
						printf("\t%s", I.author);
						printf("\t%s", I.price);
						printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
						printf("\t\t%s", I.Units_in_Stock);
						printf("\t\t%s", I.Bestseller);
						printf("\n\n");
						p++;
					}
				}
				else
				{
					printf("%s", I.Catalog_number);
					printf("\t%s", I.name);
					printf("\t%s", I.author);
					printf("\t%s", I.price);
					printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
					printf("\t\t%s", I.Units_in_Stock);
					printf("\t\t%s", I.Bestseller);
					printf("\n\n");
					p++;
				}
			}
		}
		printf("book not found");
		printf("Search again?(Y/N)\n ");
		system("PAUSE");
		if (_getch() == 'y')
		{
			searchbook();
		}
		break;
	case '7':
		printf("book best seller?(yes/no):\n");
		scanf("%s", temp);
		for (i = 0; i < 50; i++)
		{
			loadbooks(&I, fp);
			if (feof(fp))
			{
				printf("\n\n");
				printf("How many books there are =%d\n\n", p);
				system("PAUSE");
				return;
			}
			else if (strcmp(temp, I.Bestseller) == 0)
			{
				printf(" Catalog_number\t name\t author\t price\t Publication_date\t Units_in_Stock");
				printf("Catalog name:%s\n", I.Catalog_number);
				printf("Name of the book:%s\n", I.name);
				printf("Name of the author:%s\n", I.author);
				printf("Price:%s\n", I.price);
				printf("Publication date:%s.%s.%s\n", I.Publication_day, I.Publication_month, I.Publication_year);
				printf("Number of units in stock:%s\n", I.Units_in_Stock);
				printf("Bestseller:%s\n", I.Bestseller);
				printf("\n\n");
				system("PAUSE");
				return(0);
			}
		}
		printf("book not found\n");
		printf("Search again?(y/n)\n ");
		system("PAUSE");
		if (_getch() == 'y')
		{
			searchbook();
		}
	default:
	{
		gotoxy(20, 22);
		printf("Wrong!!Correct Option");
		if (_getch())
		{
			return(0);
		}
	}
	}
}

void viewbooks(void)
{
	system("cls");
	FILE *fp;
	int i = 1, j, k;
	float rprice, temp, ret;
	char temp1[100], temp2[100], *ptr;
	printf("\n\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd Books List \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf(" ID\t name\t author\t price\t Publication date \t Units in Stock\t Bestseller \n\n");
	struct books I;
	fp = fopen("items.txt", "r");
	for (k = 0; k < 50; k++)
	{
		if (feof(fp))
		{
			printf("\n\n");
			printf("How many books there are =%d\n\n", i - 1);
			return;
		}
		else
		{
			loadbooks(&I, fp);
			//rprice = strtod(I.price, &ptr);
			printf("%s", I.Catalog_number);
			printf("\t%s", I.name);
			printf("\t%s", I.author);
			printf("\t%s", I.price);
			printf("\t%s.%s.%s", I.Publication_day, I.Publication_month, I.Publication_year);
			printf("\t\t%s", I.Units_in_Stock);
			printf("\t\t%s", I.Bestseller);
			printf("\n\n");
			i = i + 1;
		}
	}
	fclose(fp);
	system("PAUSE");
	return(0);
}

void viewusers(void)
{
	system("cls");
	FILE *fp;
	int i = 0, j, k;
	printf("\n\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd Users List \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf(" username\t  password\t permission \t full name  \n\n");
	struct users I;
	fp = fopen("users.dat", "r");
	for (k = 0; k < 50; k++)
	{
		if (feof(fp))
		{
			printf("\n\n");
			printf("How many users there are =%d\n\n", i );
			system("PAUSE");
			return;
		}
		else
		{
			loadusers(&I, fp);
			printf("%s", I.username);
			printf("\t%s", I.password);
			printf("\t%s", I.level);
			printf("\t%s", I.fullname);
			printf("\n\n");
			i = i + 1;
		}
	}
	fclose(fp);
	system("PAUSE");
	return(0);
}

void editbook(void)
{
	system("cls");

	int day, month, year, hours, mins;
	getDateTime(&day, &month, &year, &hours, &mins);
	FILE *fr = fopen("log.txt", "a+");

	struct books I;
	int s, print = 37, k, i, m = 0, p;
	char newcat[20], newname[20], newauth[20], newprice[20], newd[20], newm[20], newy[20], newuis[20], newbs[20];
	char temp[100], te[100], buffer[1000];
	printf("\xcd\xcd\xcd\xcd\xcd\xcd Edit BOOK info \xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("Enter the BOOK number to edit:\n");
	FILE *fTemp, *ft;
	scanf("%s", temp);
	fp = fopen("items.txt", "r");
	rewind(fp); ///reposition file pointer to sream's beggining
	for (k = 0; k < 50; k++)
	{
		loadbooks(&I, fp);
		if (strcmp(I.Catalog_number, temp) == 0)
		{
			printf("Catalog_number: %s\n", I.Catalog_number);
			printf("name: %s\n", I.name);
			printf("author: %s\n", I.author);
			printf("price: %s\n", I.price);
			printf("Publication date: %s.%s.%s\n", I.Publication_day, I.Publication_month, I.Publication_year);
			printf("Units in Stock:%s\n", I.Units_in_Stock);
			printf("Bestseller: %s\n", I.Bestseller);
			printf("\n\n");
			printf("you want to overwrite it?(y/n)\n");
			/*gets(temp);*/
			if (_getch() == 'y')
			{
				printf("New Catalog number:\n ");
				scanf("%s", newcat);
				printf("New Name of the book:\n ");
				scanf("%s", newname);
				printf("New Author's name:\n ");
				scanf("%s", newauth);
				printf("New Price:\n ");
				scanf("%s", newprice);
				printf("New Publication day:\n ");
				scanf("%s", newd);
				printf("New Publication month:\n ");
				scanf("%s", newm);
				printf("New Publication year:\n ");
				scanf("%s", newy);
				printf("New Units in Stock: \n");
				scanf("%s", newuis);
				printf("Bestseller:(yes/no) \n");
				scanf("%s", newbs);
				rewind(fp);
				fprintf(fr, "book name %s has been changed. time:%02d/%02d/%d, %02d:%02d\n", I.name, day, month, year, hours, mins);
				ft = fopen("temp.txt", "w+");  //temporary file for replace
				for (k = 0; k < 30; k++)
				{
					if (feof(fp) != 1)
					{
						loadbooks(&I, fp);
						if (strcmp(temp, I.Catalog_number) == 0)
						{
							if (m == 0)
							{
								fprintf(ft, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", newcat, newname, newauth, newprice, newd, newm, newy, newuis, newbs);
								m = 1;
							}
							else
							{
								fprintf(ft, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", newcat, newname, newauth, newprice, newd, newm, newy, newuis, newbs);
							}
						}
						else
						{
							if (m == 0)
							{
								fprintf(ft, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", I.Catalog_number, I.name, I.author, I.price, I.Publication_day, I.Publication_month, I.Publication_year, I.Units_in_Stock, I.Bestseller); //write all in tempory file except that we want to delete
								m = 1;
							}
							else
							{
								fprintf(ft, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", I.Catalog_number, I.name, I.author, I.price, I.Publication_day, I.Publication_month, I.Publication_year, I.Units_in_Stock, I.Bestseller); //write all in tempory file except that we want to delete
							}
						}
					}
				}
				fclose(ft);
				fclose(fp);
				remove("items.txt");
				p = rename("temp.txt", "items.txt");
				if (p == 0)
				{
					if (fp = fopen("items.txt", "r+") != NULL)
					{
						printf("The item is sucessfully overwrited\n");
						sort();
						system("PAUSE");
						fflush(stdin);
						return(0);
					}
				}
				else
				{
					printf("something went wrong");
					system("PAUSE");
					return(0);
				}
			}
			else
			{
				return(0);
			}
		}
	}
	printf("\n\n");
	printf("No item is found in LIST\n");
	system("PAUSE");
	fclose(fp);
	return(0);
}

void delay(int j)
{
	int i, k;
	for (i = 0; i<j; i++)
		k = i;
}

void sort()
{
	int i, j, flag = 0,p=0,k,m,n;
	int swapped = 1;
	char *ptr;
	FILE *ft,*fp = fopen("items.txt", "r+");
	struct books I;
	books* arr = (books*)malloc(50 * sizeof(books));
	for (i = 0; i < 50 && !feof(fp); i++)
	{
		loadbooks(&I, fp);
		arr[i].ID = strtod(I.Catalog_number, &ptr);
		strcpy(arr[i].Catalog_number , I.Catalog_number);
		strcpy(arr[i].name , I.name);
		strcpy(arr[i].author , I.author);
		strcpy(arr[i].price , I.price);
		strcpy(arr[i].Publication_day , I.Publication_day);
		strcpy(arr[i].Publication_month , I.Publication_month);
		strcpy(arr[i].Publication_year , I.Publication_year);
		strcpy(arr[i].Units_in_Stock , I.Units_in_Stock);
		strcpy(arr[i].Bestseller , I.Bestseller);
		p++;
	}
	arr = (books*)realloc(arr, (i+1) * sizeof(books));
	for (k = 1; k < i; k++) {
		for (m = 0; m < i - k; m++) {
			if (arr[m].ID > arr[m + 1].ID)
			{
				books temp = arr[m];
				arr[m] = arr[m+1];
				arr[m + 1] = temp;
			}
		}
	}
	remove("items.txt");
	fclose(fp);
	ft = fopen("items.txt", "w+");


	for (j = 0; j < p; j++)
	{
		if (flag == 0)
		{
			fprintf(ft, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", arr[j].Catalog_number, arr[j].name, arr[j].author, arr[j].price, arr[j].Publication_day, arr[j].Publication_month, arr[j].Publication_year, arr[j].Units_in_Stock, arr[j].Bestseller); //write all in tempory file except that we want to delete
			flag = 1;
		}
		else
		{
			fprintf(ft, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", arr[j].Catalog_number, arr[j].name, arr[j].author, arr[j].price, arr[j].Publication_day, arr[j].Publication_month, arr[j].Publication_year, arr[j].Units_in_Stock, arr[j].Bestseller); //write all in tempory file except that we want to delete
		}
	}
	free(arr);
	fclose(ft);
	return(0);
}

void getDateTime(int *day, int *month, int *year, int *hours, int *mins)
{
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	*day = timeinfo.tm_mday;
	*month = timeinfo.tm_mon + 1;
	*year = timeinfo.tm_year + 1900;
	*hours = timeinfo.tm_hour;
	*mins = timeinfo.tm_min;
}

