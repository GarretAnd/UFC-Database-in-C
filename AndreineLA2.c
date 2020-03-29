#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For Malloc Maybe?
#include <ctype.h> //For Checking If Something Is A Digit  

typedef struct{
	
char LastName[20]; //Last Name Of Fighter

char FirstInit; //First Initial Of Fighter
	
int NumFights; //Number Of Fights

int Strikes; //Number Of Strikes Made

int TDs; //Number Of Take Downs Made

int Subs; //Number Of Submissions Made

float Accuracy; //Accuracy Of Fighter's Strikes	
	
}Fight_t;

int Filler(Fight_t Var[], int j, char Input[]);//Fills Array With Data 
int Menu(int y);//Takes User Input And Passes It To DecisionMaker
int DecisionMaker(int y, Fight_t Var[], int j, int SortArray[], int *jsaddy, char Input[]); //Function That Holds All Other Functions
void Display(Fight_t Var[], int j, int SortArray[]);//To Show Contents Of Database 
int Add(Fight_t Var[], int j, int SortArray[], char Input[]);////Function To Add Data To Database
void Searcher(Fight_t Var[], int j, int SortArray[]);//Function To Find Certain Data
int Delete(Fight_t Var[], int j, int SortArray[]);//Function To Delete
void FileSave(Fight_t Var[], int j, int SortArray[]); //Function To Save File

int main(void)
{
	
	int j = 0; //Number That Lets The User Know How Many Times The File Scanned Referred To As Counter 
	int b; //Variable To Fill Sort Array
	int y = 0;//Starter Variable To Run Some Functions
	Fight_t Var[100]; //Setting Structure Fight_t To Var With Space For 100 Entries
	int SortArray[100]; //Array That Hlds The Position Of Each Sort
	char Input[30]; //Array That Holds File Name
	
	
	for (b = 0; b<100; b++)
	{
		SortArray[b] = b; //Creates Array To Sort With 
	}
	
	j = Filler(Var, j, Input); //Filling Up Var With Data Of UFC Fighters
	
	while (y == 0) //Keeps It In While Loop Until User Chooses To Leave Database 
	{	
		y = Menu(y); //Taking The User's Input And Returning It To Main
		
		y = DecisionMaker(y, Var, j, SortArray, &j, Input); //Takes The Value From The Menu And Takes It To The Decision Maker Which Tells The Computer What To Do
	}
	return(0);
}

int Filler(Fight_t Var[], int j, char Input[]) //Fills Up Array Of Structures With Data 
{
	int i; 
	int Checker = 0;
	char jnk; //Junk Variable For Enter 
	
	//File Name Entered
	
	printf("Please Enter A File Name To Scan UFC Data From Or Enter \"0\" To Use The Default Data Of UFCData.txt: ");
	scanf("%s%c", Input, &jnk);
	
	if (strcmp(Input, "0") == 0) //Default Case Given We Can't Just Scan An Enter Into A String 
	{
		strcpy(Input, "UFCData.txt");
	}
	
	FILE *iFile;
	
	iFile = fopen(Input,"r");
	
	while(iFile == NULL) //Checks If File Does Not Exsist And Prompts Reentering If It Does Not
	{
		printf("This File Does Not Exist. Try Again!\n");
		printf("Please Enter A File Name To Scan UFC Data From Or Enter \"0\" To Use The Default Data Of UFCData.txt: : ");
		scanf("%s", Input);
		iFile = fopen(Input,"r");
	}
	
	
	
	for (i=0;fscanf(iFile,"%d", &Checker) != EOF; i++) //Scans Data From File Into Array And Keeps Track Of How Many Lines There Are 
	{
		
		fscanf(iFile,"%[^,],%c,%d,%d,%d,%d,%f", Var[i].LastName, &Var[i].FirstInit, &Var[i].NumFights, &Var[i].Strikes, &Var[i].TDs, &Var[i].Subs, &Var[i].Accuracy);
		//Scanning The Data Seperated By Commas Into The Fighter Structure 
		j = i;//Keeps Track Of How Many Times The File Was Scanned

		//printf("Last Name: %s First Initial: %c Number Of Fights: %d ", Var[i].LastName, Var[i].FirstInit, Var[i].NumFights); 
		//printf("Strikes Made %d Number Of Takedowns Made: %d Number Of Submission Wins: %d Strike Accuracy: %.2f \n", Var[i].Strikes, Var[i].TDs, Var[i].Subs, Var[i].Accuracy);
	}
	
	fclose(iFile);
	return(j); //Returns The Counter 
}

