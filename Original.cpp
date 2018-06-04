#include<stdio.h>
#include<string>
#include<conio.h>
#include<windows.h>

using namespace std;
void adminpassword();
void userpassword();
void gotoxy(int x, int y);
void menu();
void adminmode();
void usermode();
int out = 0, out2 = 0;
void patadd();
void patview();
void patedit();
void patsearch();
void patdel();
void prescription();
///////////
char yesno = 'y';
FILE *fp;
long int recsize;
int flag = 0;

struct patient
{
	char name[50], ic[50];
	char gender[10], age[20];
	char id[50];
};
struct patient list;
////////////
void appadd();
void appview();
void appdel();
void appsearch();
void appedit();
FILE *fa;
int ID;
struct appointment
{
	char patid[10], appid[10], docid[10];
	char appdate[10], disease[999];
	char description[999];
	char nextappdate[10];
};

struct appointment idlist;
long int recsize2;
//delete
FILE *ft, *ft2;
char confirm[50], confirm2[50];
char delconf = 'y';

// Admin case 6,7
int row = 3;
// Admin case 8 & 9

//Search
char filename[15];

int choice = 0;
char str[499];
//password
char input[30], input2[30];
string adminpass = "notsimple\r";
string userpass = "simple\r";
int pass;
int i = 0, j = 0;


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void main()
{

	fp = fopen("patient.txt", "rb+");

	if (fp == NULL)
	{
		fp = fopen("patient.txt", "wb+");
		if (fp == NULL)
		{
			puts("File error...");
			perror("Error");
			printf("\n"); printf("Please press any key to continue...");
			getch();
			exit(1);
		}
	}
	fa = fopen("appointment.txt", "rb+");
	if (fa == NULL)
	{
		fa = fopen("appointment.txt", "wb+");
		if (fa == NULL)
		{
			puts("File error...");
			perror("Error");
			printf("\n"); printf("Please press any key to continue...");
			getch();
			exit(1);
		}
	}
	recsize = sizeof(list);
	recsize2 = sizeof(idlist);
	while (1)
	{
		menu();
	}
}

void patadd()
{
	fseek(stdin, 0, SEEK_END);
	fseek(fp, 0, SEEK_END);
	while (yesno == 'y' || yesno == 'Y')
	{
		gotoxy(20, 5);  printf("****************************************");
		gotoxy(20, 6);  printf("*         Add Patients Details         *");
		gotoxy(20, 7);  printf("****************************************");
		gotoxy(20, 8);  printf("* ID          :                        *");
		gotoxy(20, 9);  printf("* Name        :                        *");
		gotoxy(20, 10); printf("* IC          :                        *");
		gotoxy(20, 11); printf("* Gender      :                        *");
		gotoxy(20, 12); printf("* Age         :                        *");
		gotoxy(20, 13); printf("*                                      *");
		gotoxy(20, 14); printf("*Do you wish to add new record?(y/n):  *");
		gotoxy(20, 15); printf("****************************************");
		gotoxy(36, 8);  scanf(" %[^\n]%*c", &list.id);
		gotoxy(36, 9);  scanf(" %[^\n]%*c", &list.name);
		gotoxy(36, 10); scanf(" %[^\n]%*c", &list.ic);
		gotoxy(36, 11); scanf(" %[^\n]%*c", &list.gender);
		gotoxy(36, 12); scanf(" %[^\n]%*c", &list.age);
		fwrite(&list, recsize, 1, fp);
		fflush(stdin);
		//fseek(stdin, 0, SEEK_END);
		gotoxy(57, 14); scanf("%s", &yesno);
	}
	gotoxy(20, 16); printf("Please press any key to continue...");
	getch();
	system("CLS");
}

