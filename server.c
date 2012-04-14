							/*Tic Tac Toe Game by Ishan Ankita*/
									/*Server*/ 
#include<ctype.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<signal.h> 
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define SIZE sizeof(struct sockaddr_in) 

int check (char playBoard[][3], int turns);
void catcher(int sig); 
int newsockfd[2]; 
int sockfd;
int points[2];
int x;
int main(void) 
{ 
	char serverRead[2];
	char ans[1];
	int usr=0;
	int ctr=1;
	int row = 0;
	int column = 0;
	int choice=0;
	int turns=0;
	char a[2][40];

        char playBoard [5][3] =   {							// to display the actual game status
			         		{' ',' ',' '},
						{' ',' ',' '},
		       				{' ',' ',' '},
						{' '},
						{' '}
	                          };
	
	struct sockaddr_in server = {AF_INET, 8200, INADDR_ANY}; 
	strcpy(ans,"");
	static struct sigaction act,act2; 
	act.sa_handler = catcher; 
	sigfillset(&(act.sa_mask)); 
	sigaction(SIGPIPE, &act, 0); 
	sigaction(SIGTSTP, &act, 0);
	sigaction(SIGINT, &act, 0);

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
		{ 
		perror("Socket Call Failed"); 
		exit(1); 
		} 

	if ( bind(sockfd, (struct sockaddr *)&server, SIZE) == -1) 
		{ 
		perror("Bind Call Failed"); 
		exit(1); 
		}
	
	printf("Waiting for users to join...\n");

	strcpy(a[0],"Waiting for another user to join");

	while(usr<2)
	{
		if ( listen(sockfd, 5) == -1 ) 
		{ 
			perror("listen call failed\n"); 
			exit(1) ; 
		}
		
		newsockfd[usr] = accept(sockfd, 0, 0);
		usr++;

		if (usr==1)
		{	
			strcpy(a[1],"0");
			write(newsockfd[0],a,sizeof(a));
		}

		printf("No. of users joined: %d\n",usr);
	
		if (usr==2)
		{
			strcpy(a[0],"Let's start!!!");
			strcpy(a[1],"1");
			write(newsockfd[0],a,sizeof(a));
			strcpy(a[1],"2");
			write(newsockfd[1],a,sizeof(a));
		} 	
	}	
	
		if ( fork() == 0) 
		{
			int count=0; 		
			
			while (count==0) 
			{ 	
			
				read(newsockfd[ctr], serverRead, sizeof(serverRead));			
				choice = atoi(serverRead);
				turns++;
				printf("Server side received integer %d from Player %d\n",choice,ctr+1);
				row = --choice/3;
	       			column = choice%3;
				playBoard[row][column] = (ctr==0)?'X':'O';
				int a = check(playBoard, turns);

				if(ctr == 1)
					ctr = 0;
				else
					ctr = 1;
				
				if(a==1)
				{
					strcpy(playBoard[0], "f");
					write(newsockfd[(ctr+1)%2],playBoard,sizeof(playBoard));

					}
					write(newsockfd[ctr],playBoard,sizeof(playBoard)); 
				
				
			}
			
			//close(newsockfd[0]);
			//exit (0);
		} 	
			wait();
			//close(newsockfd[1]);
}

int check (char playBoard[][3], int turns)
{
	  int i;
	  int a=0;
	  char key = ' ';
          points[0]=0;
	  points[1]=0;	
	  // Check Rows
	  for (i=0; i<3;i++)
	  if (playBoard [i][0] == playBoard [i][1] && playBoard [i][0] == playBoard [i][2] && playBoard [i][0] != ' ') key = playBoard [i][0];	
	  // check Columns
	  for (i=0; i<3;i++)
	  if (playBoard [0][i] == playBoard [1][i] && playBoard [0][i] == playBoard [2][i] && playBoard [0][i] != ' ') key = playBoard [0][i];
	  // Check Diagonals
	  if (playBoard [0][0] == playBoard [1][1] && playBoard [1][1] == playBoard [2][2] && playBoard [1][1] != ' ') key = playBoard [1][1];
	  if (playBoard [0][2] == playBoard [1][1] && playBoard [1][1] == playBoard [2][0] && playBoard [1][1] != ' ') key = playBoard [1][1];

	  if (key == 'X')
	  {
	           pointscount(turns);		
		   points[0] = points[0] + x;	
		   printf("Player 1 Wins\n\n");
		   printf("Total Points of Player 1 = %d\n",points[0]);
		   printf("Total Points of Player 2 = %d\n",points[1]);
		   sprintf(playBoard[3], "%d", points[0]);
		   sprintf(playBoard[4], "%d", points[1]); 		
		   printf("Total Points of Player 1 = %s\n",playBoard[3]);
		   printf("Total Points of Player 2 = %s\n",playBoard[4]);		
		 //  write(newsockfd, playBoard, sizeof(playBoard));
		   printf("hello\n");		
		   /*String temp="Player 1 Wins";
		   write(newsockfd[0], temp, sizeof(temp));
		   write(newsockfd[1], temp, sizeof(temp));*/				// to do: even display the final output
		  // close(newsockfd[0]);
		  // close(newsockfd[1]);
		   //exit (0);
		    a=1; 
	  }

	  if (key == 'O')
	  {
		   pointscount(turns); 	
		   points[1] = points[1] + x;	
		   printf("Player 2 Wins\n\n");
		   printf("Total Points of Player 1 = %d\n",points[0]);
		   printf("Total Points of Player 2 = %d\n",points[1]);
		   sprintf(playBoard[3], "%d", points[0]);
		   sprintf(playBoard[4], "%d", points[1]);
		   printf("Total Points of Player 1 = %s\n",playBoard[3]);
		   printf("Total Points of Player 2 = %s\n",playBoard[4]); 				
		  // write(newsockfd, playBoard, sizeof(playBoard));	
		   printf("hello\n");
		  /*String temp="Player 2 Wins";
		   write(newsockfd[0], temp, sizeof(temp));
		   write(newsockfd[1], temp, sizeof(temp));*/
		 //  close(newsockfd[0]);
		 //  close(newsockfd[1]);
		 //  exit (0);
			a=1;
	  }
	return a;
}

int pointscount(int turns)
{
	turns = (turns+1)/2;

	if(turns==3)
	return x=500;
	
	if(turns==4)
	return x=300;
	
	if(turns==5)
	return x=100;

}
void catcher(int sig) 
{ 
	printf("Quitting\n");
	close(sockfd); 
	exit (0); 
}