int Menu(int y)
{
	char x;
	char jnk; //Lets The User Choose What To Do 
	
	while (y == 0)
	{
		
		
		printf("_______________|Welcome To The Premier UFC Database|_______________\n");
		printf(" Please Select An Option: \n");
		printf(" Enter \"1\" To Display The Data Currently In The Database. [Default Choice]\n");
		printf(" Enter \"2\" To Add Data To The Database. \n");
		printf(" Enter \"3\" To Remove Data From The Database. \n");
		printf(" Enter \"4\" To Save The Data In The Database To A New File. \n");
		printf(" Enter \"5\" To Leave The Database. \n");
		printf(" Enter \"6\" To Search Fighters By Last Name Or The Number Of Bouts Competed In. \n");
		
		scanf("%c", &x);
		if (x == '\n') 
		{
			x = '1';
			printf("\nDefault Chosen!");
		}
		else
		{
			scanf("%c", &jnk);
		}

		if(x == '1')
		{
			y = 1;
		}
		else if (x == '2')
		{
			y = 2;
		}
		else if (x == '3')
		{
			y = 3;
		}
		else if (x == '4')
		{
			y = 4;
		}
		else if (x == '5')
		{
			y = 5;
		}
		else if (x == '6')
		{
			y = 6;
		}
		else 
		{
			printf("Invalid Entry! Please Try Again.\n");
			y = 0;
		}
	}
	
	return(y); //Takes Their Input And Passes It To Decision Maker 
}

int DecisionMaker(int y, Fight_t Var[100], int j, int SortArray[], int *jsaddy, char Input[]) //Decision From Menu Gets Passed To Decision Maker Which Holds Functions That Do Other Things
{
	if (y == 4)
	{
		y = 0;
		FileSave(Var, j, SortArray); //If They Enter 4 They Go Into The FileSave Function 
	}
	else if (y == 2)
	{
		y = 0;
		*jsaddy = Add(Var, j, SortArray, Input); //If They Enter 2 They Enter The Add Function Which Also Updates The Counter Via Pointer
	}
	else if (y == 3)
	{
		y = 0;
		*jsaddy = Delete(Var, j, SortArray); //If They Enter 3 They Enter The Delete Function Which Also Updates The Counter Via Pointer
	}
	else if (y == 1)
	{
		y = 0;
		Display(Var, j, SortArray); //Takes Us To Display Function If They Enter 1
	}
	else if (y == 5)
	{
		y = 1; //Returns A Value That Pops Everything Out Of The While Loop In The Main Function And Ends Program If They Enter 5 (Leave Value)
		return(y);
	}
	else if (y == 6)
	{
		y =0;
		Searcher(Var, j, SortArray); //If The User Enters 6 It Enters The Search Function 
	}
	else 
	{
		y = 0; //Almost All Values Return Y = 0 To Keep User In While Loop In Main Function And Return Them To The Menu Except The Leave Value 
	} 
	
	return(y);
}