void patview()
{
	fseek(stdin, 0, SEEK_END);
	row = 6;
	rewind(fp);

	printf("================================================================================");
	printf("                               Patients Details                                 ");
	printf("================================================================================");
	printf(" ID        Name                IC                  Gender         Age\n");
	printf("================================================================================");

	while (fread(&list, recsize, 1, fp) == 1)
	{
		gotoxy(1, row); printf("%s", list.id);
		gotoxy(11, row); printf("%s", list.name);
		gotoxy(31, row); printf("%s", list.ic);
		gotoxy(51, row); printf("%s", list.gender);
		gotoxy(66, row); printf("%s", list.age);
		row++;
	}
	gotoxy(1, row = row + 5); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void patedit() //edit part not finish
{
	fseek(stdin, 0, SEEK_END);
	flag = 0;
	gotoxy(20, 8);  printf("Enter Patient ID: "); scanf(" %s", &confirm);
	system("CLS");
	rewind(fp);
	while (fread(&list, recsize, 1, fp) == 1)
	{
		if (strcmp(list.id, confirm) != 0)
		{

		}
		else
		{
			flag = 1;
			gotoxy(20, 5);  printf("****************************************");
			gotoxy(20, 6);  printf("*         Edit Patients Details        *");
			gotoxy(20, 7);  printf("****************************************");
			gotoxy(20, 8);  printf("* 1. ID          :                     *");
			gotoxy(20, 9);  printf("* 2. Name        :                     *");
			gotoxy(20, 10); printf("* 3. IC          :                     *");
			gotoxy(20, 11); printf("* 4. Gender      :                     *");
			gotoxy(20, 12); printf("* 5. Age         :                     *");
			gotoxy(20, 13); printf("*                                      *");
			gotoxy(20, 14); printf("* 6. Edit All                          *");
			gotoxy(20, 15); printf("****************************************");
			gotoxy(38, 8);  printf("%s", list.id);
			gotoxy(38, 9);  printf("%s", list.name);
			gotoxy(38, 10); printf("%s", list.ic);
			gotoxy(38, 11); printf("%s", list.gender);
			gotoxy(38, 12); printf("%s", list.age);
			if (flag == 0)
			{

			}
			else
			{
				gotoxy(22, 16); printf("Choose the number to edit: ");
				gotoxy(50, 16); scanf("%d", &choice);
				system("CLS");
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7)
				{
					switch (choice)
					{
					case 1:
					{
						ft = fopen("temp.dat", "wb+");
						rewind(fp);
						while (fread(&list, recsize, 1, fp) == 1)
						{
							if (strcmp(list.id, confirm) != 0)
							{
								fwrite(&list, recsize, 1, ft);
							}
							else
							{
								gotoxy(20, 8); printf("Enter the ID: "); scanf(" %[^\n]%*c", &list.id);
								strcpy(list.name, list.name);
								strcpy(list.ic, list.ic);
								strcpy(list.gender, list.gender);
								strcpy(list.age, list.age);
								fwrite(&list, recsize, 1, ft);
							}
						}

						fclose(fp);
						fclose(ft);
						remove("patient.txt");
						rename("temp.dat", "patient.txt");
						fp = fopen("patient.txt", "rb+");
						fflush(stdin);
						system("CLS");
						break;
					}
					case 2:
					{
						ft = fopen("temp.dat", "wb+");
						rewind(fp);
						while (fread(&list, recsize, 1, fp) == 1)
						{
							if (strcmp(list.id, confirm) != 0)
							{
								fwrite(&list, recsize, 1, ft);
							}
							else
							{
								gotoxy(20, 8); printf("Enter the name: "); scanf(" %[^\n]%*c", &list.name);
								strcpy(list.id, list.id);
								strcpy(list.ic, list.ic);
								strcpy(list.gender, list.gender);
								strcpy(list.age, list.age);
								fwrite(&list, recsize, 1, ft);
							}
						}

						fclose(fp);
						fclose(ft);
						remove("patient.txt");
						rename("temp.dat", "patient.txt");
						fp = fopen("patient.txt", "rb+");
						fflush(stdin);
						system("CLS");
						break;
					}
					case 3:
					{
						ft = fopen("temp.dat", "wb+");
						rewind(fp);
						while (fread(&list, recsize, 1, fp) == 1)
						{
							if (strcmp(list.id, confirm) != 0)
							{
								fwrite(&list, recsize, 1, ft);
							}
							else
							{
								gotoxy(20, 8); printf("Enter the IC: "); scanf(" %[^\n]%*c", &list.ic);
								strcpy(list.id, list.id);
								strcpy(list.name, list.name);
								strcpy(list.gender, list.gender);
								strcpy(list.age, list.age);
								fwrite(&list, recsize, 1, ft);
							}
						}

						fclose(fp);
						fclose(ft);
						remove("patient.txt");
						rename("temp.dat", "patient.txt");
						fp = fopen("patient.txt", "rb+");
						fflush(stdin);
						system("CLS");
						break;
					}
					case 4:
					{
						ft = fopen("temp.dat", "wb+");
						rewind(fp);
						while (fread(&list, recsize, 1, fp) == 1)
						{
							if (strcmp(list.id, confirm) != 0)
							{
								fwrite(&list, recsize, 1, ft);
							}
							else
							{
								gotoxy(20, 8); printf("Enter the gender: "); scanf(" %[^\n]%*c", &list.gender);
								strcpy(list.id, list.id);
								strcpy(list.name, list.name);
								strcpy(list.ic, list.ic);
								strcpy(list.age, list.age);
								fwrite(&list, recsize, 1, ft);
							}
						}

						fclose(fp);
						fclose(ft);
						remove("patient.txt");
						rename("temp.dat", "patient.txt");
						fp = fopen("patient.txt", "rb+");
						fflush(stdin);
						system("CLS");
						break;
					}
					case 5:
					{
						ft = fopen("temp.dat", "wb+");
						rewind(fp);
						while (fread(&list, recsize, 1, fp) == 1)
						{
							if (strcmp(list.id, confirm) != 0)
							{
								fwrite(&list, recsize, 1, ft);
							}
							else
							{
								gotoxy(20, 8); printf("Enter the age: "); scanf(" %[^\n]%*c", &list.age);
								strcpy(list.id, list.id);
								strcpy(list.name, list.name);
								strcpy(list.ic, list.ic);
								strcpy(list.gender, list.gender);
								fwrite(&list, recsize, 1, ft);
							}
						}

						fclose(fp);
						fclose(ft);
						remove("patient.txt");
						rename("temp.dat", "patient.txt");
						fp = fopen("patient.txt", "rb+");
						fflush(stdin);
						system("CLS");
						break;
					}
					case 6:
					{
						gotoxy(20, 5);  printf("****************************************");
						gotoxy(20, 6);  printf("*         Edit Patients Details        *");
						gotoxy(20, 7);  printf("****************************************");
						gotoxy(20, 8);  printf("* 1. ID          :                     *");
						gotoxy(20, 9);  printf("* 2. Name        :                     *");
						gotoxy(20, 10); printf("* 3. IC          :                     *");
						gotoxy(20, 11); printf("* 4. Gender      :                     *");
						gotoxy(20, 12); printf("* 5. Age         :                     *");
						gotoxy(20, 13); printf("*                                      *");
						gotoxy(20, 14); printf("* 6. Edit All                          *");
						gotoxy(20, 15); printf("****************************************");
						gotoxy(38, 8);  scanf(" %[^\n]%*c", &list.id);
						gotoxy(38, 9);  scanf(" %[^\n]%*c", &list.name);
						gotoxy(38, 10); scanf(" %[^\n]%*c", &list.ic);
						gotoxy(38, 11); scanf(" %[^\n]%*c", &list.gender);
						gotoxy(38, 12); scanf(" %[^\n]%*c", &list.age);
						fseek(fp, -recsize, SEEK_CUR);
						fwrite(&list, recsize, 1, fp);
						fflush(stdin);
						break;

					}


					default:
					{
						printf("Invalid choice. Please try again.");
						printf("\n"); printf("Please press any key to continue..."); getch();
						system("CLS");
						break;
					}
					}
				}
				else
				{
					printf("Invalid choice. Please try again.");
					printf("\n"); printf("Please press any key to continue..."); getch();
				}
			}
			break;
		}
	}
	if (flag == 0)
	{
		gotoxy(20, 8); printf("Patient not exist!!");
	}

	gotoxy(20, 16); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void patdel()
{
	fseek(stdin, 0, SEEK_END);
	flag = 0;
	while (delconf == 'y' || delconf == 'Y')
	{
		gotoxy(20, 8);  printf("Enter Patient ID: "); scanf(" %s", &confirm);
		system("CLS");
		ft = fopen("temp.dat", "wb+");
		rewind(fp);
		while (fread(&list, recsize, 1, fp) == 1)
		{
			if (strcmp(list.id, confirm) != 0)
			{
				fwrite(&list, recsize, 1, ft);
			}
			else
			{
				flag = 1;
				gotoxy(20, 5);  printf("****************************************");
				gotoxy(20, 6);  printf("*       Delete Patients Details        *");
				gotoxy(20, 7);  printf("****************************************");
				gotoxy(20, 8);  printf("* 1. ID          :                     *");
				gotoxy(20, 9);  printf("* 1. Name        :                     *");
				gotoxy(20, 10); printf("* 2. IC          :                     *");
				gotoxy(20, 11); printf("* 3. Gender      :                     *");
				gotoxy(20, 12); printf("* 4. Age         :                     *");
				gotoxy(20, 13); printf("*                                      *");
				gotoxy(20, 14); printf("*                                      *");
				gotoxy(20, 15); printf("****************************************");
				gotoxy(38, 8);  printf("%s", list.id);
				gotoxy(38, 9);  printf("%s", list.name);
				gotoxy(38, 10);  printf("%s", list.ic);
				gotoxy(38, 11); printf("%s", list.gender);
				gotoxy(38, 12); printf("%s", list.age);
				gotoxy(20, 16); printf("Is this the details you wished to delete(y/n)?");
				gotoxy(67, 16); scanf("%s", &delconf);
				if (delconf == 'y' || delconf == 'Y')
				{
					/*	ft2 = fopen("temp2.dat", "wb+");
					rewind(fp);
					while (fread(&list, recsize, 1, fp) == 1)
					if (strcmp(list.id, comfirm) != 0)
					{
					fwrite(&list, recsize, 1, ft2);
					}
					fclose(fp);
					fclose(ft2);
					ft2 = fopen("temp2.dat", "rb+");
					while (ft2 != NULL)
					{

					remove("temp.dat");
					rename("temp2.dat", "temp.dat");
					ft = fopen("temp.dat", "rb+");
					fflush(stdin);
					ft2 = fopen("temp2.dat", "rb+");
					}*/

				}
				else
				{
					fwrite(&list, recsize, 1, ft);
				}
			}
		}
		if (flag == 0)
		{
			gotoxy(20, 16); printf("Patient ID invalid. Please try again.");
			fclose(ft);
			remove("temp.dat");
			gotoxy(20, 17); printf("Please press any key to continue..."); getch();
			system("CLS");
		}
		else
		{
			fclose(fp);
			fclose(ft);
			remove("patient.txt");
			rename("temp.dat", "patient.txt");
			fp = fopen("patient.txt", "rb+");
		}
		fseek(stdin, 0, SEEK_END);
		gotoxy(20, 17); printf("Delete other patient details(y/n)?");
		gotoxy(55, 17); scanf("%s", &delconf);
		system("CLS");
	}
}

void patsearch()
{
	fseek(stdin, 0, SEEK_END);
	flag = 0;

	while (delconf == 'y' || delconf == 'Y')
	{
		system("CLS");
		gotoxy(20, 8);  printf("Enter Patient ID: "); scanf(" %s", &confirm);
		system("CLS");
		rewind(fp);
		while (fread(&list, recsize, 1, fp) == 1)
		{
			if (strcmp(list.id, confirm) != 0)
			{

			}
			else
			{
				flag = 1;
				gotoxy(20, 5);  printf("****************************************");
				gotoxy(20, 6);  printf("*            Search Result             *");
				gotoxy(20, 7);  printf("****************************************");
				gotoxy(20, 8);  printf("* 1. ID          :                     *");
				gotoxy(20, 9);  printf("* 2. Name        :                     *");
				gotoxy(20, 10); printf("* 3. IC          :                     *");
				gotoxy(20, 11); printf("* 4. Gender      :                     *");
				gotoxy(20, 12); printf("* 5. Age         :                     *");
				gotoxy(20, 13); printf("*                                      *");
				gotoxy(20, 14); printf("****************************************");
				gotoxy(38, 8);  printf("%s", list.id);
				gotoxy(38, 9);  printf("%s", list.name);
				gotoxy(38, 10); printf("%s", list.ic);
				gotoxy(38, 11); printf("%s", list.gender);
				gotoxy(38, 12); printf("%s", list.age);

			}
		}
		if (flag == 0)
		{
			gotoxy(20, 9);  printf("Patient ID invalid. Please try again.");
			gotoxy(20, 10); printf("Search other patient details(y/n)?"); scanf(" %s", &delconf);
		}
		else
		{
			gotoxy(20, 15); printf("Search other patient details(y/n)?"); scanf(" %s", &delconf);
		}
	}
	gotoxy(20, 16); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void appadd()
{
	fseek(stdin, 0, SEEK_END);
	yesno = 'y';
	while (yesno == 'y' || yesno == 'Y')
	{
		yesno == 'y';
		printf("================================================================================");
		printf("                          Adding Appointment Details                            ");
		printf("================================================================================");
		gotoxy(20, 8); printf("Enter Patients ID: "); scanf("%s", &confirm);
		rewind(fp);
		while (fread(&list, recsize, 1, fp) == 1)
		{
			if (strcmp(list.id, confirm) != 0)
			{

			}
			else
			{
				flag = 1;
			}
		}

		if (flag == 1)
		{
			while (yesno == 'y' || yesno == 'Y')
			{
				system("CLS");
				fseek(fa, 0, SEEK_END);
				fseek(stdin, 0, SEEK_END);
				printf("================================================================================");
				printf("                          Adding Appointment Details                            ");
				printf("================================================================================");
				printf("Appointment ID: "); scanf(" %[^\n]%*c", &idlist.appid);
				printf("Date: "); scanf(" %[^\n]%*c", &idlist.appdate);
				printf("Doctor ID: "); scanf(" %[^\n]%*c", &idlist.docid);
				printf("\nDisease: ");  scanf(" %[^\n]%*c", &idlist.disease);
				printf("\nDescription: "); scanf(" %[^\n]%*c", &idlist.description);
				strcpy(idlist.patid, confirm);
				//gotoxy(10, 1);  
				//gotoxy(10, 2); 
				fwrite(&idlist, recsize2, 1, fa);
				fflush(stdin);
				printf("\n\n\n"); printf("Do you wish to add new record for this patient(y/n)? ");
				scanf("%s", &yesno);
			}
		}
		else
		{
			system("CLS");
			printf("Patient not exist. Please try again.");
		}

		printf("\n\n"); printf("Do you wish to add new record for another patient(y/n)? ");
		scanf("%s", &yesno);
		system("CLS");
	}
	gotoxy(20, 8); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void appview()  //no loop for checking others file
{
	yesno = 'y';
	fseek(stdin, 0, SEEK_END);
	while (yesno == 'y' || yesno == 'Y')
	{
		yesno = 'y';
		flag = 0;
		fseek(stdin, 0, SEEK_END);
		rewind(fa);
		system("CLS");
		printf("================================================================================"); printf("\n");
		printf("                                Viewing Records                                 "); printf("\n");
		printf("================================================================================"); printf("\n");
		gotoxy(20, 8); printf("Enter Patients ID: "); scanf("%s.txt", &confirm);
		system("CLS");
		printf("================================================================================"); printf("\n");
		printf("                              Appointment Records                               "); printf("\n");
		printf("================================================================================"); printf("\n");
		while (fread(&idlist, recsize2, 1, fa) == 1)
		{
			if (strcmp(idlist.patid, confirm) != 0)
			{

			}
			else
			{
				flag = 1;
				printf("Appointment ID: %s", idlist.appid); printf("\n");
				printf("Date: %s", idlist.appdate); printf("\n");
				printf("Doctor ID: %s", idlist.docid); printf("\n");
				printf("Disease: %s", idlist.disease); printf("\n\n");
				printf("Description: %s",idlist.description); printf("\n\n");
			}
		}
		if (flag == 0)
		{
			printf("Record for this patient is not exist. Please try again."); printf("\n");
			printf("Please press any key to continue..."); getch();
			system("CLS");
		}
		printf("\n"); printf("Do you wish to view others patients records(y/n)? "); scanf("%s", &yesno);
	}
	printf("\n\n\n"); printf("Please press any key to continue..."); getch();
	system("CLS"); 
}

void appedit()
{
	delconf = 'y';
	fseek(stdin, 0, SEEK_END);
	while (delconf == 'y' || delconf == 'Y')
	{
		system("CLS");
		flag = 0;
		printf("================================================================================"); printf("\n");
		printf("                                Editing Records                                 "); printf("\n");
		printf("================================================================================"); printf("\n");
		gotoxy(20, 8); printf("Enter Patients ID: "); scanf("%s.txt", &confirm);
		system("CLS");
		printf("================================================================================"); printf("\n");
		printf("                                Editing Records                                 "); printf("\n");
		printf("================================================================================"); printf("\n");
		rewind(fa);
		while (fread(&idlist, recsize2, 1, fa) == 1)
		{
			if (strcmp(idlist.patid, confirm) != 0)
			{

			}
			else
			{
				flag = 1;
				printf("Appointment ID: %s", idlist.appid); printf("\n");
				printf("Date: %s", idlist.appdate); printf("\n");
				printf("Doctor ID: %s", idlist.docid); printf("\n");
				printf("Disease: %s", idlist.disease); printf("\n\n");
				printf("Description: %s", idlist.description); printf("\n\n");
			}
		}
		if (flag == 0)
		{
			printf("Record for this patient is not exist. Please try again."); printf("\n");
			printf("Please press any key to continue..."); getch();
			system("CLS");
		}
		else
		{
			flag = 0;
			printf("Enter appointment ID: "); scanf(" %s", &confirm2);
			system("CLS");
			rewind(fa);
			while (fread(&idlist, recsize2, 1, fa) == 1)
			{
				if (strcmp(idlist.patid, confirm) != 0)
				{

				}
				else
				{
					if (strcmp(idlist.appid, confirm2) != 0)
					{

					}
					else
					{
					
							fseek(stdin, 0, SEEK_END);
							flag = 1;
							printf("================================================================================"); printf("\n");
							printf("                                  Edit Check                                    "); printf("\n");
							printf("================================================================================"); printf("\n");
							printf("Patient ID: %s", confirm); printf("\n");
							printf("1. Appointment ID: %s", idlist.appid); printf("\n");
							printf("2. Date: %s", idlist.appdate); printf("\n");
							printf("3. Doctor ID: %s", idlist.docid); printf("\n");
							printf("4. Disease: %s", idlist.disease); printf("\n\n");
							printf("5. Description: %s", idlist.description); printf("\n\n");
							printf("6. Edit All"); printf("\n\n\n\n");
							printf("Choose the number to edit: "); scanf("%d", &choice);
							system("CLS");
							if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7)
							{
								switch (choice)
								{
								case 1:
								{
									system("CLS");
									ft = fopen("temp.dat", "wb+");
									rewind(fa);
									while (fread(&idlist, recsize2, 1, fa) == 1)
									{
										if (strcmp(idlist.patid, confirm) != 0)
										{
											fwrite(&idlist, recsize2, 1, ft);
										}
										else
										{
											if (strcmp(idlist.appid, confirm2) != 0)
											{
												fwrite(&idlist, recsize2, 1, ft);
											}
											else
											{
												printf("Enter Appointment ID: "); scanf(" %[^\n]%*c", &idlist.appid);
												strcpy(idlist.disease, idlist.patid);
												strcpy(idlist.appdate, idlist.appdate);
												strcpy(idlist.docid, idlist.docid);
												strcpy(idlist.disease, idlist.disease);
												strcpy(idlist.description, idlist.description);
												fwrite(&idlist, recsize2, 1, ft);
											}
										}
									}

									fclose(fa);
									fclose(ft);
									remove("appointment.txt");
									rename("temp.dat", "appointment.txt");
									fa = fopen("appointment.txt", "rb+");
									fflush(stdin);
									system("CLS");
									break;
								}
								case 2:
								{
									system("CLS");
									ft = fopen("temp.dat", "wb+");
									rewind(fa);
									while (fread(&idlist, recsize2, 1, fa) == 1)
									{
										if (strcmp(idlist.patid, confirm) != 0)
										{
											fwrite(&idlist, recsize2, 1, ft);
										}
										else
										{
											if (strcmp(idlist.appid, confirm2) != 0)
											{
												fwrite(&idlist, recsize2, 1, ft);
											}
											else
											{
												printf("Enter the Date: "); scanf(" %[^\n]%*c", &idlist.appdate);
												strcpy(idlist.disease, idlist.patid);
												strcpy(idlist.appid, idlist.appid);
												strcpy(idlist.docid, idlist.docid);
												strcpy(idlist.disease, idlist.disease);
												strcpy(idlist.description, idlist.description);
												fwrite(&idlist, recsize2, 1, ft);
											}
										}
									}

									fclose(fa);
									fclose(ft);
									remove("appointment.txt");
									rename("temp.dat", "appointment.txt");
									fa = fopen("appointment.txt", "rb+");
									fflush(stdin);
									system("CLS");
									break;
								}
								case 3:
								{
									system("CLS");
									ft = fopen("temp.dat", "wb+");
									rewind(fa);
									while (fread(&idlist, recsize2, 1, fa) == 1)
									{
										if (strcmp(idlist.patid, confirm) != 0)
										{
											fwrite(&idlist, recsize2, 1, ft);
										}
										else
										{
											if (strcmp(idlist.appid, confirm2) != 0)
											{
												fwrite(&idlist, recsize2, 1, ft);
											}
											else
											{
												printf("Enter the Doctor ID: "); scanf(" %[^\n]%*c", &idlist.docid);
												strcpy(idlist.disease, idlist.patid);
												strcpy(idlist.appid, idlist.appid);
												strcpy(idlist.appdate, idlist.appdate);
												strcpy(idlist.disease, idlist.disease);
												strcpy(idlist.description, idlist.description);
												fwrite(&idlist, recsize2, 1, ft);
											}
										}
									}
									fclose(fa);
									fclose(ft);
									remove("appointment.txt");
									rename("temp.dat", "appointment.txt");
									fa = fopen("appointment.txt","rb+");
									fflush(stdin);
									system("CLS");
									break;
								}
								case 4:
								{
									system("CLS");
									ft = fopen("temp.dat", "wb+");
									rewind(fa);
									while (fread(&idlist, recsize2, 1, fa) == 1)
									{
										if (strcmp(idlist.patid, confirm) != 0)
										{
											fwrite(&idlist, recsize2, 1, ft);
										}
										else
										{
											if (strcmp(idlist.appid, confirm2) != 0)
											{
												fwrite(&idlist, recsize2, 1, ft);
											}
											else
											{
												printf("Enter the Date: "); scanf(" %[^\n]%*c", &idlist.disease);
												strcpy(idlist.disease, idlist.patid);
												strcpy(idlist.appid, idlist.appid);
												strcpy(idlist.appdate, idlist.appdate);
												strcpy(idlist.docid, idlist.docid);
												strcpy(idlist.description, idlist.description);
												fwrite(&idlist, recsize2, 1, ft);
											}
										}

										fclose(fa);
										fclose(ft);
										remove("appointment.txt");
										rename("temp.dat", "appointment.txt");
										fa = fopen("appointment.txt", "rb+");
										fflush(stdin);
										system("CLS");
										break;
									}
								}
								case 5:
								{
									system("CLS");
									ft = fopen("temp.dat", "wb+");
									rewind(fa);
									while (fread(&idlist, recsize2, 1, fa) == 1)
									{
										if (strcmp(idlist.patid, confirm) != 0)
										{
											fwrite(&idlist, recsize2, 1, ft);
										}
										else
										{
											if (strcmp(idlist.appid, confirm2) != 0)
											{
												fwrite(&idlist, recsize2, 1, ft);
											}
											else
											{
												printf("Enter the Date: "); scanf(" %[^\n]%*c", &idlist.description);
												strcpy(idlist.disease, idlist.patid);
												strcpy(idlist.appid, idlist.appid);
												strcpy(idlist.appdate, idlist.appdate);
												strcpy(idlist.docid, idlist.docid);
												strcpy(idlist.disease, idlist.disease);
												fwrite(&idlist, recsize2, 1, ft);
											}
										}
									}

									fclose(fa);
									fclose(ft);
									remove("appointment.txt");
									rename("temp.dat", "appointment.txt");
									fa = fopen("appointment.txt", "rb+");
									fflush(stdin);
									system("CLS");
									break;
								}
								case 6:
								{
									printf("================================================================================"); printf("\n");
									printf("                                Editing Record                                  "); printf("\n");
									printf("================================================================================"); printf("\n");
									printf("Appointment ID: "); scanf(" %[^\n]%*c", &idlist.appid);
									printf("Date: "); scanf(" %[^\n]%*c", &idlist.appdate);
									printf("Doctor ID: "); scanf(" %[^\n]%*c", &idlist.docid);
									printf("\nDisease: ");  scanf(" %[^\n]%*c", &idlist.disease);
									printf("\nDescription: "); scanf(" %[^\n]%*c", &idlist.description);
									strcpy(idlist.patid, confirm);
									fseek(fa, -recsize2, SEEK_CUR);
									fwrite(&idlist, -recsize2, 1, fa);
									fflush(stdin);
									break;

								}
								default:
								{
									printf("Invalid choice. Please try again.");
									printf("\n"); printf("Please press any key to continue..."); getch();
									system("CLS");
									break;
								}
								}
							}
							else
							{
								printf("Invalid choice. Please try again.");
								printf("\n"); printf("Please press any key to continue..."); getch();
							}

						}
				}
			}
		}
		if (flag == 0)
		{
			printf("\n\n"); printf("Record not exists. Please try again...");
			printf("\n"); printf("Do you wish to edit another appointment details(y/n)? "); scanf("%s", &delconf);
		}
		else
		{
			
			printf("\n"); printf("Do you wish to edit another appointment details(y/n)? "); scanf("%s", &delconf);
		}
		
	}


	printf("\n\n"); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void appdel()
{
	delconf = 'y';
	fseek(stdin, 0, SEEK_END);
	while (delconf == 'y' || delconf == 'Y')
	{
		system("CLS");
		rewind(fa);
		flag = 0;
		printf("================================================================================"); printf("\n");
		printf("                               Deleting Records                                 "); printf("\n");
		printf("================================================================================"); printf("\n");
		gotoxy(20, 8); printf("Enter Patients ID: "); scanf("%s.txt", &confirm);
		system("CLS");
		printf("================================================================================"); printf("\n");
		printf("                               Deleting Records                                 "); printf("\n");
		printf("================================================================================"); printf("\n");
		
		while (fread(&idlist, recsize2, 1, fa) == 1)
		{
			if (strcmp(idlist.patid, confirm) != 0)
			{

			}
			else
			{
				flag = 1;
				printf("Appointment ID: %s", idlist.appid); printf("\n");
				printf("Date: %s", idlist.appdate); printf("\n");
				printf("Doctor ID: %s", idlist.docid); printf("\n");
				printf("Disease: %s", idlist.disease); printf("\n\n");
				printf("Description: %s", idlist.description); printf("\n\n");
			}
		}
		if (flag == 0)
		{
			printf("Record for this patient is not exist. Please try again."); printf("\n");
			printf("Please press any key to continue..."); getch();
			system("CLS");
		}
		else
		{
			flag = 0;
			ft = fopen("temp.dat", "wb+");
			rewind(fa);
			printf("Enter appointment ID of the record that you wish to delete: "); scanf(" %s", &confirm2);
			system("CLS");
			while (fread(&idlist, recsize2, 1, fa) == 1)
			{
				if (strcmp(idlist.patid, confirm) != 0)
				{
					fwrite(&idlist, recsize2, 1, ft);
				}
				else
				{
					if (strcmp(idlist.appid, confirm2) != 0)
					{
						fwrite(&idlist, recsize2, 1, ft);
					}
					else
					{
						fseek(stdin, 0, SEEK_END);
						flag = 1;
						printf("================================================================================"); printf("\n");
						printf("                              Delete Confirmation                               "); printf("\n");
						printf("================================================================================"); printf("\n");
						printf("Appointment ID: %s", idlist.appid); printf("\n");
						printf("Date: %s", idlist.appdate); printf("\n");
						printf("Doctor ID: %s", idlist.docid); printf("\n");
						printf("Disease: %s", idlist.disease); printf("\n\n");
						printf("Description: %s", idlist.description); printf("\n\n\n");
						printf("Is this the appointment record you wanted to delete(y/n)? : "); scanf("%s", &delconf);
						if (delconf == 'y' || delconf == 'Y')
						{

						}
						else
						{
							fwrite(&idlist, recsize2, 1, ft);
						}
					}
				}
			}
			delconf = 'n';
			if (flag == 0)
			{
				printf("\n"); printf("There are no appointment details with this appointment ID!!\nPlease try again.");
				fclose(ft);
				remove("temp.dat");
				printf("\n\n"); printf("Please press any key to continue..."); getch();
				system("CLS");
			}
			else
			{
				fclose(fa);
				fclose(ft);
				remove("appointment.txt");
				rename("temp.dat", "appointment.txt");
				fa = fopen("appointment.txt", "rb+");
			}
		}
		fseek(stdin, 0, SEEK_END);
		printf("\n"); printf("Delete other patient appointment details(y/n)?"); scanf("%s", &delconf);
		system("CLS");
	}
}

void appsearch()
{
	delconf = 'y';
	fseek(stdin, 0, SEEK_END);
	while (delconf == 'y' || delconf == 'Y')
	{
		system("CLS");
		flag = 0;
		printf("================================================================================"); printf("\n");
		printf("                               Searching Records                                "); printf("\n");
		printf("================================================================================"); printf("\n");
		gotoxy(20, 8); printf("Enter Patients ID: "); scanf("%s.txt", &confirm);
		system("CLS");
		printf("================================================================================"); printf("\n");
		printf("                               Searching Records                                "); printf("\n");
		printf("================================================================================"); printf("\n");
		rewind(fa);
		while (fread(&idlist, recsize2, 1, fa) == 1)
		{
			if (strcmp(idlist.patid, confirm) != 0)
			{

			}
			else
			{
				flag = 1;
				printf("Appointment ID: %s", idlist.appid); printf("\n");
				printf("Date: %s", idlist.appdate); printf("\n");
				printf("Doctor ID: %s", idlist.docid); printf("\n");
				printf("Disease: %s", idlist.disease); printf("\n\n");
				printf("Description: %s", idlist.description); printf("\n\n");
			}
		}
		if (flag == 1)
		{
			printf("\n\n"); printf("1. Search by appointment ID");
			printf("\n");   printf("2. Search by Date");
			printf("\n");   printf("Enter your choice: "); scanf("%d", &choice);
			if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7)
			{
				switch (choice)
				{
				case 1:
				{
					if (flag == 0)
					{
						printf("Record for this patient is not exist. Please try again."); printf("\n");
						printf("Please press any key to continue..."); getch();
						system("CLS");
					}
					else
					{
						flag = 0;
						printf("Enter appointment ID: "); scanf(" %s", &confirm2);
						system("CLS");
						rewind(fa);
						while (fread(&idlist, recsize2, 1, fa) == 1)
						{
							if (strcmp(idlist.patid, confirm) != 0)
							{

							}
							else
							{
								if (strcmp(idlist.appid, confirm2) != 0)
								{

								}
								else
								{

									fseek(stdin, 0, SEEK_END);
									flag = 1;
									printf("================================================================================"); printf("\n");
									printf("                                Search Result                                   "); printf("\n");
									printf("================================================================================"); printf("\n");
									printf("Appointment ID: %s", idlist.appid); printf("\n");
									printf("Date: %s", idlist.appdate); printf("\n");
									printf("Doctor ID: %s", idlist.docid); printf("\n");
									printf("Disease: %s", idlist.disease); printf("\n\n");
									printf("Description: %s", idlist.description); printf("\n\n\n");
								}
							}
						}
					} break;
				}
				case 2:
				{
					if (flag == 0)
					{
						printf("Record for this patient is not exist. Please try again."); printf("\n");
						printf("Please press any key to continue..."); getch();
						system("CLS");
					}
					else
					{
						flag = 0;
						printf("Enter appointment date: "); scanf(" %s", &confirm2);
						system("CLS");
						rewind(fa);
						while (fread(&idlist, recsize2, 1, fa) == 1)
						{
							if (strcmp(idlist.patid, confirm) != 0)
							{

							}
							else
							{
								if (strcmp(idlist.appdate, confirm2) != 0)
								{

								}
								else
								{

									fseek(stdin, 0, SEEK_END);
									flag = 1;
									printf("================================================================================"); printf("\n");
									printf("                                Search Result                                   "); printf("\n");
									printf("================================================================================"); printf("\n");
									printf("Appointment ID: %s", idlist.appid); printf("\n");
									printf("Date: %s", idlist.appdate); printf("\n");
									printf("Doctor ID: %s", idlist.docid); printf("\n");
									printf("Disease: %s", idlist.disease); printf("\n\n");
									printf("Description: %s", idlist.description); printf("\n\n\n");
								}
							}
						}
					} break;
				}
				default:
				{
					printf("Invalid choice. Please try again.");
					printf("\n"); printf("Please press any key to continue..."); getch();
					break;
				}
				}
			}
			else
			{
				printf("Invalid choice. Please try again.");
				printf("\n"); printf("Please press any key to continue..."); getch();
			}
		}
		else
		{
			printf("\n"); printf("Patient no exist. Please try again.");
		}
		printf("\n\n"); printf("Do you want to search another appointment details(y/n)?"); scanf("%s", &delconf);
	}
	printf("\n\n"); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void menu() //gotoxy need edit, case not finish, loop not finish
{
	fseek(stdin, 0, SEEK_END);
	choice = 0;
	gotoxy(20, 5);  printf("********************************************");
	gotoxy(20, 6);  printf("*  Patient Appointment Reservation System  *");
	gotoxy(20, 7);  printf("********************************************");
	gotoxy(20, 8);  printf("********************************************");
	gotoxy(20, 9);  printf("*  1. Log in as Administrator              *");
	gotoxy(20, 10); printf("*  2. Log in as User                       *");
	gotoxy(20, 11); printf("*                                          *");
	gotoxy(20, 12); printf("*  9. Exit                                 *");
	gotoxy(20, 13); printf("*  Enter your choice:                      *");
	gotoxy(20, 14); printf("********************************************");
	gotoxy(42, 13); scanf("%d", &choice);
	system("CLS");
	if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
	{
		switch (choice)
		{
		case 1:
		{
			out = 0;
			pass = 0;
			adminpassword();
			if (pass == 1)
			{
				while (out == 0)
				{
					adminmode();
				}
			}
			break;
		}
		case 2:
		{
			out = 0;
			pass = 0;
			userpassword();
			if (pass == 1)
			{
				while (out == 0)
				{
					usermode();
				}
			}
			break;
		}
		case 9:
		{
			fclose(fp);
			fclose(fa);
			system("CLS");
			gotoxy(20, 8); printf("Exiting the program...");
			exit(0);
			gotoxy(20, 9); printf("Please press any key to continue..."); getch();
		}
		default:
		{
			system("CLS");
			gotoxy(20, 8); printf("Invalid choice. Please try again.");
			gotoxy(20, 9); printf("Please press any key to continue...");
			getch();
			break;
		}
		}
	}
	else
	{
		gotoxy(20, 8); printf("Invalid choice. Please try again.");
		gotoxy(20, 9); printf("Please press any key to continue...");
		getch();
	}



}

void adminmode()
{
	fseek(stdin, 0, SEEK_END);
	choice = 0;
	yesno = 'y';
	delconf = 'y';
	gotoxy(20, 5);  printf("********************************************");
	gotoxy(20, 6);  printf("*  Patient Appointment Reservation System  *");
	gotoxy(20, 7);  printf("*        *Log in as Administrator*         *");
	gotoxy(20, 8);  printf("********************************************");
	gotoxy(20, 9);  printf("********************************************");
	gotoxy(20, 10); printf("*  1. Appointment                          *");
	gotoxy(20, 11); printf("*  2. Patient Details                      *");
	gotoxy(20, 12); printf("*  3. Prescription                         *");
	gotoxy(20, 13); printf("*                                          *");
	gotoxy(20, 14); printf("*                                          *");
	gotoxy(20, 15); printf("*  8. Logout and back to main menu         *");
	gotoxy(20, 16); printf("*  9. Exit                                 *");
	gotoxy(20, 17); printf("*  Enter your choice:                      *");
	gotoxy(20, 18); printf("********************************************");
	gotoxy(42, 17); scanf("%d", &choice);
	system("CLS");
	if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
	{
		switch (choice)
		{
		case 1:
		{
			//fflush(stdin);
			out2 = 0;
			while (out2 == 0)
			{
				yesno = 'y';
				delconf = 'y';
				fseek(stdin, 0, SEEK_END);
				choice = 0;
				gotoxy(20, 5);  printf("********************************************");
				gotoxy(20, 6);  printf("*               Appointment                *");
				gotoxy(20, 7);  printf("*        *Log in as Administrator*         *");
				gotoxy(20, 8);  printf("********************************************");
				gotoxy(20, 9);  printf("********************************************");
				gotoxy(20, 10); printf("*  1. Add Records                          *");
				gotoxy(20, 11); printf("*  2. View Records                         *");
				gotoxy(20, 12); printf("*  3. Search Records                       *");
				gotoxy(20, 13); printf("*  4. Edit Records                         *");
				gotoxy(20, 14); printf("*  5. Delete Records                       *");
				gotoxy(20, 15); printf("*                                          *");
				gotoxy(20, 16); printf("*  8. Back to main menu                    *");
				gotoxy(20, 17); printf("*  Enter your choice:                      *");
				gotoxy(20, 18); printf("********************************************");
				gotoxy(42, 17); scanf("%d", &choice);
				system("CLS");
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
				{
					switch (choice)
					{
					case 1:
					{
						appadd();
						break;
					}
					case 2:
					{
						appview();
						break;
					}
					case 3:
					{
						appsearch();
						break;
					}
					case 4:
					{
						appedit();
						break;
					}
					case 5:
					{
						appdel();
						break;
					}
					case 8:
					{
						out2 = 1;
						break;
					}
					default:
					{
						system("CLS");
						gotoxy(20, 8); printf("Invalid choice. Please try again.");
						gotoxy(20, 9); printf("Please press any key to continue..."); getch();
						break;
					}

					}
				}
				else
				{
					gotoxy(20, 8); printf("Invalid choice. Please try again.");
					gotoxy(20, 9); printf("Please press any key to continue..."); getch();
				}

			}
			break;
		}
		case 2:
		{
			out2 = 0;
			while (out2 == 0)
			{
				yesno = 'y';
				delconf = 'y';
				fseek(stdin, 0, SEEK_END);
				choice = 0;
				gotoxy(20, 5);  printf("********************************************");
				gotoxy(20, 6);  printf("*             Patients Details             *");
				gotoxy(20, 7);  printf("*        *Log in as Administrator*         *");
				gotoxy(20, 8);  printf("********************************************");
				gotoxy(20, 9);  printf("********************************************");
				gotoxy(20, 10); printf("*  1. Add Records                          *");
				gotoxy(20, 11); printf("*  2. View Records                         *");
				gotoxy(20, 12); printf("*  3. Search Records                       *");
				gotoxy(20, 13); printf("*  4. Edit Records                         *");
				gotoxy(20, 14); printf("*  5. Delete Records                       *");
				gotoxy(20, 15); printf("*                                          *");
				gotoxy(20, 16); printf("*  8. Back to main menu                    *");
				gotoxy(20, 17); printf("*  Enter your choice:                      *");
				gotoxy(20, 18); printf("********************************************");
				gotoxy(42, 17); scanf("%d", &choice);
				system("CLS");
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
				{
					switch (choice)
					{
					case 1:
					{
						patadd();
						break;
					}
					case 2:
					{
						patview();
						break;
					}
					case 3:
					{
						patsearch();
						break;
					}
					case 4:
					{
						patedit();
						break;
					}
					case 5:
					{
						patdel();
						break;
					}
					case 8:
					{
						out2 = 1;
						break;
					}
					default:
					{
						system("CLS");
						gotoxy(20, 8); printf("Invalid choice. Please try again.");
						gotoxy(20, 9); printf("Please press any key to continue..."); getch();
						break;
					}

					}
				}
				else
				{
					gotoxy(20, 8); printf("Invalid choice. Please try again.");
					gotoxy(20, 9); printf("Please press any key to continue..."); getch();
				}
			}
			break;
		}
		case 3:
		{
			prescription();
			break;

		}
		case 8:
		{
			out = 1;
			break;
		}
		case 9:
		{
			fclose(fp);
			fclose(fa);
			printf("Exiting the program...");
			exit(0);
			printf("\n"); printf("Please press any key to continue...");
			getch();
		}
		default:
		{
			system("CLS");
			gotoxy(20, 8); printf("Invalid choice. Please try again.");
			gotoxy(20, 9); printf("Please press any key to continue..."); getch();
			break;
		}
		}
	}
	else
	{
		gotoxy(20, 8); printf("Invalid choice. Please try again.");
		gotoxy(20, 9); printf("Please press any key to continue..."); getch();
	}
}

void usermode()
{
	yesno = 'y';
	delconf = 'y';
	fseek(stdin, 0, SEEK_END);
	choice = 0;
	gotoxy(20, 5);  printf("********************************************");
	gotoxy(20, 6);  printf("*  Patient Appointment Reservation System  *");
	gotoxy(20, 7);  printf("*            *Log in as User*              *");
	gotoxy(20, 8);  printf("********************************************");
	gotoxy(20, 9);  printf("********************************************");
	gotoxy(20, 10); printf("*  1. Appointment                          *");
	gotoxy(20, 11); printf("*  2. Patient Details                      *");
	gotoxy(20, 12); printf("*  3. Prescription                         *");
	gotoxy(20, 13); printf("*                                          *");
	gotoxy(20, 14); printf("*                                          *");
	gotoxy(20, 15); printf("*  8. Logout and back to main menu         *");
	gotoxy(20, 16); printf("*  9. Exit                                 *");
	gotoxy(20, 17); printf("*  Enter your choice:                      *");
	gotoxy(20, 18); printf("********************************************");
	gotoxy(42, 17); scanf("%d", &choice);
	system("CLS");
	if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
	{
		switch (choice)
		{
		case 1:
		{
			out2 = 0;
			while (out2 == 0)
			{
				yesno = 'y';
				delconf = 'y';
				fseek(stdin, 0, SEEK_END);
				choice = 0;
				gotoxy(20, 5);  printf("********************************************");
				gotoxy(20, 6);  printf("*              Appointment                 *");
				gotoxy(20, 7);  printf("*            *Log in as User*              *");
				gotoxy(20, 8);  printf("********************************************");
				gotoxy(20, 9);  printf("********************************************");
				gotoxy(20, 10); printf("*  1. View Records                         *");
				gotoxy(20, 11); printf("*  2. Search Records                       *");
				gotoxy(20, 12); printf("*                                          *");
				gotoxy(20, 13); printf("*  8. Back to main menu                    *");
				gotoxy(20, 14); printf("*  Enter your choice:                      *");
				gotoxy(20, 15); printf("********************************************");
				gotoxy(42, 14); scanf("%d", &choice);
				system("CLS");
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
				{
					switch (choice)
					{
					case 1:
					{
						appview();
						break;
					}
					case 2:
					{
						appsearch();
						break;
					}
					case 8:
					{
						out2 = 1;
						break;
					}
					default:
					{
						system("CLS");
						gotoxy(20, 8); printf("Invalid choice. Please try again.");
						gotoxy(20, 9); printf("Please press any key to continue..."); getch();
						break;
					}
					}
				}
				else
				{
					gotoxy(20, 8); printf("Invalid choice. Please try again.");
					gotoxy(20, 9); printf("Please press any key to continue..."); getch();
				}
			}
			break;
		}
		case 2:
		{
			out2 = 0;
			while (out2 == 0)
			{
				yesno = 'y';
				delconf = 'y';
				fseek(stdin, 0, SEEK_END);
				choice = 0;
				gotoxy(20, 5);  printf("********************************************");
				gotoxy(20, 6);  printf("*            Patients Details              *");
				gotoxy(20, 7);  printf("*            *Log in as User*              *");
				gotoxy(20, 8);  printf("********************************************");
				gotoxy(20, 9);  printf("********************************************");
				gotoxy(20, 10); printf("*  1. View Records                         *");
				gotoxy(20, 11); printf("*  2. Search Records                       *");
				gotoxy(20, 12); printf("*                                          *");
				gotoxy(20, 13); printf("*  8. Back to main menu                    *");
				gotoxy(20, 14); printf("*  Enter your choice:                      *");
				gotoxy(20, 15); printf("********************************************");
				gotoxy(42, 14); scanf("%d", &choice);
				system("CLS");
				if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 8 || choice == 9)
				{
					switch (choice)
					{
					case 1:
					{
						patview();
						break;
					}
					case 2:
					{
						patsearch();
						break;
					}
					case 8:
					{
						out2 = 1;
						break;
					}
					default:
					{
						system("CLS");
						gotoxy(20, 8); printf("Invalid choice. Please try again.");
						gotoxy(20, 9); printf("Please press any key to continue..."); getch();
						break;
					}

					}
				}
				else
				{
					gotoxy(20, 8); printf("Invalid choice. Please try again.");
					gotoxy(20, 9); printf("Please press any key to continue..."); getch();
				}
			}
			break;
		}
		case 3:
		{
			prescription();
			break;
		}
		case 8:
		{
			out = 1;
			break;
		}
		case 9:
		{
			fclose(fp);
			fclose(fa);
			printf("Exiting the program...");
			exit(0);
			printf("\n"); printf("Please press any key to continue...");
			getch();
		}
		default:
		{
			system("CLS");
			gotoxy(20, 8); printf("Invalid choice. Please try again.");
			gotoxy(20, 9); printf("Please press any key to continue..."); getch();
			break;
		}
		}
	}
	else
	{
		gotoxy(20, 8); printf("Invalid choice. Please try again.");
		gotoxy(20, 9); printf("Please press any key to continue..."); getch();
	}
}

void adminpassword()
{

	pass = 0;
	for (i = 0; i < 30; i++)
	{
		input[i] = '\0';
	}
	fseek(stdin, 0, SEEK_END);
	printf("Note that every word you type is an input except Enter,Shift, Caps Lock and Num Lock");
	gotoxy(20, 10); printf("Enter the password: ");
	i = 0;
	input[0] = _getch();
	while (input[i] != 13)
	{
		i++;
		printf("*");
		input[i] = _getch();
	}
	//input2 = input;
	/*	j = strlen(input);
	i = 0;
	while (i < j)
	{
	input2[i] = input[i];
	i++;
	}
	*/

	if (input == adminpass)
	{
		system("CLS");
		gotoxy(20, 8); printf("Log in success...");
		pass = 1;
	}
	else
	{
		system("CLS");
		gotoxy(20, 8); printf("Log in FAIL!!!");
		gotoxy(20, 9); printf("Returning to the homepage...");

	}

	fflush(stdin);

	//printf("\n"); printf("%s\n\n%d", input2, j);
	gotoxy(20, 10); printf("Please press any key to continue..."); getch();
	system("CLS");

}

void userpassword()
{
	pass = 0;
	for (i = 0; i < 30; i++)
	{
		input[i] = '\0';
	}
	fseek(stdin, 0, SEEK_END);
	printf("Note that every word you type is an input except Enter,Shift, Caps Lock and Num Lock");
	gotoxy(20, 10); printf("Enter the password: ");
	i = 0;
	input[0] = _getch();
	while (input[i] != 13)
	{

		i++;
		printf("*");
		input[i] = _getch();
	}
	//input2 = input;
	/*	j = strlen(input);
	i = 0;
	while (i < j)
	{
	input2[i] = input[i];
	i++;
	}
	*/

	if (input == userpass)
	{
		system("CLS");
		gotoxy(20, 8); printf("Log in success...");
		pass = 1;
	}
	else
	{
		system("CLS");
		gotoxy(20, 8); printf("Log in FAIL!!!");
		gotoxy(20, 9); printf("Returning to the homepage...");
	}


	fflush(stdin);
	//printf("\n"); printf("%s\n\n%d", input2, j);
	gotoxy(20, 10); printf("Please press any key to continue..."); getch();
	system("CLS");
}

void prescription()
{
	fseek(stdin, 0, SEEK_END);
	rewind(fp);
	printf("================================================================================"); printf("\n");
	printf("                                 Prescription                                   "); printf("\n");
	printf("================================================================================");

	while (fread(&list, recsize, 1, fp) == 1)
	{
		printf("\n");  printf("Patient ID: %s", list.id); printf("\n");
		printf("Patient Name: %s", list.name); printf("\n");
		rewind(fa);
		while (fread(&idlist, recsize2, 1, fa) == 1)
		{
			if (strcmp(idlist.patid, list.id) != 0)
			{

			}
			else
			{
				printf("Appointment ID: %s", idlist.appid); printf("\n");
				printf("Date: %s", idlist.appdate); printf("\n");
				printf("Doctor ID: %s", idlist.docid); printf("\n");
				printf("Disease: %s", idlist.disease); printf("\n\n");
				printf("Description: %s", idlist.description); printf("\n\n");
			}

		}
		printf("\n"); printf("================================================================================");
	}
	printf("\n\n"); printf("Please press any key to continue..."); getch();
	system("CLS");
}

//setting in user interface need to be fixed, password check for 3 times?