#include<stdio.h>
#define EMPTY  (char)222

struct TicTacToe
{
 char board[3][3];
 int r, c;//current move
 int playerNumber;
};
typedef struct TicTacToe TicTacToe;

void init(TicTacToe *p)
{
 int i, j;
 for(i =0 ;i< 3; i++)
  for(j=0; j< 3; j++)
   p->board[i][j] = EMPTY;
 
   p->playerNumber = 1;
}

void drawBoard(TicTacToe *p)
{
    int i, j;
    
    for(i =0 ; i< 3; i++)
    {
        printf("\n\n");
        for(j =0 ; j< 3; j++)
        {
            printf("%5c", p->board[i][j]);
        }
    }
}

void input(TicTacToe *p)
{
    printf("\n enter row coordinate (0-2) ");
    scanf("%d", &p->r);
    printf("\n enter column coordinate (0-2) ");
    scanf("%d", &p->c);
}

int validateInput(TicTacToe *p)
{
    if(p->r >=0 && p->r <=2 && p->c >=0 && p->c <=2)
    {
        if(p->board[p->r][p->c] == EMPTY)
            return 1;//true
        else
            return 0;//false
    }
    else
        return 0;//false
 }

int gameOver(TicTacToe *p)
{
    int i, j;
    for(i =0 ; i< 3; i++)
    {
        for(j=0; j< 3; j++)
        {
            if(p->board[i][j] == EMPTY)
                return 0;//false
        }
    }
    return 1;//true
}

void play(TicTacToe *p)
{
    int flag = 0;
    while(!gameOver(p))
    {
        drawBoard(p);
        printf("\nPlayer %d to play ", p->playerNumber);
        input(p);
        if(validateInput(p))
        {
            if(p->playerNumber == 1)
                p->board[p->r][p->c] = 'X';
            else
                p->board[p->r][p->c]= 'O';
            
            if(checkWins(p))
            {
                flag = 1;
                drawBoard(p);
                printf("\n Player %d wins", p->playerNumber);
                break;
            }
            
            p->playerNumber = p->playerNumber ==1?2:1;
            
        }
        else
        {
            printf("\n invalid input ignored ");
            printf("\n same player plays again");
        }
    }//while
    
    if(flag == 0)
        printf("\n Game Over With No Descision");
}

int  checkWins(TicTacToe *p)
{
    char symbol;
    symbol = p->playerNumber == 1?'X':'O';
    
    if(p->board[0][0]== symbol && p->board[0][1] == symbol && p->board[0][2] == symbol)
        return 1;
    if(p->board[1][0]== symbol && p->board[1][1] == symbol && p->board[1][2] == symbol)
        return 1;
    if(p->board[2][0]== symbol && p->board[2][1] == symbol && p->board[2][2] == symbol)
        return 1;
    
    if(p->board[0][0]== symbol && p->board[1][0] == symbol && p->board[2][0] == symbol)
        return 1;
    if(p->board[0][1]== symbol && p->board[1][1] == symbol && p->board[2][1] == symbol)
        return 1;
    if(p->board[0][2]== symbol && p->board[1][2] == symbol && p->board[2][2] == symbol)
        return 1;
    
    if(p->board[0][0]== symbol && p->board[1][1] == symbol && p->board[2][2] == symbol)
        return 1;
    if(p->board[0][2]== symbol && p->board[1][1] == symbol && p->board[2][0] == symbol)
        return 1;
    
    return 0;
    
}

int main()
{
 TicTacToe obj;
 init(&obj);
 play(&obj);
 
 return 0;
}