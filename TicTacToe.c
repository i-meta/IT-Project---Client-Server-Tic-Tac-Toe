#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int winner = 0;
char playBoard[3][3];
void showLogo();
void mapBoard (char playBoard[][3]);
void check();
int main (void)

	{
	    int player = 0;
	    int winner = 0;
	    int choice = 0;
	    int row = 0;
	    int column = 0;
	    int line = 0;
	    int i=0;	
	    char numberBoard [3][3] = {							// to display positions to choose from
	                 		{'1','2','3'},
                			{'4','5','6'},
               				{'7','8','9'}
                     		    };
	    char playBoard [3][3] = {							// to display the actual game status
	                 		{' ',' ',' '},
					{' ',' ',' '},
               				{' ',' ',' '}
                     		    };
	 
	    showLogo();

	    for (i = 0; i<9 && winner==0; i++)
	    {
		mapBoard(numberBoard);	        
		mapBoard(playBoard);
	        player = i%2 + 1;
	 
	/*         do
	        {
	            printf("\nPlayer %d, Please enter the number of the square where you want to place your %c: ",player,(player==1)?'X':'O');
	            scanf("%d", &choice);		
	 			 
	            row = --choice/3;
	            column = choice%3;
	        }
		while(choice<0 || choice>9 || playBoard [row][column]>'9'|| playBoard [row][column]='X' || playBoard [row][column]='O');
	  */

		for(;;)
	        {
		printf("\nPlayer %d, Please enter the number of the square where you want to place your %c: ",player,(player==1)?'X':'O');
	        scanf("%d", &choice);

		
		row = --choice/3;
	        column = choice%3;
		
		if(choice<0 || choice>9 || playBoard [row][column]>'9'|| playBoard [row][column]=='X' || playBoard [row][column]=='O')
		printf("Invalid Input. Please Enter again.\n");
		
		else
		{
			break;
		}
	        }
		playBoard[row][column] = (player == 1) ? 'X' : 'O';
	   	check(playBoard); 									// check if any player wins or looses
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

void check (char playBoard[][3])
{
	  int i;
	  char key = ' ';

	  // Check Rows
	  for (i=0; i<3;i++)
	  if (playBoard [i][0] == playBoard [i][1] && playBoard [i][0] == playBoard [i][2] && playBoard [i][0] != ' ') key = playBoard [i][0];	
	  // check Columns
	  for (i=0; i<3;i++)
	  if (playBoard [0][i] == playBoard [1][i] && playBoard [0][i] == playBoard [2][i] && playBoard [0][i] != ' ') key = playBoard [0][i];
	  // Check Diagonals
	  if (playBoard [0][0] == playBoard [1][1] && playBoard [1][1] == playBoard [2][2] && playBoard [1][1] != ' ') key = playBoard [1][1];
	  if (playBoard [0][2] == playBoard [1][1] && playBoard [1][1] == playBoard [2][0] && playBoard [1][1] != ' ') key = playBoard [1][1];

	  //Declare Winner if any

	  if (key == 'X')
	  {
	   printf ("Player 1 Wins\n");
	   winner=1;
	   exit (0);
	  }

	  if (key == 'O')
	  {
	   printf ("Player 2 Wins\n	");
	   winner=2;
	   exit (0);
	  }
	
	  	

}


