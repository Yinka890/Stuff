#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//work on AI, and print winner


typedef struct
{
 bool AI;
 bool player;
}
pot;

typedef struct
{
  int AI;
  int player;
}
score;

//prototypes
bool full(void);
bool true_check(void);
bool check_horizontal(int index);
bool check_vertical(int vindex);
bool cross_check(void);
void load_table(void);
void draw(void);

void print_winner(void);

const unsigned int M = 9;
const int n = 3;
pot arr[M];
pot win[n][n];
score horizontal_score[3]={0};
score vertical_score[3]= {0};
score diagonal[2]={0};


      int main(void)
{

printf("You are circle\n");
    //continue until the board is full or someone has won
   while(true_check() && !full())
{
//play the game
           int play_x;
           printf("player 1 position:");
            scanf("%i", &play_x);

      if(!(play_x>=1 && play_x<=9))
      {
            printf("invalid position\n");


      }
      else{

play_x = play_x -1;
//check if position is free then update
         if(!arr[play_x].player && !arr[play_x].AI)
     {


              arr[play_x].player = true;
              load_table();
              true_check();
              draw();
//pass this to function to redraw the board


//if not full and player has not won then play
   if(true_check() && !full())
   {

           printf("player 2 position:");
            scanf("%i", &play_x);

      if(!(play_x>=1 && play_x<=9))
      {
            printf("invalid position\n");


      }
      else{
          play_x = play_x -1;
        if(!arr[play_x].AI && !arr[play_x].player)
        {
            arr[play_x].AI = true;
        }
      }



             load_table();

//draw again
             draw();
    }
    else{
      
      print_winner();
      return 0;
    }
     }

            else
     {
                printf("invalid position\n");

     }


      }

}

//print winner, takes the check functions as input
print_winner();
return 0;


}

//checks if the board is full
bool full(void)
{
   int played_count =0;
         for(int i=0; i<M; i++)
{
      if(arr[i].AI  ||  arr[i].player)
   {
        played_count++;
       if(played_count ==9)
     {
        return true;
     }
   }
}

return false;
}


//checks if anyone has won
bool true_check(void)
{
    for(int i=0; i<3; i++)
    {
        if(!check_horizontal(i))
        {
        return false;
        }

         if(!check_vertical(i))
        {
          return false;
        }
    }

    if(!cross_check())
    {
        return false;
    }

    return true;
}


//function to check if game is done or someone won
//argument should change the arrays
bool check_horizontal(int index)
{
   int AI_count = 0, player_count = 0;
//win condition
    for(int i=0; i<3; i++)
    {
                if(win[index][i].AI)
        {
          AI_count++;
          horizontal_score[index].AI = AI_count;
          if(AI_count ==3)
          {
            return false;
          }
       //another func to check win_count?
       }
            else if(win[index][i].player)
       {
        player_count++;
        horizontal_score[index].player = player_count;
        if(player_count == 3)
        {
            return false;
        }
       }
    }

    return true;

}

bool check_vertical(int vindex)
{

int AI_count = 0, player_count = 0;
//win condition
    for(int i=0; i<3; i++)
    {
                if(win[i][vindex].AI)
        {
          AI_count++;
          vertical_score[vindex].AI = AI_count;
          if(AI_count ==3)
          {
            return false;
          }
       //another func to check win_count?
       }
            else if(win[i][vindex].player)
       {
        player_count++;
        vertical_score[vindex].player = player_count;
        if(player_count ==3)
        {
            return false;
        }
       }
    }
   return true;
}

bool cross_check(void)
{
 int diagonal_ai =0;
 int diagonal_player =0;
  int diagonal_ai2=0;
   int diagonal_player2=0;
//loop here to count
   if(win[0][0].AI  && win[1][1].AI && win[2][2].AI)
   {
    return false;
   }
   else if(win[0][0].player && win[1][1].player && win[2][2].player)
   {
    return false;
   }
   else if(win[0][2].AI  && win[1][1].AI && win[2][0].AI)
   {
    return false;
   }
   else if(win[0][2].player && win[1][1].player && win[2][0].player)
   {
    return false;
   }
   //also check who is winning diagonal
   for(int i=0; i<3; i++)
   {
    if(win[i][i].AI)
    {
      diagonal_ai++;
       diagonal[0].AI = diagonal_ai;
    }
    else if(win[i][i].player)
    {
      diagonal_player++;
      diagonal[0].player = diagonal_player;
    }
   }

   for(int i=0; i<3; i++)
   {
    if(win[i][2-i].AI)
    {
      diagonal_ai2++;
       diagonal[1].AI= diagonal_ai2;
    }
    else if(win[i][2-i].player)
    {
      diagonal_player2++;
      diagonal[1].player= diagonal_player2;
    }
   }


return true;



}




//win condition, 012, 345, 678, 036, 147, 258, 048, 246
void load_table(void)
{


//translate the input to a position on win array
    for(int i=0; i<9; i++)
    {
         if(i<=2)
        {
            win[0][i].AI = arr[i].AI;
            win[0][i].player = arr[i].player;
        }
        else if(i > 2 && i<=5)
        {
          win[1][i-3].AI = arr[i].AI;
          win[1][i-3].player = arr[i].player;
        }
        else
        {
           win[2][i-6].AI = arr[i].AI;
          win[2][i-6].player = arr[i].player;
        }
    }


}


void draw(void)
{
    //takes the array and draws the new board with it
    for(int i=0; i<n; i++)
    {
      for(int j=0; j<n; j++)
      {
        if(win[i][j].AI)
        {
          printf("|_X___");
        }
        else if(win[i][j].player)
        {
          printf("|_O___");
        }
        else{
          printf("|_____");
        }
      }

      printf("\n");
    }

}



//print the winner
void print_winner(void)
{

      for(int i=0; i<3; i++)
{
  if(horizontal_score[i].AI==3)
  {
    printf("Player 2 WON!!!\n");
    return;
  }
  else if(vertical_score[i].AI==3)
  {
    printf("Player 2 WON!!!!\n");
    return;
  }
  else if(i!=2 && diagonal[i].AI==3)
  {
    printf("Player 2 WON!!!\n");
    return;
  }

}

for(int i=0; i<3; i++)
{
  if(horizontal_score[i].player==3 || vertical_score[i].player==3 || (i!=2 && diagonal[i].AI==3))
  {
    printf("Player 1 WON!!!\n");
    return;
  }
}

//either draw or lost
printf("IT'S A DRAW!!!\n");
}