void Display(Fight_t Var[], int j, int SortArray[]) //Displays The Values In The Database And Allows The User To Access The Sort Function 
{
	int i = 0; 
	char Answer; //Answer Stored Here 
	char jnk;//Enter Stored Here 
	int y = 0;
	int q; // Counter For First For Loop In String Compare
	int w; // Counter For Second For Loop In String Compare
	int prize; //Variable That Holds Data In String Compare
	
	while(i <= j) 
	{
		printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
		printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
		i++;
	}//Prints Out All Data In Array
	
	while(y == 0)
	{//Gives User Options To Sort By 
			
		printf("\nHow Would You Like The Data To Be Sorted?");
		printf("\nEnter \"1\" If You Would Like To Sort By Last Name. [Default Choice]");
		printf("\nEnter \"2\" If You Would Like To Sort By First Initial."); //Will Have An Option A-Z Or Z-A
		printf("\nEnter \"3\" If You Would Like To Sort By Number Of Bouts."); //Will Have Option To Sort By Ascending Or Decending Order 
		printf("\nEnter \"4\" If You Would Like To Sort By Number Of Strikes Made."); //Will Have Option To Sort By Ascending Or Decending Order
		printf("\nEnter \"5\" If You Would Like To Sort By Number Of Takedowns Made."); //Will Have Option To Sort By Ascending Or Decending Order
		printf("\nEnter \"6\" If You Would Like To Sort By Number Of Submission Wins."); //Will Have Option To Sort By Ascending Or Decending Order
		printf("\nEnter \"7\" If You Would Like To Sort By Percentage Of Strike Accuracy. \n"); //Will Have Option To Sort By Ascending Or Decending Order
		
		
		scanf("%c", &Answer);//If They Hit Enter They Enter The Default Case 
		if (Answer == '\n') 
		{
			Answer = '1';
			printf("\nDefault Chosen!\n");
		}
		else
		{
			scanf("%c", &jnk); //Stores The Extra Data Into Junk 
		}
			
		if(Answer == '1')
		{
			//Displays Last Name In A-Z Order Via Bubble Sort 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(strcmp(Var[SortArray[w]].LastName, Var[SortArray[w+1]].LastName) > 0)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++) 
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else if (Answer == '2')
		{
			//Displays First Initial A-Z Via Bubble Sort 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(Var[SortArray[w]].FirstInit > Var[SortArray[w+1]].FirstInit)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++)
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else if (Answer == '3')
		{
			//Sorts By Number Of Fights Via Bubble Sort Where It Goes High->Low 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(Var[SortArray[w]].NumFights < Var[SortArray[w+1]].NumFights)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++)
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else if (Answer == '4')
		{
			//Sorts By Number Of Strikes Via Bubble Sort High -> Low 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(Var[SortArray[w]].Strikes < Var[SortArray[w+1]].Strikes)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++)
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else if (Answer == '5')
		{
			//Sorts By Takedowns Via Bubble Sort High -> Low 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(Var[SortArray[w]].TDs < Var[SortArray[w+1]].TDs)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++)
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else if (Answer == '6')
		{
			//Sorts By Number Of Submissions From High -> Low 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(Var[SortArray[w]].Subs < Var[SortArray[w+1]].Subs)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++)
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else if (Answer == '7')
		{
			//Sorts By Accuracy From High -> Low 
			for (q=0; q<=j; q++)
			{
				for (w=0;w<j; w++)
				{
					if(Var[SortArray[w]].Accuracy < Var[SortArray[w+1]].Accuracy)
					{
						prize = SortArray[w];
						SortArray[w] = SortArray[w+1];
						SortArray[w+1] = prize;
					}
				}
			}
			for (i=0; i <= j; i++)
			{
				printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
				printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
			}
			y = 1;
		}
		else 
		{
			printf("Invalid Entry! Please Try Again.\n");
			y = 0;
		}//Basically, If The User Enters A Letter It Fails And Gets Prompted To Enter Again
		//If The User Enters A Number Not 1-7 The User Fails And Gets Prompted To Enter Again
	}
}

int Add(Fight_t Var[], int j, int SortArray[], char Input[]) //Lets User Add Data To Database 
{
	FILE *oFile;
	
	j++;
	char jnk;
	
	oFile = fopen(Input, "a");
	
	printf("\nYou Will Now Fill In Data For The Fighter To Add To The Database, For Any Unknown Data Just Enter \"0\".\n");
	
	printf("\nPlease Enter The Last Name Of The Fighter: ");
	scanf(" %[^\n]*c", Var[SortArray[j]].LastName);
	printf("\nPlease Enter The First Initial Of The Fighter: "); 
	scanf(" %c", &Var[SortArray[j]].FirstInit);
	printf("\nPlease Enter The Number Of Bouts The Fighter Has Competed In: ");
	scanf("%d", &Var[SortArray[j]].NumFights);
	printf("\nPlease Enter The Number Of Strikes Made By The Fighter: "); 
	scanf("%d", &Var[SortArray[j]].Strikes);
	printf("\nPlease Enter The Number Of Takedowns Made By The Fighter: ");
	scanf("%d", &Var[SortArray[j]].TDs);
	printf("\nPlease Enter The Number Of Submission Wins The Fighter Has: ");
	scanf("%d", &Var[SortArray[j]].Subs);
	printf("\nPlease Enter The Accuracy (Out Of 100.00) Of The Fighters Strikes Made To Strikes Thrown Ratio: ");
	scanf("%f", &Var[SortArray[j]].Accuracy);
	scanf("%c", &jnk);
	
	
	fprintf(oFile, "\n%s,%c,%d,%d,%d,%d,%.2f", Var[SortArray[j]].LastName, Var[SortArray[j]].FirstInit, Var[SortArray[j]].NumFights, Var[SortArray[j]].Strikes, Var[SortArray[j]].TDs, Var[SortArray[j]].Subs, Var[SortArray[j]].Accuracy);
	
	fclose(oFile); //Stores Data In File And Closes It 
	
	printf("\nThe New Fighter Has Been Added To The Database!\n");
	
	return(j); //Need To Return The Value J To Update The Counter
}

void Searcher(Fight_t Var[], int j, int SortArray[]) //Lets The User Search For Data And Displays It 
{
	char array[30];
	char Answer;
	int Bouts;
	int i; 
	char jnk;
	
	while (Answer == 0)
	{
		printf("\nWould You Like To Search By The Number Of Bouts \"1\" [Default] Or The Last Name \"2\"?: ");
		scanf("%c", &Answer); //Default Case Of Searching For Number Of Bouts 
		if (Answer == '\n') 
		{
			Answer = '1';
			printf("\nDefault Chosen!\n");
		}
		else
		{
			scanf("%c", &jnk);
		}
	
	
		if (Answer == '1')
		{
			printf("Please Enter The Number Of Bouts: "); //Asks For Bouts And Searches 
			scanf("%d", &Bouts);
			scanf("%c", &jnk);
			
			for (i = 0; i<j; i++)
			{
				if(Var[SortArray[i]].NumFights == Bouts) //Only Prints Data That Matches Input 
				{
					printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
					printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
				}
			}
			
			printf("\nAbove Are The Fighters That Have Competed In %d Many Bouts.\n", Bouts);
		}
		else if (Answer == '2')
		{
			printf("Please Enter The Last Name Of The Fighter: "); //Searchs By Last Name 
			scanf(" %[^\n]s", array);
			scanf("%c", &jnk);
			
			for (i = 0; i<j; i++)
			{
				if(strcmp(Var[SortArray[i]].LastName,array) == 0) //Only Prints Data That Matches Input 
				{
					printf("\nLast Name:%s First Initial:%c Number Of Bouts:%d ", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
					printf("Strikes Made:%d Number Of Takedowns Made:%d Number Of Submission Wins:%d Strike Accuracy:%.2f \n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
				}
			}
			
			printf("\nAbove Are The Fighters That Have The Last Name: %s.\n", array);
		}
		else
		{
			printf("Error, Invalid Input. Try Again!");
			Answer = 0;
		}
	}
}

int Delete(Fight_t Var[], int j, int SortArray[])
{
	char array[30];
	int i;
	int z;
	char jnk;
	
	
	printf("Please Enter The Last Name Of The Fighter You Would Like To Delete: ");
	scanf(" %[^\n]s", array); //Deletes By Last Name 
	scanf("%c", &jnk);
	
	for (i = 0; i<j; i++)
	{
		if( strcmp(Var[SortArray[i]].LastName, array) == 0)
		{
			for (z = i; z<j; z++) //Moves Person With Last Name To Back Then Subtracts From The Counter 
			{
				strcpy(Var[SortArray[z]].LastName,Var[SortArray[z+1]].LastName);
				Var[SortArray[z]].FirstInit = Var[SortArray[z+1]].FirstInit;
				Var[SortArray[z]].NumFights = Var[SortArray[z+1]].NumFights;
				Var[SortArray[z]].Strikes = Var[SortArray[z+1]].Strikes;
				Var[SortArray[z]].TDs = Var[SortArray[z+1]].TDs;
				Var[SortArray[z]].Subs = Var[SortArray[z+1]].Subs;
				Var[SortArray[z]].Accuracy = Var[SortArray[z+1]].Accuracy;
			}
			j = j-1;
		}
	}
	
	
	printf("\nFighter With The Last Name: \"%s\" Has Been Deleted. Please Save The Database To Make This Permanent.\n", array);
	
	return(j); //When You Save The Data Again It Will Only Save The Data In The Amount Of Spaces As The Counter, Won't Save The Data Behind It 
}

void FileSave(Fight_t Var[], int j, int SortArray[])
{
	char array[100];
	FILE *zFile;
	int check;
	int h = 0;
	int i; //Counter For For Loop 
	char jnk;
	
	printf("Please Enter The File Name That You Would Like The Data To Be Saved To: ");
	scanf("%s", array); //Stores The Users Input Into Array 
	scanf("%c", &jnk);
	
	zFile = fopen(array,"r"); 
	
	if (zFile != NULL) //If The File Exsists Prompts The User To Choose To Overwrite It Or Not 
	{
		h = 1;
		while(h == 1)
		{
			printf("This File Already Exists. Are You Sure You Want To Overwrite It?\n");
			printf("Please Enter [1] To Overwrite It Or [2] To Enter A Different File Name: ");
			scanf("%d", &check);
			scanf("%c", &jnk);
			if (check == 1)
			{
				h = 0;
			}
			else if (check == 2) //If They Choose To Not, It Reprompts User To Enter File Name 
			{
				fclose(zFile);
			
				printf("Please Enter The File Name That You Would Like The Data To Be Saved To: ");
				scanf("%s", array);
				scanf("%c", &jnk);
			
				zFile = fopen(array,"r");
	
				if (zFile != NULL)
				{
					h = 1;
				}
				else
				{
					h = 0;
				}
			}
			else 
			{
				printf("Error, Invalid Entry. Try Again.");
				h = 1;
			}
		}
	}
	else 
	{
		h = 0;
	}
	
	zFile = fopen(array,"w");
	
	for (i = 0; i <= j; i++) //Prints The Data To Enter File 
	{
		fprintf(zFile, "%s,%c,%d,", Var[SortArray[i]].LastName, Var[SortArray[i]].FirstInit, Var[SortArray[i]].NumFights); 
		fprintf(zFile, "%d,%d,%d,%.2f\n", Var[SortArray[i]].Strikes, Var[SortArray[i]].TDs, Var[SortArray[i]].Subs, Var[SortArray[i]].Accuracy);
	}
	
	printf("The Database Has Been Saved To The File Titled: \"%s\". \n", array);
	
	fclose(zFile);
}

