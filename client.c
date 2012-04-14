							/*Tic Tac Toe Game by Ishan Ankita*/
									/*Client*/ 

#include<ctype.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#define SIZE sizeof(struct sockaddr_in) 

void catcher(int sig);
void mapBoard(char playBoard[][3]);
void showLogo();

int main(void) 
{
	 
	/*
	sigset_t set1;
	sigfillset(&set1);
	sigprocmask(SIG_SETMASK, &set1, NULL);
	*/
	
	void result(char [],char []);
	static struct sigaction act; 
	act.sa_handler = SIG_IGN; 
	sigfillset(&(act.sa_mask)); 
	sigaction(SIGTSTP, &act, 0);

	struct sockaddr_in server = {AF_INET, 8200}; 
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	int sockfd; 
	char input; 
	int i;
	int row,column,choice;
	int points[2];
	char pnts[2][10];

	char numberBoard [3][3] = {							// to display positions to choose from
	 		         		{'1','2','3'},
		        			{'4','5','6'},
		       				{'7','8','9'}
	       		          }; 

        

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket Call Failed");
		exit(1);
	}

	if ( connect (sockfd, (struct sockaddr *)&server, SIZE) == -1) 
	{ 
		perror("Connect Call Failed"); 
		exit(1); 
	} 



		

	char a[2][40];
	read(sockfd,a,sizeof(a));
	printf("%s\n",a[0]);

	if(strcmp(a[1],"0")==0)
	{
		read(sockfd,a,sizeof(a));
		printf("%s\n",a[0]);
		showLogo();
	}

	char clientRead[5][3];
	strcpy(clientRead[3],"0");
	strcpy(clientRead[4],"0");
	char clientWrite[1];
	int iclientRead; 	
for(;;)
{
		char playBoard [5][3] =   {							// to display the actual game status
			         		{' ',' ',' '},
						{' ',' ',' '},
		       				{' ',' ',' '},
						{' '},
						{' '}	
		                          };

	if (strcmp(a[1],"1")!=0)
	{
		showLogo();		
		mapBoard(numberBoard);	
		printf("\n    Number Board\n\n");
		for(;;)
			{
			printf("\nPlayer %d, Please enter the number of the square where you want to place your '%c': \n",(strcmp(a[1], "1")==0)?1:2,(strcmp(a[1], "1")==0)?'X':'O');
			scanf("%s",clientWrite);
			
			choice = atoi(clientWrite);
			row = --choice/3;
			column = choice%3;
		
			if(choice<0 || choice>9 || playBoard [row][column]>'9'|| playBoard [row][column]=='X' || playBoard [row][column]=='O')
				printf("Invalid Input. Please Enter again.\n\n");
		
			else
				{
				playBoard[row][column] = (strcmp(a[1], "1")==0)?'X':'O';					
				break;
					}
			}	

		write(sockfd, clientWrite, sizeof(clientWrite));
		system("clear");
		showLogo();
		mapBoard(playBoard);
		printf("\nCurrent Play Board\n\n");
	}

	for(input = 'x';;) 
	{ 	
		if (input == '\n') 
		{	
			mapBoard(numberBoard);	
			printf("\n    Number Board\n\n");					
			for(;;)
			{
			printf("\nPlayer %d, Now your turn .. Please enter the number of the square where you want to place your '%c': \n",(strcmp(a[1], "1")==0)?1:2,(strcmp(a[1], "1")==0)?'X':'O');
			scanf("%s",clientWrite);

			choice = atoi(clientWrite);
			row = --choice/3;
			column = choice%3;
		
				if(choice<0 || choice>9 || playBoard [row][column]>'9'|| playBoard [row][column]=='X' || playBoard [row][column]=='O')
				printf("Invalid Input. Please Enter again.\n\n");
		
				else
				{
					playBoard[row][column] = (strcmp(a[1], "1")==0)?'X':'O';
					break;
				}
			}	
			
			write(sockfd, clientWrite, sizeof(clientWrite));
			system("clear");
			showLogo();
			mapBoard(playBoard);
			printf("\nCurrent Play Board\n\n");
			
		}

		if (read(sockfd, clientRead, sizeof(clientRead)) >0) 
		{
			
			system("clear");
			showLogo();
			memcpy(playBoard, clientRead, sizeof(playBoard));	// copy the contents of the array received from server side in playBoard array
			mapBoard(playBoard);
			printf("\nCurrent Play Board\n\n");
			input = '\n';
			printf("Total Points of Player 1 = %s\n",clientRead[3]);		
		        printf("Total Points of Player 2 = %s\n",clientRead[4]);	
			if(strcmp(clientRead[0], "f")==0)
			break;
		}	
		else 
		{
			printf("server has died\n");
			
			printf("Total Points of Player 1 = %s\n",playBoard[3]);		
		        printf("Total Points of Player 2 = %s\n",playBoard[4]);	
			close(sockfd);
			exit(1); 
		} 
		/*system("clear");
		showLogo();
		mapBoard(playBoard);
		printf("\nCurrent Play Board\n\n");*/
			
}	
continue;
}

}

void showLogo() 
{
	printf("--------------------------------------------------------------------------\n");
	printf("| # # #   # # #    # # #   # # #    #      # # #  # # #   # # #   # # #  |\n");
	printf("|   #       #      #   #     #     #  #    #   #    #     #   #   #      |\n");
	printf("|   #       #      #         #    #    #   #        #     #   #   # # #  |\n");
	printf("|   #       #      #   #     #   # #  # #  #   #    #     #   #   #      |\n");
	printf("|   #     # # #    # # #     #  #        # # # #    #     # # #   # # #  |\n");
	printf("--------------------------------------------------------------------------\n");
}

void mapBoard(char playBoard[][3])
{
        printf(" _________________\n");
        printf("|     |     |     | \n");
        printf("|  %c  |  %c  |  %c  |\n",playBoard[0][0],playBoard[0][1],playBoard[0][2]);
        printf("|_____|_____|_____|\n");
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n",playBoard[1][0],playBoard[1][1],playBoard[1][2]);
        printf("|_____|_____|_____|\n");
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n",playBoard[2][0],playBoard[2][1],playBoard[2][2]);
        printf("|_____|_____|_____|\n");
		
}

void catcher(int sig)
{
	printf("Sorry...you can quit only after your chance is over! \n");
}

