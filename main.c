#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
char board[10][14][10000]; //variable used to modify the board
char RedoCheck[10][14][10000];//variable used to check the redo
char white[10000];//variable to store the white player name
int whitelength;
char black[10000];//variable to store the black player name
int blacklength;
static int counter=0;
static int checkRedo=0;
static int checkmate=0;
static int turn;//turn equals 1 if it's white's turn and 0 if it's black's turn
void printBoard();
void boardGame();//grey represents white square and green represents black square
//CAPITAL dark red LETTERS are the black pieces while small blue letters are white ones
void print();//prints the new board
void clean();//cleans the screen
void copy();//makes a copy of the board for the undo
void WhiteMove();//controls the movement of white pieces
void BlackMove();//controls the movement of black pieces
char ModifyLetter(char c);//exchange the entered numbered with the right one in the array
void Rook(char number1,char number2,char letter1,char letter2,char type2);//rook movement
void Knight(char number1,char number2,char letter1,char letter2,char type2);//Knight movement
void Bishop(char number1,char number2,char letter1,char letter2,char type2);//Bishop movement
void Queen(char number1,char number2,char letter1,char letter2,char type2);//Queen movement
void King(char number1,char number2,char letter1,char letter2,char type2);//King movement
void BlackPawn(char number1,char number2,char letter1,char letter2,char type2);//Black pawn movement
void WhitePawn(char number1,char number2,char letter1,char letter2,char type2);//White pawn movement
void Storing(char type2,char number2,char letter2,char letter1,char number1);//storing dead pieces and eating
void Undo();//undo one move backward
void redo();//redo one move forward
void save();//creates a save file
void load();//loads the saved file
void checkKing();//checks if the king is checked
void checkTheCheck();//checks if the king is safe after the check movement
void staleMate();//checks if the king is stalemated
void checkMate();//check if the king is checkmated
void intro(); //creates an intro to the game
void SetColorAndBackground(int ForgC, int BackC);//changes color of the board
int main()
{
    intro();
    clean();
    boardGame();
    while(checkmate<1)
    {
        WhiteMove();
        if(checkmate==1||checkmate==2)
        {
            break;
        }
        BlackMove();
    }
    if(checkmate==1)
    {
        if (turn==1)
        {
            printf("\nBlack player won!\a");
            PlaySound(TEXT("final.wav"),NULL,SND_SYNC);
            getch();
        }
        else
        {
            printf("\nWhite player won!\a");
            PlaySound(TEXT("final.wav"),NULL,SND_SYNC);
            getch();
        }
    }
    else
    {
            printf("\nStalemate! Game ended with a draw!\a");
            getch();
    }
    return 0;
}
void SetColorAndBackground(int ForgC, int BackC){
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void intro()
{
  printf("\n\n\n\n\n\n\n");
  system("COLOR FC");
  printf("\t\t\t\t  ______ _                        _           ______ \n");
  printf("\t\t\t\t / _____) |                      (_)         / _____)\n");
  printf("\t\t\t\t| /     | | _   ____  ___  ___    _ ____    | /      \n");
  printf("\t\t\t\t| |     | || \\ / _  )/___)/___)  | |  _ \\   | |      \n");
  printf("\t\t\t\t| \\_____| | | ( (/ /|___ |___ |  | | | | |  | \\_____ \n");
  printf("\t\t\t\t \\______)_| |_|\\____|___/(___/   |_|_| |_|   \\______)\n");
  printf("\t\t\t\t\t\t\t\t\t Made by : Pierre and Mina");
  PlaySound(TEXT("intro.wav"),NULL,SND_SYNC);
  printf("\nEnter white's player name: ");
  fgets(white,10000,stdin);
  for(int i=0;i<10000;i++)
  {
      if(white[i]==' '||white[i]=='\0'||white[i]=='\n')
      {
          whitelength=i;
          break;
      }
  }
  while(whitelength==0)
  {
      printf("\nMake sure you entered a name\a");
      getch();
      printf("\nEnter white's player name: ");
  fgets(white,10000,stdin);
  for(int i=0;i<10000;i++)
  {
      if(white[i]==' '||white[i]=='\0'||white[i]=='\n')
      {
          whitelength=i;
          break;
      }
  }

  }
  printf("\nEnter black's player name: ");
  fgets(black,10000,stdin);
  for(int i=0;i<10000;i++)
  {
      if(black[i]==' '||black[i]=='\0'||black[i]=='\n')
      {
          blacklength=i;
          break;
      }
  }
  while(blacklength==0)
  {
      printf("\nMake sure you entered a name\a");
      getch();
      printf("\nEnter black's player name: ");
  fgets(black,10000,stdin);
  for(int i=0;i<10000;i++)
  {
      if(black[i]==' '||black[i]=='\0'||black[i]=='\n')
      {
          blacklength=i;
          break;
      }
  }

  }
}
void boardGame()
{

    board[0][0][counter]='B';
    board[0][1][counter]='L';
    board[0][2][counter]=' ';
    board[0][3][counter]='a';
    board[0][4][counter]='b';
    board[0][5][counter]='c';
    board[0][6][counter]='d';
    board[0][7][counter]='e';
    board[0][8][counter]='f';
    board[0][9][counter]='g';
    board[0][10][counter]='h';
    board[0][12][counter]='W';
    board[0][13][counter]='H';
    board[1][0][counter]=' ';
    board[1][1][counter]=' ';
    board[1][2][counter]='8';
    board[1][3][counter]='R';
    board[1][4][counter]='N';
    board[1][5][counter]='B';
    board[1][6][counter]='Q';
    board[1][7][counter]='K';
    board[1][8][counter]='B';
    board[1][9][counter]='N';
    board[1][10][counter]='R';
    board[1][11][counter]='8';
    board[1][12][counter]=' ';
    board[1][13][counter]=' ';
    board[2][0][counter]=' ';
    board[2][1][counter]=' ';
    board[2][2][counter]='7';
    board[2][3][counter]='P';
    board[2][4][counter]='P';
    board[2][5][counter]='P';
    board[2][6][counter]='P';
    board[2][7][counter]='P';
    board[2][8][counter]='P';
    board[2][9][counter]='P';
    board[2][10][counter]='P';
    board[2][11][counter]='7';
    board[2][12][counter]=' ';
    board[2][13][counter]=' ';
    board[3][0][counter]=' ';
    board[3][1][counter]=' ';
    board[3][2][counter]='6';
    board[3][3][counter]=' ';
    board[3][4][counter]=' ';
    board[3][5][counter]=' ';
    board[3][6][counter]=' ';
    board[3][7][counter]=' ';
    board[3][8][counter]=' ';
    board[3][9][counter]=' ';
    board[3][10][counter]=' ';
    board[3][11][counter]='6';
    board[3][12][counter]=' ';
    board[3][13][counter]=' ';
    board[4][0][counter]=' ';
    board[4][1][counter]=' ';
    board[4][2][counter]='5';
    board[4][3][counter]=' ';
    board[4][4][counter]=' ';
    board[4][5][counter]=' ';
    board[4][6][counter]=' ';
    board[4][7][counter]=' ';
    board[4][8][counter]=' ';
    board[4][9][counter]=' ';
    board[4][10][counter]=' ';
    board[4][11][counter]='5';
    board[4][12][counter]=' ';
    board[4][13][counter]=' ';
    board[5][0][counter]=' ';
    board[5][1][counter]=' ';
    board[5][2][counter]='4';
    board[5][3][counter]=' ';
    board[5][4][counter]=' ';
    board[5][5][counter]=' ';
    board[5][6][counter]=' ';
    board[5][7][counter]=' ';
    board[5][8][counter]=' ';
    board[5][9][counter]=' ';
    board[5][10][counter]=' ';
    board[5][11][counter]='4';
    board[5][12][counter]=' ';
    board[5][13][counter]=' ';
    board[6][0][counter]=' ';
    board[6][1][counter]=' ';
    board[6][2][counter]='3';
    board[6][3][counter]=' ';
    board[6][4][counter]=' ';
    board[6][5][counter]=' ';
    board[6][6][counter]=' ';
    board[6][7][counter]=' ';
    board[6][8][counter]=' ';
    board[6][9][counter]=' ';
    board[6][10][counter]=' ';
    board[6][11][counter]='3';
    board[6][12][counter]=' ';
    board[6][13][counter]=' ';
    board[7][0][counter]=' ';
    board[7][1][counter]=' ';
    board[7][2][counter]='2';
    board[7][3][counter]='p';
    board[7][4][counter]='p';
    board[7][5][counter]='p';
    board[7][6][counter]='p';
    board[7][7][counter]='p';
    board[7][8][counter]='p';
    board[7][9][counter]='p';
    board[7][10][counter]='p';
    board[7][11][counter]='2';
    board[7][12][counter]=' ';
    board[7][13][counter]=' ';
    board[8][0][counter]=' ';
    board[8][1][counter]=' ';
    board[8][2][counter]='1';
    board[8][3][counter]='r';
    board[8][4][counter]='n';
    board[8][5][counter]='b';
    board[8][6][counter]='q';
    board[8][7][counter]='k';
    board[8][8][counter]='b';
    board[8][9][counter]='n';
    board[8][10][counter]='r';
    board[8][11][counter]='1';
    board[8][12][counter]=' ';
    board[8][13][counter]=' ';
    board[9][0][counter]=' ';
    board[9][1][counter]=' ';
    board[9][2][counter]=' ';
    board[9][3][counter]='a';
    board[9][4][counter]='b';
    board[9][5][counter]='c';
    board[9][6][counter]='d';
    board[9][7][counter]='e';
    board[9][8][counter]='f';
    board[9][9][counter]='g';
    board[9][10][counter]='h';
    board[9][12][counter]=' ';
    board[9][13][counter]=' ';




}
void print()
{    int i,j;
    printf("\n\n\n\n");
    for(i=0;i<10;i++)
    {
        printf("\t\t\t\t  ");
        for(j=0;j<14;j++)
        {
            if(j==0||j==2||j==1||i==9||i==0||j==12||j==13||j==11)
            {
                SetColorAndBackground(12,255);

            printf(" %c ",board[i][j][counter]);
            }
            else if((j%2==1&&i%2==1&&j<11)||(j%2==0&&i%2==0&&j<11))
            {
                if(board[i][j][counter]=='P'||board[i][j][counter]=='R'||board[i][j][counter]=='N'||
                   board[i][j][counter]=='B'||board[i][j][counter]=='Q'||board[i][j][counter]=='K')
                   {SetColorAndBackground(20, 200);}
                   else{SetColorAndBackground(17,200);}

             printf(" %c ",board[i][j][counter]);
            }
            else if((j%2==0&&j<11)||(j%2==1&&i%2==0&&j<11))
            {if(board[i][j][counter]=='P'||board[i][j][counter]=='R'||board[i][j][counter]=='N'||
                   board[i][j][counter]=='B'||board[i][j][counter]=='Q'||board[i][j][counter]=='K')
                   {SetColorAndBackground(20, 50);}
                   else{SetColorAndBackground(17,50);};

                printf(" %c ",board[i][j][counter]);
            }


        }
        printf("\n");
    }
    printf("Enter the coordinates to play(e.g:a2a3), press enter 'u' to undo,'r' to redo,'s' to save and 'l' to load");
}
void clean()
{
    system("cls");
}
void WhiteMove()
{
    if (counter==0)
    {
        int i,j;
 for(i=0;i<10;i++){
    for(j=0;j<14;j++){
        RedoCheck[i][j][counter]=board[i][j][counter];
    }
 }
    }
    print();
    turn=1;
    checkMate();
    if(checkmate==1)
    {
        return;
    }
    staleMate();
    if(checkmate==2)
    {
        return;
    }
    checkTheCheck();
    checkKing();
    char letter1,number1,letter2,number2;
    char choice[100000];
    printf("\n");
    for(int i=0;i<whitelength;i++)
    {
        printf("%c",white[i]);
    }
    printf("'s turn: ");
    fgets(choice,100000,stdin);
    if (choice[0]=='u'&&choice[1]=='\n')
    {
        Undo();
    }
     else if (choice[0]=='r'&&choice[1]=='\n')
    {
        redo();
    }
    else if(choice[0]=='s'&&choice[1]=='\n')
    {
        save();
    }
     else if(choice[0]=='l'&&choice[1]=='\n')
    {
        load();
    }
    else
    {
    letter1=choice[0];
    number1=choice[1];
    number1-='0';
    letter2=choice[2];
    number2=choice[3];
    number2-='0';
    if((letter1=='a'||letter1=='b'||letter1=='c'||letter1=='d'||letter1=='e'||letter1=='f'||letter1=='g'||letter1=='h')&&
       (letter2=='a'||letter2=='b'||letter2=='c'||letter2=='d'||letter2=='e'||letter2=='f'||letter2=='g'||letter2=='h'))
    {letter1=ModifyLetter(letter1);
    letter2=ModifyLetter(letter2);}
        else
        {
             printf("\nYou entered a wrong origin character\a");
        getch();
        clean();
        return WhiteMove();
        }
        if((number1==1||number1==2||number1==3||number1==4||number1==5||number1==6||number1==7||number1==8)&&
           (number2==1||number2==2||number2==3||number2==4||number2==5||number2==6||number2==7||number2==8))
        {
            number1=9-number1;
            number2=9-number2;
        }
         else
        {
             printf("\nYou entered a wrong number\a");
        getch();
        clean();
        return WhiteMove();
        }
    char type1,type2;
     type1=board[number1][letter1][counter];
     type2=board[number2][letter2][counter];
     if (type2=='p'||type2=='r'||type2=='n'
        ||type2=='k'||type2=='q'||type2=='b')
     {
         printf("\nyou can't eat your own pieces\a");
         getch();
         clean();
         return WhiteMove();
     }

    if(1<=number1&&number1<=8&&1<=number2&&number2<=8)
    {
        if (type1=='r')
        {
            Rook(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='k')
        {
            King(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='q')
        {
            Queen(number1,number2,letter1,letter2,type2);
            clean();

        }
        else if(type1=='p')
        {
            WhitePawn(number1,number2,letter1,letter2,type2);
            clean();

        }
        else if(type1=='n')
        {
        Knight(number1,number2,letter1,letter2,type2);
        clean();
        }
        else if(type1=='b')
        {
            Bishop(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='P'||type1=='R'||type1=='N'||type1=='B'||type1=='K'||type1=='Q')
        {
            printf("\nYou can't move a black piece\a");
            getch();
            clean();
            return WhiteMove();
        }
        else
        {
            printf("\nYou chose an empty position\a");
            getch();
            clean();
            return WhiteMove();
        }


    }


      else{
        printf("\nYou entered a wrong position number\a");
        getch();
        clean();
        return WhiteMove();
    }
    }
}
void BlackMove()
{
    print();
    turn=0;
    checkMate();
    if(checkmate==1)
    {
        return;
    }
     staleMate();
     if(checkmate==2)
    {
        return;
    }
    checkTheCheck();
    checkKing();
    char letter1,number1,letter2,number2;
    char choice[100000];
    printf("\n");
    for(int i=0;i<blacklength;i++)
    {
        printf("%c",black[i]);
    }
    printf("'s turn: ");
    fgets(choice,100000,stdin);
    if(choice[0]=='u'&&choice[1]=='\n')
    {
        Undo();
    }
    else if (choice[0]=='r'&&choice[1]=='\n')
    {
        redo();
    }
      else if(choice[0]=='s'&&choice[1]=='\n')
    {
        save();
    }
    else if(choice[0]=='l'&&choice[1]=='\n')
    {
        load();
    }
    else
    {
    letter1=choice[0];
    number1=choice[1];
    number1-='0';
    letter2=choice[2];
    number2=choice[3];
    number2-='0';
   if((letter1=='a'||letter1=='b'||letter1=='c'||letter1=='d'||letter1=='e'||letter1=='f'||letter1=='g'||letter1=='h')&&
       (letter2=='a'||letter2=='b'||letter2=='c'||letter2=='d'||letter2=='e'||letter2=='f'||letter2=='g'||letter2=='h'))
    {letter1=ModifyLetter(letter1);
    letter2=ModifyLetter(letter2);}
        else
        {
             printf("\nYou entered a wrong origin character\a");
        getch();
        clean();
        return BlackMove();
        }
    if((number1==1||number1==2||number1==3||number1==4||number1==5||number1==6||number1==7||number1==8)&&
           (number2==1||number2==2||number2==3||number2==4||number2==5||number2==6||number2==7||number2==8))
        {
            number1=9-number1;
            number2=9-number2;
        }
         else
        {
             printf("\nYou entered a wrong number\a");
        getch();
        clean();
        return BlackMove();
        }
    char type1;
    char type2;
     type1=board[number1][letter1][counter];
     type2=board[number2][letter2][counter];
     if (type2=='P'||type2=='R'||type2=='N'
        ||type2=='K'||type2=='Q'||type2=='B')
     {
         printf("\nyou can't eat your own pieces\a");
         getch();
         clean();
         return BlackMove();
     }
    if(1<=number1&&number1<=8&&1<=number2&&number2<=8)
    {
        if (type1=='R')
        {
            Rook(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='K')
        {
            King(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='Q')
        {
            Queen(number1,number2,letter1,letter2,type2);
            clean();

        }
        else if(type1=='P')
        {
            BlackPawn(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='N')
        {
        Knight(number1,number2,letter1,letter2,type2);
        clean();

        }
        else if(type1=='B')
        {
            Bishop(number1,number2,letter1,letter2,type2);
            clean();
        }
        else if(type1=='p'||type1=='r'||type1=='n'||type1=='b'||type1=='k'||type1=='q')
        {
            printf("\nYou can't move a white piece\a");
            getch();
            clean();
            return BlackMove();
        }
        else
        {
            printf("\nYou chose an empty position\a");
            getch();
            clean();
            return BlackMove();
        }

    }
    else{
        printf("\nYou entered a wrong position number\a");
        getch();
        clean();
        return BlackMove();
    }
    }
}
char ModifyLetter(char c)
{
    switch(c){
    case(97):
        c=3;
        break;
    case(98):
        c=4;
        break;
    case(99):
        c=5;
        break;
    case(100):
        c=6;
        break;
    case(101):
        c=7;
        break;
    case(102):
        c=8;
        break;
    case(103):
        c=9;
        break;
    case(104):
        c=10;
        break;
    }
    return c;
}
void Rook(char number1,char number2,char letter1,char letter2,char type2)
{
    if (number1 == number2) {

                if(abs(letter1-letter2)==1)
                {copy();
                    if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
                }
        else if (letter1 < letter2) {
                int i;
            for ( i = letter1 + 1; i < letter2; ++i)
               {

               if (((turn==1&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(letter2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{BlackMove();break;}
                    }}

        } else {
            int i;
            for (i = letter1 - 1; i > letter2; --i)
                {
                    if (((turn==1&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(letter2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
                }
            }

    } else if (letter1 == letter2) {
            if(abs(number1-number2)==1)
                {copy();
                    if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
                }
        else if (number1 < number2) {
                int i;
            for ( i = number1 + 1; i < number2; ++i)
            {
             if (((turn==1&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(number2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
            }
        }
         else {
                int i;
            for ( i = number1-1; i >number2; --i)
            {
                if (((turn==1&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(number2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                                BlackMove();
                                break;
                        }
                    }
            }


         }
    }

     else {
        printf("You entered a wrong coordinates for a rook\a");
                if(turn==1)
                {
                getch();
                clean();
                WhiteMove();
                }
                else
                {
                getch();
                clean();
                BlackMove();
                }
    }
}
void Knight(char number1,char number2,char letter1,char letter2,char type2)
{
    if((abs(letter2 - letter1)==(1) && abs(number2 - number1)==(2))
        ||(abs(letter2 - letter1)==(2) && abs(number2 - number1)==(1)))
        {    copy();
              if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
           Storing(type2,number2,letter2,letter1,number1);
                }
                }


        else
            {
                printf("You entered a wrong coordinates for a knight\a");
                if(turn==1)
                {
                getch();
                clean();
                WhiteMove();
                }
                else
                {
                getch();
                clean();
                BlackMove();
                }
            }

}
void Bishop(char number1,char number2,char letter1,char letter2,char type2)
{
    if(abs(letter2 - letter1)==abs(number2 - number1))
            {
            if(abs(letter1-letter2)==1)
                {copy();
                    if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
                }
                else if ((letter1 < letter2)&&(number1<number2)) {
                int i,j=1;
            for ( i = letter1 + 1; i < letter2; ++i)
               {

                if (((turn==1&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{BlackMove();break;}
                    }
                    }

        } else if ((letter1 < letter2)&&(number1>number2))  {
            int i,j=1;
            for (i = letter1 + 1; i < letter2; ++i)
                {
                    if (((turn==1&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
                }
            }
             else if ((letter1 > letter2)&&(number1>number2)) {
                int i,j=1;
            for ( i = letter1 - 1; i > letter2; --i)
               {

                if (((turn==1&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{BlackMove();break;}
                    }
                    }

        } else if ((letter1 > letter2)&&(number1<number2))  {
            int i,j=1;
            for (i = letter1 - 1; i > letter2; --i)
                {
                    if (((turn==1&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
                }
            }

            }
            else
            {
                printf("You entered a wrong coordinates for a bishop\a");
                if(turn==1)
                {
                getch();
                clean();
                WhiteMove();
                }
                else
                {
                getch();
                clean();
                BlackMove();
                }
            }
}
void Queen(char number1,char number2,char letter1,char letter2,char type2)
{

    if (number1 == number2) {

                if(abs(letter1-letter2)==1)
                {copy();
                    if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
                }
        else if (letter1 < letter2) {
                int i;
            for ( i = letter1 + 1; i < letter2; ++i)
               {

                if (((turn==1&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {copy();
                        if(i==(letter2-1))
                    {
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{BlackMove();break;}
                    }}

        } else {
            int i;
            for ( i = letter1 - 1; i > letter2; --i)
                {
                   if (((turn==1&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(letter2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
                }
            }

    }
    else if (letter1 == letter2) {

                if(abs(number1-number2)==1)
                {copy();
                    if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
                }
        else if (number1 < number2) {
                int i;
            for ( i = number1 + 1; i < number2; ++i)
            {
              if (((turn==1&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(number2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
            }
        }
         else {
                int i;
            for ( i = number1 - 1; i > number2; --i)
            {
               if (((turn==1&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[i][letter1][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        if(i==(number2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                                BlackMove();
                                break;
                        }
                    }
            }


         }
    }
    else if(abs(letter2 - letter1)==abs(number2 - number1))
            {
            if(abs(letter1-letter2)==1)
                {copy();
                    if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
                }
                else if ((letter1 < letter2)&&(number1<number2)) {
                int i,j=1;
            for ( i = letter1 + 1; i < letter2; ++i)
               {

                if (((turn==1&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{BlackMove();break;}
                    }
                    }

        } else if ((letter1 < letter2)&&(number1>number2))  {
            int i,j=1;
            for (i = letter1 + 1; i < letter2; ++i)
                {
                    if (((turn==1&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2-1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
                }
            }
             else if ((letter1 > letter2)&&(number1>number2)) {
                int i,j=1;
            for ( i = letter1 - 1; i > letter2; --i)
               {

                if (((turn==1&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1-j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;

                        }
                        else{BlackMove();break;}
                    }
                    }

        } else if ((letter1 > letter2)&&(number1<number2))  {
            int i,j=1;
            for (i = letter1 - 1; i > letter2; --i)
                {
                    if (((turn==1&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='P'||type2=='R'||
                    type2=='N'||type2=='B'||type2=='Q'))||
                    ((turn==0&&board[number1+j][i][counter] == ' ')&&(type2==' '||type2=='p'||type2=='r'||
                    type2=='n'||type2=='b'||type2=='q')))
                    {
                        j++;
                        if(i==(letter2+1))
                    {copy();
                        if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else{
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
                    }
                    else{
                    printf("\nYou can't bypass your pieces\a");
                        getch();
                        clean();
                        if(turn==1)
                        {
                            WhiteMove();
                            break;
                        }
                        else{
                        BlackMove();
                        break;
                        }
                    }
                }
            }
            }
            else
            {
                printf("You entered a wrong coordinates for a queen\a");
                if(turn==1)
                {
                getch();
                clean();
                WhiteMove();
                }
                else
                {
                getch();
                clean();
                BlackMove();
                }
            }

}
void King(char number1,char number2,char letter1,char letter2,char type2)
{
    if(abs(letter2 - letter1)<=1&&abs(number2 - number1)<=1)
            {    copy();
                  if(type2==' ')
                {
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else
                {
                Storing(type2,number2,letter2,letter1,number1);
                }

            }
            else
            {
                printf("You entered a wrong coordinates for a king\a");
                if(turn==1)
                {
                getch();
                clean();
                WhiteMove();
                }
                else
                {
                getch();
                clean();
                BlackMove();
                }
            }
}
void BlackPawn(char number1,char number2,char letter1,char letter2,char type2)
{
    if ((letter2 == letter1) && ((number2 - number1)==1)
            &&(number1==7)&&type2==' ')
            {
                printf("\nEnter the piece you want to have (make sure it's capital): \a");
                char choice[100000];
                fgets (choice,100000,stdin);
                if(choice[0]=='R'||choice[0]=='N'||choice[0]=='B'||choice[0]=='Q')
                {     copy();
                clean();
                 board[8][letter2][counter]=choice[0];
                 board[7][letter1][counter]=' ';
                 print();
                 }
                 else
                 {
                     printf("\nyou entered a wrong character make sure it's capital \a");
                     getch();
                     clean();
                     BlackMove();
                 }
            }

            else if ((abs(letter2-letter1)==1)&&(number2-number1)==1&&number1==7)
            {
                printf("\nEnter the piece you want to have (make sure it's capital):\a");
                char choice[100000];
                fgets (choice,100000,stdin);
                if(choice[0]=='R'||choice[0]=='N'||choice[0]=='B'||choice[0]=='Q')
                {    copy();
                clean();
                Storing(type2,number2,letter2,letter1,number1);
                 board[8][letter2][counter]=choice[0];
                 board[7][letter1][counter]=' ';
                 print();
                 }
                 else
                 {
                     printf("\nyou entered a wrong character make sure it's capital \a");
                     getch();
                     clean();
                     BlackMove();
                 }

            }
            else if(((letter2 == letter1) && ((number2 - number1)==1))
            ||(((number2-number1)==2)&&number1==2&&(letter2==letter1)))
            {
                if(type2==' ')
                {    copy();
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else
                {
                    printf("\nwrong movement\a");
                    getchar();
                    clean();
                    BlackMove();
                }

            }
            else if ((abs(letter2-letter1)==1)&&(number2-number1)==1)
            {
                if(board[number2][letter2][counter]==' ')
                {
                    printf("\nwrong move\a");
                    getch();
                clean();
                BlackMove();

                }
                else{
                copy();
                Storing(type2,number2,letter2,letter1,number1);
                }

            }

            else
            {
                printf("You entered a wrong coordinates for a pawn\a");
                getch();
                clean();
                BlackMove();
            }
}
void WhitePawn(char number1,char number2,char letter1,char letter2,char type2)
{
    if ((letter2 == letter1) && ((number1 - number2)==1)
            &&(number1==2)&&type2==' ')
            {
                printf("\nEnter the piece you want to have \a");
                char choice[100000];
                fgets (choice,100000,stdin);
                if(choice[0]=='r'||choice[0]=='n'||choice[0]=='b'||choice[0]=='q')
                {    copy();
                clean();
                 board[1][letter2][counter]=choice[0];
                 board[2][letter1][counter]=' ';
                 print();
                 }
                 else
                 {
                     printf("\nyou entered a wrong character make sure it's capital \a");
                     getch();
                     clean();
                     WhiteMove();

                 }
            }

            else if ((abs(letter2-letter1)==1)&&(number1-number2)==1&&number1==2)
            {
                printf("\nEnter the piece you want to have \a");
                char choice[100000];
                fgets (choice,100000,stdin);
                if(choice[0]=='r'||choice[0]=='n'||choice[0]=='b'||choice[0]=='q')
                {    copy();
                clean();
                Storing(type2,number2,letter2,letter1,number1);
                 board[1][letter2][counter]=choice[0];
                 board[2][letter1][counter]=' ';
                 print();
                 }
                 else
                 {
                     printf("\nyou entered a wrong character make sure it's small \a");
                     getch();
                     clean();
                     WhiteMove();

                 }

            }
    else if((letter2 == letter1) && ((number1 - number2)==1)
            ||(number1-number2==2)&&number1==7&&(letter2==letter1))
            {
                 if(type2==' ')
                {    copy();
                    char temp=board[number2][letter2][counter];
                    board[number2][letter2][counter]=board[number1][letter1][counter];
                    board[number1][letter1][counter]=temp;
                }
                else
                {
                    printf("\nwrong movement\a");
                    getchar();
                    clean();
                    WhiteMove();

                }

            }
             else if ((abs(letter2-letter1)==1)&&(number1-number2)==1)
            {
                if(board[number2][letter2][counter]==' ')
                {
                    printf("\nwrong move\a");
                    getch();
                clean();
                WhiteMove();

                }
                else{
                            copy();
                Storing(type2,number2,letter2,letter1,number1);
                }
            }
            else
            {
                printf("You entered a wrong coordinates for a pawn\a");
                getch();
                clean();
                WhiteMove();

            }
}
void Storing(char type2,char number2,char letter2,char letter1,char number1)
{
    clean();

               if(type2=='R')
                {
                    if(board[1][0][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[1][0][counter]='R';
                    }
                    else if(board[8][0][counter]==' ')
                    {
                      board[8][0][counter]='R';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                    else
                    {
                        int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][1][counter]==' ')
                            {
                                 board[i][1][counter]='R';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='N')
                {
                    if(board[2][0][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[2][0][counter]='N';
                    }
                    else if(board[7][0][counter]==' ')
                    {
                      board[7][0][counter]='N';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                    else
                    {
                        int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][1][counter]==' ')
                            {
                                 board[i][1][counter]='N';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='B')
                {
                    if(board[3][0][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[3][0][counter]='B';
                    }
                    else if (board[6][0][counter]==' ')
                    {
                      board[6][0][counter]='B';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                    else
                    {
                        int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][1][counter]==' ')
                            {
                                 board[i][1][counter]='B';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='Q')
                {
                    if(board[4][0][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[4][0][counter]='Q';
                    }
                    else if (board[5][0][counter]==' ')
                    {
                      board[5][0][counter]='Q';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                    else
                    {int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][1][counter]==' ')
                            {
                                 board[i][1][counter]='Q';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                 else if(type2=='P')
                {
                    if(board[1][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[1][1][counter]='P';
                    }
                    else if(board[2][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[2][1][counter]='P';
                    }
                    else if(board[3][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[3][1][counter]='P';
                    }
                    else if(board[4][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[4][1][counter]='P';
                    }
                    else if(board[5][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[5][1][counter]='P';
                    }
                    else if(board[6][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[6][1][counter]='P';
                    }
                    else if(board[7][1][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[7][1][counter]='P';
                    }
                    else
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[8][1][counter]='P';
                    }

                }
                else if(type2=='r')
                {
                    if(board[1][13][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[1][13][counter]='r';
                    }

                    else if (board[8][13][counter]==' ')
                    {
                      board[8][13][counter]='r';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                    else
                    {int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][12][counter]==' ')
                            {
                                 board[i][12][counter]='r';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='n')
                {
                    if(board[2][13][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[2][13][counter]='n';
                    }
                    else if (board[7][13][counter]==' ')
                    {
                      board[7][13][counter]='n';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                      else
                    {
                        int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][12][counter]==' ')
                            {
                                 board[i][12][counter]='n';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='b')
                {
                    if(board[3][13][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[3][13][counter]='b';
                    }
                    else if (board[6][13][counter])
                    {
                      board[6][13][counter]='b';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                      else
                    {
                        int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][12][counter]==' ')
                            {
                                 board[i][12][counter]='b';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='q')
                {
                    if(board[4][13][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[4][13][counter]='q';
                    }
                    else if (board[5][13][counter]==' ')
                    {
                      board[5][13][counter]='q';
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                    }
                      else
                    {int i;
                        for( i=0;i<8;i++)
                        {
                            if (board[i][12][counter]==' ')
                            {
                                 board[i][12][counter]='q';
                                 board[number2][letter2][counter]=board[number1][letter1][counter];
                                 board[number1][letter1][counter]=' ';
                                 break;
                            }
                        }
                    }
                }
                else if(type2=='p')
                {
                    if(board[1][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[1][12][counter]='p';
                    }
                    else if(board[2][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[2][12][counter]='p';
                    }
                    else if(board[3][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[3][12][counter]='p';
                    }
                    else if(board[4][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[4][12][counter]='p';
                    }
                    else if(board[5][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[5][12][counter]='p';
                    }
                    else if(board[6][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[6][12][counter]='p';
                    }
                    else if(board[7][12][counter]==' ')
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[7][12][counter]='p';
                    }
                    else
                    {
                      board[number2][letter2][counter]=board[number1][letter1][counter];
                      board[number1][letter1][counter]=' ';
                      board[8][12][counter]='p';
                    }

                }


}
void Undo()
{
    if(counter==0)
    {
        printf("\nThere isn't any move to undo\a");
        getch();
        clean();
        if(turn==1)
        {
            WhiteMove();
            return;
        }
        else
        {
            BlackMove();
            return;
        }
    }
    else
    {
    clean();
    counter--;
    if(turn==1)
    {
        BlackMove();
        WhiteMove();
    }
    else
    {
        WhiteMove();
        BlackMove();
    }
    }

}
void redo()
{
    if(counter>=checkRedo)
    {
        printf("\nThere isn't any move to redo\a");
        getch();
        clean();
        if(turn==1)
        {
            WhiteMove();
            return;
        }
        else
        {
            BlackMove();
            return;
        }
    }
    else
    {
         int i,j;
 for(i=0;i<10;i++){
    for(j=0;j<14;j++){
        if(board[i][j][counter]!=RedoCheck[i][j][counter+1])
        {
        printf("\nThere isn't any move to redo\a");
        getch();
        clean();
        if(turn==1)
        {
            WhiteMove();
            return;
        }
        else
        {
            BlackMove();
            return;
        }
        }
    }
 }
    clean();
    counter++;
    if(turn==1)
    {
        BlackMove();
        WhiteMove();
    }
    else
    {
        WhiteMove();
        BlackMove();
    }
    }
}
void copy()
{
    counter++;
    int i,j;
 for(i=0;i<10;i++){
    for(j=0;j<14;j++){
        board[i][j][counter]=board[i][j][counter-1];
        RedoCheck[i][j][counter]=board[i][j][counter-1];
    }
 }
 if (counter>checkRedo)
 {
     checkRedo=counter;
 }
}
void save()
{
    FILE * save;
    save=fopen("save.txt","w");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<14;j++)
        {
            fprintf(save,"%c",board[i][j][counter] );
        }
        fprintf(save,"\n");
    }

    fclose(save);
    printf("File saved!\a");
    getch();
    clean();
    if(turn==1)
    {
        WhiteMove();
    }
    else
    {
        BlackMove();
    }
}
void load()
{
    FILE *pFile;
    if(pFile = fopen("save.txt","r"))
    {
    char line[256];
    int i=0,j=0,z=0;
    counter=0;
    while(fgets(line,sizeof(line),pFile))
    {
        while(line[z]!='\0')
        {
         board[i][j][counter]=line[z];
        j++;
        z++;
        }
        i++;
        j=0;
        z=0;
    }
    fclose(pFile);
    clean();
    if (turn==1)
    {
        WhiteMove();
    }
    else
    {
        BlackMove();
    }
    }
    else
    {
        printf("\nNo previous saved file\a");
        getch();
        clean();
        if (turn==1)
    {
        WhiteMove();
    }
    else
    {
        BlackMove();
    }
    }
}
void checkKing()
{
    if (turn==1)
    {
        int i,j;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if (board[i][j][counter]=='k')
                {
                    break;
                }
            }
            if (board[i][j][counter]=='k')
                {
                    break;
                }
        }
        int x=i,y=j;
        if((i-1)>=1&&(i-1)<=8)
        {
            if((j-1)>=3&&(j-1)<=10)
            {
               if(board[i-1][j-1][counter]=='P')
               {
                printf("\nCheck!\a");
               }
           }
           if ((j+1)>=3&&(j+1)<=10)
           {
              if (board[i-1][j+1][counter]=='P')
             {
               printf("\nCheck!\a");
             }
          }
        }
        if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[i-2][j-1][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
         if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='N')
            {
                printf("\nCheck!\a");
            }
        }
        for(i=x+1;i<9;i++)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='R'||board[i][y][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='R'||board[i][y][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        for(i=y+1;i<11;i++)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='R'||board[x][i][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        for(i=y-1;i>2;i--)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='R'||board[x][i][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        int m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='B'||board[i][y+m][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='B'||board[i][y-m][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='B'||board[i][y+m][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='B'||board[i][y-m][counter]=='Q')
        {
            printf("\nCheck!\a");
        }
    }
    else
    {
        int i,j;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if (board[i][j][counter]=='K')
                {
                    break;
                }
            }
            if (board[i][j][counter]=='K')
                {
                    break;
                }
        }
        int x=i,y=j;
        if((i+1)>=1&&(i+1)<=8)
        {
            if((j-1)>=3&&(j-1)<=10)
            {
               if(board[i+1][j-1][counter]=='p')
               {
                printf("\nCheck!\a");
               }
           }
           if ((j+1)>=3&&(j+1)<=10)
           {
              if (board[i+1][j+1][counter]=='p')
             {
               printf("\nCheck!\a");
             }
          }
        }
        if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[i-2][j-1][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='n')
            {
                printf("\nCheck!\a");
            }
        }
        for(i=x+1;i<9;i++)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='r'||board[i][y][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='r'||board[i][y][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        for(i=y+1;i<11;i++)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='r'||board[x][i][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        for(i=y-1;i>2;i--)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='r'||board[x][i][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        int m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='b'||board[i][y+m][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='b'||board[i][y-m][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='b'||board[i][y+m][counter]=='q')
        {
            printf("\nCheck!\a");
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='b'||board[i][y-m][counter]=='q')
        {
            printf("\nCheck!\a");
        }
    }

}
void checkTheCheck()
{
    if (turn==0)
    {
        int i,j;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if (board[i][j][counter]=='k')
                {
                    break;
                }
            }
            if (board[i][j][counter]=='k')
                {
                    break;
                }
        }
        int x=i,y=j;
        if((i-1)>=1&&(i-1)<=8)
        {
            if((j-1)>=3&&(j-1)<=10)
            {
               if(board[i-1][j-1][counter]=='P')
               {
                printf("\nStill Checked!\a");
                getch();
                Undo();
               }
           }
           if ((j+1)>=3&&(j+1)<=10)
           {
              if (board[i-1][j+1][counter]=='P')
             {
               printf("\nStill Checked!\a");
                getch();
                Undo();
             }
          }
        }
        if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[i-2][j-1][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
         if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='N')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        for(i=x+1;i<9;i++)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='R'||board[i][y][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='R'||board[i][y][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        for(i=y+1;i<11;i++)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='R'||board[x][i][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        for(i=y-1;i>2;i--)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='R'||board[x][i][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        int m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='B'||board[i][y+m][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='B'||board[i][y-m][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='B'||board[i][y+m][counter]=='Q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='B'||board[i][y-m][counter]=='Q')
        {
           printf("\nStill Checked!\a");
                getch();
                Undo();
        }
    }
    else
    {
        int i,j;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if (board[i][j][counter]=='K')
                {
                    break;
                }
            }
            if (board[i][j][counter]=='K')
                {
                    break;
                }
        }
        int x=i,y=j;
        if((i+1)>=1&&(i+1)<=8)
        {
            if((j-1)>=3&&(j-1)<=10)
            {
               if(board[i+1][j-1][counter]=='p')
               {
               printf("\nStill Checked!\a");
                getch();
                Undo();
               }
           }
           if ((j+1)>=3&&(j+1)<=10)
           {
              if (board[i+1][j+1][counter]=='p')
             {
              printf("\nStill Checked!\a");
                getch();
                Undo();
             }
          }
        }
        if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[i-2][j-1][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='n')
            {
                printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='n')
            {
               printf("\nStill Checked!\a");
                getch();
                Undo();
            }
        }
        for(i=x+1;i<9;i++)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='r'||board[i][y][counter]=='q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='r'||board[i][y][counter]=='q')
        {
           printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        for(i=y+1;i<11;i++)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='r'||board[x][i][counter]=='q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        for(i=y-1;i>2;i--)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='r'||board[x][i][counter]=='q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        int m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='b'||board[i][y+m][counter]=='q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='b'||board[i][y-m][counter]=='q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='b'||board[i][y+m][counter]=='q')
        {
           printf("\nStill Checked!\a");
                getch();
                Undo();
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='b'||board[i][y-m][counter]=='q')
        {
            printf("\nStill Checked!\a");
                getch();
                Undo();
        }
    }

}
void staleMate()
{

    if (turn==1)
    {
        int i,j;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if(board[i][j][counter]=='r'||board[i][j][counter]=='q')
                {
                    if(i+1>=1&&i+1<=8)
                    {
                        int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }

                        if (board[i+1][j][counter]==' '||board[i+1][j][counter]=='P'||board[i+1][j][counter]=='R'
                            ||board[i+1][j][counter]=='Q'||board[i+1][j][counter]=='N'
                            ||board[i+1][j][counter]=='B')
                        {
                            return;
                        }
                    }
                    if(i-1>=1&&i-1<=8)
                    {
                        int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                         m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }

                        if (board[i-1][j][counter]==' '||board[i-1][j][counter]=='P'
                            ||board[i-1][j][counter]=='R'||board[i-1][j][counter]=='Q'
                            ||board[i-1][j][counter]=='N'||board[i-1][j][counter]=='B')
                        {
                            return;
                        }
                    }
                    if(j-1>=3&&j-1<=10)
                    {int z,h;
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if (board[i][j-1][counter]==' '||board[i][j-1][counter]=='P'
                            ||board[i][j-1][counter]=='R'||board[i][j-1][counter]=='Q'
                            ||board[i][j-1][counter]=='N'||board[i][j-1][counter]=='B')
                        {
                            return;
                        }
                    }
                    if(j+1>=3&&j+1<=10)
                    {
                        int z,h;
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if (board[i][j+1][counter]==' '||board[i][j+1][counter]=='P'
                            ||board[i][j+1][counter]=='R'||board[i][j+1][counter]=='Q'
                            ||board[i][j+1][counter]=='N'||board[i][j+1][counter]=='B')
                        {
                            return;
                        }
                    }

                }
                if (board[i][j][counter]=='b'||board[i][j][counter]=='q')
                {
                    if(i+1>=1&&i+1<=8&&j+1>=3&&j+1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if (board[i+1][j+1][counter]==' '||board[i+1][j+1][counter]=='P'
                            ||board[i+1][j+1][counter]=='R'||board[i+1][j+1][counter]=='Q'
                            ||board[i+1][j+1][counter]=='N'||board[i+1][j+1][counter]=='B')
                        {
                            return;
                        }
                    }
                     if(i+1>=1&&i+1<=8&&j-1>=3&&j-1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if (board[i+1][j-1][counter]==' '||board[i+1][j-1][counter]=='P'
                            ||board[i+1][j-1][counter]=='R'||board[i+1][j-1][counter]=='Q'
                            ||board[i+1][j-1][counter]=='N'||board[i+1][j-1][counter]=='B')
                        {
                            return;
                        }
                    }
                     if(i-1>=1&&i-1<=8&&j+1>=3&&j+1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if (board[i-1][j+1][counter]==' '||board[i-1][j+1][counter]=='P'
                            ||board[i-1][j+1][counter]=='R'||board[i-1][j+1][counter]=='Q'
                            ||board[i-1][j+1][counter]=='N'||board[i-1][j+1][counter]=='B')
                        {
                            return;
                        }
                    }
                     if(i-1>=1&&i-1<=8&&j-1>=3&&j-1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if (board[i-1][j-1][counter]==' '||board[i-1][j-1][counter]=='P'
                            ||board[i-1][j-1][counter]=='R'||board[i-1][j-1][counter]=='Q'
                            ||board[i-1][j-1][counter]=='N'||board[i-1][j-1][counter]=='B')
                        {
                            return;
                        }
                    }
                }
                if(board[i][j][counter]=='n')
                {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                    if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
           {
            if(board[i-2][j-1][counter]=='N'||board[i-2][j-1][counter]=='B'||board[i-2][j-1][counter]=='Q'
               ||board[i-2][j-1][counter]=='R'||board[i-2][j-1][counter]=='P'||board[i-2][j-1][counter]==' ')
            {
                return;
            }
        }
         if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='N'||board[i-1][j-2][counter]=='B'||board[i-1][j-2][counter]=='Q'
               ||board[i-1][j-2][counter]=='R'||board[i-1][j-2][counter]=='P'||board[i-1][j-2][counter]==' ')
            {
                return;
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='N'||board[i+1][j+2][counter]=='B'||board[i+1][j+2][counter]=='Q'
               ||board[i+1][j+2][counter]=='R'||board[i+1][j+2][counter]=='P'||board[i+1][j+2][counter]==' ')
            {
                return;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='N'||board[i+2][j+1][counter]=='B'||board[i+2][j+1][counter]=='Q'
               ||board[i+2][j+1][counter]=='R'||board[i+2][j+1][counter]=='P'||board[i+2][j+1][counter]==' ')
            {
                return;
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='N'||board[i-1][j+2][counter]=='B'||board[i-1][j+2][counter]=='Q'
               ||board[i-1][j+2][counter]=='R'||board[i-1][j+2][counter]=='P'||board[i-1][j+2][counter]==' ')
            {
                return;
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='N'||board[i+1][j-2][counter]=='B'||board[i+1][j-2][counter]=='Q'
               ||board[i+1][j-2][counter]=='R'||board[i+1][j-2][counter]=='P'||board[i+1][j-2][counter]==' ')
            {
                return;
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='N'||board[i-2][j+1][counter]=='B'||board[i-2][j+1][counter]=='Q'
               ||board[i-2][j+1][counter]=='R'||board[i-2][j+1][counter]=='P'||board[i-2][j+1][counter]==' ')
            {
                return;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='N'||board[i+2][j-1][counter]=='B'||board[i+2][j-1][counter]=='Q'
               ||board[i+2][j-1][counter]=='R'||board[i+2][j-1][counter]=='P'||board[i+2][j-1][counter]==' ')
            {
                return;
            }
        }
                }

                if (board[i][j][counter]=='p')
                {
                    if(i-1>=1&&i-1<=8)
                    {
                        int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }

                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='B'||type1=='Q')&&type2=='k'
                           ||(type2=='B'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                     if(board[i-1][j][counter]==' ')
                    {
                        return;
                    }

                    if(j-1>=3&&j-1<=10)
                       {
                           int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                           if(board[i-1][j-1][counter]=='P'||board[i-1][j-1][counter]=='R'
                       ||board[i-1][j-1][counter]=='B'||board[i-1][j-1][counter]=='N'
                       ||board[i-1][j-1][counter]=='Q')
                       {
                           return;
                       }
                       }
                    if(j+1>=3&&j+1<=10)
                        {
                            int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='R'||type1=='Q')&&type2=='k'
                           ||(type2=='R'||type2=='Q')&&type1=='k')
                        {
                            continue;
                        }
                        }
                            if(board[i-1][j+1][counter]=='P'
                       ||board[i-1][j+1][counter]=='B'||board[i-1][j+1][counter]=='N'
                       ||board[i-1][j+1][counter]=='Q'||board[i-1][j+1][counter]=='R')
                    {
                     return;
                    }}}
                }
            }
        }
        int right=1,left=1,bottom=1,up=1,upright=1,lowright=1,upleft=1,lowleft=1;
        int flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if (board[i][j][counter]=='k')
                {
                    break;
                }
            }
            if (board[i][j][counter]=='k')
                {
                    break;
                }
        }
        int x=i,y=j;

        if((i-1)>=1&&(i-1)<=8)//checks the upper place
        {if(board[i-1][j][counter]=='P'||board[i-1][j][counter]=='B'||board[i-1][j][counter]=='N'||board[i-1][j][counter]==' ')
            {int z=x-1;

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='R'&&board[x][i][counter]!='Q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='R'&&board[x][i][counter]!='Q')
        {
            flag2=0;
        }
        int m=1;
        temp=temp|flag1|flag2;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q'&&board[i][y+m][counter]!='P')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q'&&board[i][y-m][counter]!='P')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q'&&board[i][y+m][counter]!='P')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q'&&board[i][y-m][counter]!='P')
        {
            flag4=0;
        }
        up=temp|flag1|flag2|flag3|flag4;
        }}
        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((x+1)>=1&&(x+1)<=8)//checks the lower place
        {if(board[x+1][j][counter]=='P'||board[x+1][j][counter]=='B'||board[x+1][j][counter]=='N'||board[x+1][j][counter]==' ')
            {int z=x+1;

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag2=0;
        }
        temp=temp|flag1|flag2;
        int m=1;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q'&&board[i][y+m][counter]!='P')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q'&&board[i][y-m][counter]!='P')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q'&&board[i][y+m][counter]!='P')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q'&&board[i][y-m][counter]!='P')
        {
            flag4=0;
        }
        bottom=flag1|flag2|flag3|flag4|temp;
        }}
        i=x;
         flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
           if((j-1)>=3&&(j-1)<=10)//checks the left place
        {if(board[i][j-1][counter]=='P'||board[i][j-1][counter]=='B'||board[i-1][j][counter]=='N'||board[i][j-1][counter]==' ')
            {int z=y-1;
        if((((i-2)>=1&&(i-2)<=8)&&((z-1)>=3&&(z-1)<=10)))
        {
            if(board[i-2][z-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((i-1)>=1&&(i-1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i-1][z-2][counter]!='N')
            {
                flag2=0;
            }
        }else
        {
            flag2=0;
        }
        if (((i+1)>=1&&(i+1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i+1][z+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i+2][z+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((i-1)>=1&&(i-1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i-1][z+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((i+1)>=1&&(i+1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i+1][z-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((i-2)>=1&&(i-2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i-2][z+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if(board[i+2][z-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag2=0;
        }
        temp=temp|flag1|flag2;
        int m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        temp=flag1|flag2;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q'&&board[i][z+m][counter]!='P')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='B'&&board[i][z-m][counter]!='Q'&&board[i][z-m][counter]!='P')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q'&&board[i][z+m][counter]!='P')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]=='B'&&board[i][z-m][counter]=='Q'&&board[i][z-m][counter]!='P')
        {
            flag4=0;
        }
        left=temp|flag1|flag2|flag3|flag4;

        }}
       i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((j+1)>=3&&(j+1)<=10)//checks the right place
        {if(board[i][j+1][counter]=='P'||board[i][j+1][counter]=='B'||board[i+1][j][counter]=='N'||board[i][j+1][counter]==' ')
           {int z=y+1;
        if((((z-2)>=3&&(z-2)<=10)&&((i-1)>=1&&(i-1)<=8)))
        {
            if(board[i-1][z-2][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=3&&(z-1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z-1][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=3&&(z+1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z+1][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z+2][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=3&&(z-1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z-1][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=3&&(z+1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z+1][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=3&&(z-2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z-2][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i-1)>=1&&(i-1)<=8))
        {
            if(board[i-1][z+2][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag2=0;
        }
        int m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        temp=temp|flag1|flag2;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q'&&board[i][z+m][counter]!='P')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='B'&&board[i][z-m][counter]!='Q'&&board[i][z-m][counter]!='P')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q'&&board[i][z+m][counter]!='P')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='B'&&board[i][z-m][counter]!='Q'&&board[i][z-m][counter]!='P')
        {
            flag4=0;
        }
        right=temp|flag1|flag2|flag3|flag4;
        }}
        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j-1)>=3&&(j-1)<=10&&(x-1)>=1&&(x-1)<=8)//checks left upper place
            {if(board[i-1][j-1][counter]=='R'||board[i-1][j-1][counter]=='N'||board[i-1][j-1][counter]==' ')
                {int z=i-1,h=j-1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag8=0;
        }
         upleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j+1)>=3&&(j+1)<=10&&(x-1)>=1&&(x-1)<=8)//checks right upper place
            {if(board[i-1][j+1][counter]=='R'||board[i-1][j+1][counter]=='N'||board[i-1][j+1][counter]==' ')
                {int z=i-1,h=j+1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag8=0;
        }
         upright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j-1)>=3&&(j-1)<=10&&(x+1)>=1&&(x+1)<=8)//checks left lower place
            {if(board[i+1][j-1][counter]=='R'||board[i+1][j-1][counter]=='N'||board[i+1][j-1][counter]=='P'||board[i+1][j-1][counter]==' ')
                {int z=i+1,h=j-1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag8=0;
        }
        lowleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
            flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        i=x;
            if((j+1)>=3&&(j+1)<=10&&(x+1)>=1&&(x+1)<=8)//checks right lower place
            {if(board[i+1][j+1][counter]=='R'||board[i+1][j][counter]=='N'||board[i+1][j][counter]=='P'||board[i+1][j+1][counter]==' ')
                {int z=i+1,h=j-1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q'&&board[i][h+m][counter]!='P')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q'&&board[i][h-m][counter]!='P')
        {
            flag8=0;
        }
        lowright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        }
            }

        if((lowright==1)&&(lowleft==1)&&(upright==1)&&(upleft==1)&&(left==1)&&(right==1)&&(up==1)&&(bottom==1))
        {
            checkmate=2;
        }
    }
    else
    {
        int i,j;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if(board[i][j][counter]=='R'||board[i][j][counter]=='Q')
                {
                    if(i+1>=1&&i+1<=8)
                    {
                        int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }

                        if (board[i+1][j][counter]==' '||board[i+1][j][counter]=='p'||board[i+1][j][counter]=='r'
                            ||board[i+1][j][counter]=='q'||board[i+1][j][counter]=='n'
                            ||board[i+1][j][counter]=='b')
                        {
                            return;
                        }
                    }
                    if(i-1>=1&&i-1<=8)
                    {
                        int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                         m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }

                        if (board[i-1][j][counter]==' '||board[i-1][j][counter]=='p'
                            ||board[i-1][j][counter]=='r'||board[i-1][j][counter]=='q'
                            ||board[i-1][j][counter]=='n'||board[i-1][j][counter]=='b')
                        {
                            return;
                        }
                    }
                    if(j-1>=3&&j-1<=10)
                    {int z,h;
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if (board[i][j-1][counter]==' '||board[i][j-1][counter]=='p'
                            ||board[i][j-1][counter]=='r'||board[i][j-1][counter]=='q'
                            ||board[i][j-1][counter]=='n'||board[i][j-1][counter]=='b')
                        {
                            return;
                        }
                    }
                    if(j+1>=3&&j+1<=10)
                    {
                        int z,h;
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if (board[i][j+1][counter]==' '||board[i][j+1][counter]=='p'
                            ||board[i][j+1][counter]=='r'||board[i][j+1][counter]=='q'
                            ||board[i][j+1][counter]=='n'||board[i][j+1][counter]=='b')
                        {
                            return;
                        }
                    }

                }
                if (board[i][j][counter]=='B'||board[i][j][counter]=='Q')
                {
                    if(i+1>=1&&i+1<=8&&j+1>=3&&j+1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[z][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if (board[i+1][j+1][counter]==' '||board[i+1][j+1][counter]=='p'
                            ||board[i+1][j+1][counter]=='r'||board[i+1][j+1][counter]=='q'
                            ||board[i+1][j+1][counter]=='n'||board[i+1][j+1][counter]=='b')
                        {
                            return;
                        }
                    }
                     if(i+1>=1&&i+1<=8&&j-1>=3&&j-1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if (board[i+1][j-1][counter]==' '||board[i+1][j-1][counter]=='p'
                            ||board[i+1][j-1][counter]=='r'||board[i+1][j-1][counter]=='q'
                            ||board[i+1][j-1][counter]=='n'||board[i+1][j-1][counter]=='b')
                        {
                            return;
                        }
                    }
                     if(i-1>=1&&i-1<=8&&j+1>=3&&j+1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if (board[i-1][j+1][counter]==' '||board[i-1][j+1][counter]=='p'
                            ||board[i-1][j+1][counter]=='r'||board[i-1][j+1][counter]=='q'
                            ||board[i-1][j+1][counter]=='n'||board[i-1][j+1][counter]=='b')
                        {
                            return;
                        }
                    }
                     if(i-1>=1&&i-1<=8&&j-1>=3&&j-1<=10)
                    {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if (board[i-1][j-1][counter]==' '||board[i-1][j-1][counter]=='p'
                            ||board[i-1][j-1][counter]=='r'||board[i-1][j-1][counter]=='q'
                            ||board[i-1][j-1][counter]=='n'||board[i-1][j-1][counter]=='b')
                        {
                            return;
                        }
                    }
                }
                if(board[i][j][counter]=='N')
                {int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        if(i-1>=1&&i-1<9&&i+1>=1&&i+1<9)
                        {for(z=i-1;z>=3;z--)
                        {
                            if(board[z][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=i+1;h>11;h++)
                        {
                            if(board[h][j][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[z][j][counter];
                        char type2=board[h][j][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                    if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
           {
            if(board[i-2][j-1][counter]=='n'||board[i-2][j-1][counter]=='b'||board[i-2][j-1][counter]=='q'
               ||board[i-2][j-1][counter]=='r'||board[i-2][j-1][counter]=='p'||board[i-2][j-1][counter]==' ')
            {
                return;
            }
        }
         if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='n'||board[i-1][j-2][counter]=='b'||board[i-1][j-2][counter]=='q'
               ||board[i-1][j-2][counter]=='r'||board[i-1][j-2][counter]=='p'||board[i-1][j-2][counter]==' ')
            {
                return;
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='n'||board[i+1][j+2][counter]=='b'||board[i+1][j+2][counter]=='q'
               ||board[i+1][j+2][counter]=='r'||board[i+1][j+2][counter]=='p'||board[i+1][j+2][counter]==' ')
            {
                return;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='n'||board[i+2][j+1][counter]=='b'||board[i+2][j+1][counter]=='q'
               ||board[i+2][j+1][counter]=='r'||board[i+2][j+1][counter]=='p'||board[i+2][j+1][counter]==' ')
            {
                return;
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='n'||board[i-1][j+2][counter]=='b'||board[i-1][j+2][counter]=='q'
               ||board[i-1][j+2][counter]=='r'||board[i-1][j+2][counter]=='p'||board[i-1][j+2][counter]==' ')
            {
                return;
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='n'||board[i+1][j-2][counter]=='b'||board[i+1][j-2][counter]=='q'
               ||board[i+1][j-2][counter]=='r'||board[i+1][j-2][counter]=='p'||board[i+1][j-2][counter]==' ')
            {
                return;
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='n'||board[i-2][j+1][counter]=='b'||board[i-2][j+1][counter]=='q'
               ||board[i-2][j+1][counter]=='r'||board[i-2][j+1][counter]=='p'||board[i-2][j+1][counter]==' ')
            {
                return;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='n'||board[i+2][j-1][counter]=='b'||board[i+2][j-1][counter]=='q'
               ||board[i+2][j-1][counter]=='r'||board[i+2][j-1][counter]=='p'||board[i+2][j-1][counter]==' ')
            {
                return;
            }
        }
                }

                if (board[i][j][counter]=='P')
                {
                    if(i+1>=1&&i+1<=8)
                    {
                        int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        int m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i+m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i+m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i-m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i-m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                        m=1;
                        if(j+1>=3&&j+1<=10&&j-1>=3&&j-1<=10)
                        {
                            for(z=j-1;z>=3;z--)
                        {
                            if(board[i-m][z][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }
                        char type1=board[i-m][z][counter];
                        m=1;
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i+m][h][counter]!=' ')
                            {
                                break;
                            }
                            m++;
                        }

                        char type2=board[i+m][h][counter];
                        if((type1=='b'||type1=='q')&&type2=='K'
                           ||(type2=='b'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                     if(board[i+1][j][counter]==' ')
                    {
                        return;
                    }

                    if(j-1>=3&&j-1<=10)
                       {
                           int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                           if(board[i+1][j-1][counter]=='p'||board[i+1][j-1][counter]=='r'
                       ||board[i+1][j-1][counter]=='b'||board[i+1][j-1][counter]=='n'
                       ||board[i+1][j-1][counter]=='q')
                       {
                           return;
                       }
                       }
                    if(j+1>=3&&j+1<=10)
                        {
                            int z,h;
                        if(j-1>=3&&j-1<11&&j+1>=3&&j+1<11)
                        {for(z=j-1;z>=3;z--)
                        {
                            if(board[i][z][counter]!=' ')
                            {
                                break;
                            }
                        }
                        for(h=j+1;h>11;h++)
                        {
                            if(board[i][h][counter]!=' ')
                            {
                                break;
                            }
                        }
                        char type1=board[i][z][counter];
                        char type2=board[i][h][counter];
                        if((type1=='r'||type1=='q')&&type2=='K'
                           ||(type2=='r'||type2=='q')&&type1=='K')
                        {
                            continue;
                        }
                        }
                            if(board[i+1][j+1][counter]=='p'
                       ||board[i+1][j+1][counter]=='b'||board[i+1][j+1][counter]=='n'
                       ||board[i+1][j+1][counter]=='q'||board[i+1][j+1][counter]=='r')
                    {
                     return;
                    }}}
                }
            }
        }
        int right=1,left=1,bottom=1,up=1,upright=1,lowright=1,upleft=1,lowleft=1;
        int flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=1;i<9;i++)
        {
            for( j=3;j<11;j++)
            {
                if (board[i][j][counter]=='K')
                {
                    break;
                }
            }
            if (board[i][j][counter]=='K')
                {
                    break;
                }
        }
         int x=i,y=j;

        if((i-1)>=1&&(i-1)<=8)//checks the upper place
        {if(board[i-1][j][counter]=='p'||board[i-1][j][counter]=='b'||board[i-1][j][counter]=='n'||board[i-1][j][counter]==' ')
            {int z=x-1;

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='r'&&board[x][i][counter]!='q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='r'&&board[x][i][counter]!='q')
        {
            flag2=0;
        }
        int m=1;
        temp=temp|flag1|flag2;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q'&&board[i][y+m][counter]!='p')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q'&&board[i][y-m][counter]!='p')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q'&&board[i][y+m][counter]!='p')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q'&&board[i][y-m][counter]!='p')
        {
            flag4=0;
        }
        up=temp|flag1|flag2|flag3|flag4;
        }}

        i=x;


        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;

        if((x+1)>=1&&(x+1)<=8)//checks the lower place
        {if(board[x+1][j][counter]=='p'||board[x+1][j][counter]=='b'||board[x+1][j][counter]=='n'||board[x+1][j][counter]==' ')
            {int z=x+1;

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag2=0;
        }
        temp=temp|flag1|flag2;
        int m=1;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q'&&board[i][y+m][counter]!='p')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q'&&board[i][y-m][counter]!='p')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q'&&board[i][y+m][counter]!='p')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q'&&board[i][y-m][counter]!='p')
        {
            flag4=0;
        }
        bottom=flag1|flag2|flag3|flag4|temp;
        }}

        i=x;

         flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;

            if((j-1)>=3&&(j-1)<=10)//checks the left place
        {if(board[i][j-1][counter]=='p'||board[i][j-1][counter]=='b'||board[i-1][j][counter]=='n'||board[i][j-1][counter]==' ')
            {int z=y-1;
        if((((i-2)>=1&&(i-2)<=8)&&((z-1)>=3&&(z-1)<=10)))
        {
            if(board[i-2][z-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((i-1)>=1&&(i-1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i-1][z-2][counter]!='n')
            {
                flag2=0;
            }
        }else
        {
            flag2=0;
        }
        if (((i+1)>=1&&(i+1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i+1][z+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i+2][z+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((i-1)>=1&&(i-1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i-1][z+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((i+1)>=1&&(i+1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i+1][z-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((i-2)>=1&&(i-2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i-2][z+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if(board[i+2][z-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag2=0;
        }
        temp=temp|flag1|flag2;
        int m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        temp=flag1|flag2;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q'&&board[i][z+m][counter]!='p')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='b'&&board[i][z-m][counter]!='q'&&board[i][z-m][counter]!='p')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q'&&board[i][z+m][counter]!='p')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]=='b'&&board[i][z-m][counter]=='q'&&board[i][z-m][counter]!='p')
        {
            flag4=0;
        }
        left=temp|flag1|flag2|flag3|flag4;

        }


       i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;

        if((j+1)>=3&&(j+1)<=10)//checks the right place
        {if(board[i][j+1][counter]=='p'||board[i][j+1][counter]=='b'||board[i+1][j][counter]=='n'||board[i][j+1][counter]==' ')
           {int z=y+1;
        if((((z-2)>=3&&(z-2)<=10)&&((i-1)>=1&&(i-1)<=8)))
        {
            if(board[i-1][z-2][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=3&&(z-1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z-1][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=3&&(z+1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z+1][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z+2][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=3&&(z-1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z-1][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=3&&(z+1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z+1][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=3&&(z-2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z-2][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i-1)>=1&&(i-1)<=8))
        {
            if(board[i-1][z+2][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag2=0;
        }
        int m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        temp=temp|flag1|flag2;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q'&&board[i][z+m][counter]!='p')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='b'&&board[i][z-m][counter]!='q'&&board[i][z-m][counter]!='p')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q'&&board[i][z+m][counter]!='p')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='b'&&board[i][z-m][counter]!='q'&&board[i][z-m][counter]!='p')
        {
            flag4=0;
        }
        right=temp|flag1|flag2|flag3|flag4;
        }}


        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((j-1)>=3&&(j-1)<=10&&(x-1)>=1&&(x-1)<=8)//checks left upper place
            {if(board[i-1][j-1][counter]=='p'||board[i-1][j-1][counter]=='r'||board[i-1][j-1][counter]=='n'||board[i-1][j-1][counter]==' ')
                {int z=i-1,h=j-1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag8=0;
        }
         upleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}


        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((j+1)>=3&&(j+1)<=10&&(x-1)>=1&&(x-1)<=8)//checks right upper place
            {if(board[i-1][j+1][counter]=='p'||board[i-1][j+1][counter]=='r'||board[i-1][j+1][counter]=='n'||board[i-1][j+1][counter]==' ')
                {int z=i-1,h=j+1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag8=0;
        }
         upright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}


        i=x;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((j-1)>=3&&(j-1)<=10&&(x+1)>=1&&(x+1)<=8)//checks left lower place
            {if(board[i+1][j-1][counter]=='r'||board[i+1][j-1][counter]=='n'||board[i+1][j-1][counter]==' ')
                {int z=i+1,h=j-1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag8=0;
        }
        lowleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}

            flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;

        i=x;

        if((j+1)>=3&&(j+1)<=10&&(x+1)>=1&&(x+1)<=8)//checks right lower place
            {if(board[i+1][j+1][counter]=='r'||board[i+1][j][counter]=='n'||board[i+1][j+1][counter]==' ')
                {int z=i+1,h=j-1;
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        int m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q'&&board[i][h+m][counter]!='p')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q'&&board[i][h-m][counter]!='p')
        {
            flag8=0;
        }
        lowright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}


        if((lowright==1)&&(lowleft==1)&&(upright==1)&&(upleft==1)&&(left==1)&&(right==1)&&(up==1)&&(bottom==1))
        {
            checkmate=2;
        }
    }}
}
void checkMate()
{
      if (turn==1)
    {
        int i,j,check=0,z,h,xKing,yKing,m=1;
        char type1=' ',type2;
        for(xKing=1;xKing<9;xKing++)
        {
            for( yKing=3;yKing<11;yKing++)
            {
                if (board[xKing][yKing][counter]=='k')
                {
                    break;
                }
            }
            if (board[xKing][yKing][counter]=='k')
                {
                    break;
                }
        }
        int x=xKing,y=yKing;
        i=x;j=y;
        if((i-1)>=1&&(i-1)<=8)
        {
            if((j-1)>=3&&(j-1)<=10)
            {
               if(board[i-1][j-1][counter]=='P')
               {
                check=1,z=i-1,h=j-1;
               }
           }
           if ((j+1)>=3&&(j+1)<=10)
           {
              if (board[i-1][j+1][counter]=='P')
             {
               check=1,z=i-1,h=j+1;
             }
          }
        }
        if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[i-2][j-1][counter]=='N')
            {
               check=1,z=i-2,h=j-1;
            }
        }
         if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='N')
            {
                check=1,z=i-1,h=j-2;
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='N')
            {
               check=1,z=i+1,h=j+2;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='N')
            {
                check=1,z=i+2,h=j+1;
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='N')
            {
                check=1,z=i-1,h=j+2;
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='N')
            {
                check=1,z=i+1,h=j-2;
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='N')
            {
               check=1,z=i-2,h=j+1;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='N')
            {
                check=1,z=i+2,h=j-1;
            }
        }
        for(i=x+1;i<9;i++)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='R'||board[i][y][counter]=='Q')
        {
            check=1,z=i,h=y;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='R'||board[i][y][counter]=='Q')
        {
            check=1,z=i,h=y;
        }
        for(i=y+1;i<11;i++)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='R'||board[x][i][counter]=='Q')
        {
            check=1,z=x,h=i;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='R'||board[x][i][counter]=='Q')
        {
            check=1,z=x,h=i;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='B'||board[i][y+m][counter]=='Q')
        {
            check=1,z=i,h=y+m;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='B'||board[i][y-m][counter]=='Q')
        {
            check=1,z=i,h=y-m;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='B'||board[i][y+m][counter]=='Q')
        {
           check=1,z=i,h=y+m;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='B'||board[i][y-m][counter]=='Q')
        {
            check=1,z=i,h=y-m;
        }
        if(check==0)
        {
            return;
        }
        type2=board[z][h][counter];//type 2 is the piece that causes the check
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                type1=board[i][h][counter];
                break;
            }
        }
            if(type1=='r'||type1=='q')
            {
                return;
            }
            type1=' ';
            for(i=z-1;i>=1;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                type1=board[i][h][counter];
                break;
            }
        }
            if(type1=='r'||type1=='q')
            {
                return;
            }
            type1=' ';
            for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                type1=board[z][i][counter];
                break;
            }
        }
            if(type1=='r'||type1=='q')
            {
                return;
            }
            type1=' ';
            for(i=h-1;i>=3;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                type1=board[z][i][counter];
                break;
            }
        }
            if(type1=='r'||type1=='q')
            {
                return;
            }
            type1=' ';
             m=1;
            for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                type1=board[i][h-m][counter];
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        m=1;
        if(type1=='b'||type1=='q')
        {
            return;
        }
        type1=' ';
           for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                type1=board[i][h+m][counter];
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        m=1;
        if(type1=='b'||type1=='q')
        {
            return;
        }
        type1=' ';
           for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                type1=board[i][h-m][counter];
                break;
            }
            m++;
            }
        }m=1;
            if(type1=='b'||type1=='q')
        {
            return;
        }
        type1=' ';
           for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                type1=board[i][h+m][counter];
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(type1=='b'||type1=='q')
        {
            return;
        }
        type1=' ';
        if(((z+1)>=2&&(z+1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z+1][h-1][counter]=='p')
            {
                return;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z+1][h+1][counter]=='p')
            {
                return;
            }
        }
            if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]=='n')
            {
                return;
            }
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]=='n')
            {
                return;
            }
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]=='n')
            {
                return;
            }
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]=='n')
            {
                return;
            }
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]=='n')
            {
                return;
            }
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]=='n')
            {
                return;
            }
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]=='n')
            {
                return;
            }
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]=='n')
            {
                return;
            }
        }
        int u1=1,u2=1,u3=1,u4=1,u5=1,u6=1,u7=1,u8=1,u9=1;
        if((abs(h-yKing)>1&&abs(z-xKing)==0)
           ||abs(z-xKing)>1&&abs(h-yKing)==0)
        {if(type2=='R'||type2=='Q')
        {
            for(int o=1;o<9;o++)
        {
            for(int p=3;p<11;p++)
            {
                if (board[o][p][counter]=='p')
                {
                    if(xKing==z)
                    {
                        if(o-z==1&&o>z&&board[o-1][p][counter]==' ')
                        {
                            u1=0;
                        }
                    }
                }
                if (board[o][p][counter]=='r'||board[o][p][counter]=='q')
                {
                    if(xKing==z)
                    {
                        if(o>z)
                        { int w;
                            for(w=o-1;w>=z;w--)
                            {
                                if(board[w][p][counter]!=' ')
                                {
                                    break;
                                }
                            }
                            if(w==z-1)
                            {
                                u2=0;
                            }
                        }
                        else if (z>o)
                        { int w;
                            for(w=o+1;w>=z;w++)
                            {
                                if(board[w][p][counter]!=' ')
                                {
                                    break;
                                }

                        }
                        if(w==z+1)
                        {
                            u3=0;
                        }
                    }
                }
                else if(yKing==h)
                {
                     if(p>h)
                        { int w;
                            for(w=p-1;w>=h;w--)
                            {
                                if(board[o][w][counter]!=' ')
                                {
                                    break;
                                }
                            }
                            if(w==h-1)
                            {
                                u4=0;
                            }
                        }
                        else if(p<h)
                        { int w;
                            for(w=p-1;w<=h;w++)
                            {
                                if(board[o][w][counter]!=' ')
                                {
                                    break;
                                }
                            }
                            if(w==h+1)
                            {
                                u5=0;
                            }
                        }
                }
            }
            if(board[o][p][counter]=='b'||board[o][p][counter]=='q')
            { int b=1;
                if(p>h)
                        { int w;
                        for(w=p-1;w>=h;w--)
                            {
                                if(o-b>=3&&o-b<=10)
                                {if(board[o-b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }if((o-b>z&&o-b<xKing)||(o-b<z&&o-b>xKing))
                            {if(w==h-1)
                            {
                                u6=0;
                            }}
                            b=1;
                            for(w=p+1;w>=h;w--)
                            {
                                if(o+b>=3&&o+b<=10)
                                {if(board[o+b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }if((o+b>z&&o+b<xKing)||(o+b<z&&o+b>xKing))
                            {if(w==h-1)
                            {
                                u7=1;
                            }}}
                    b=1;
                    if(p<h)
                        { int w;
                        if(o>z)
                            {for(w=p+1;w>=h;w++)
                            {
                                if(o-b>=3&&o-b<=10)
                                {if(board[o-b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }
                            if((o-b>z&&o-b<xKing)||(o-b<z&&o-b>xKing))
                            {if(w==h+1)
                            {
                                u8=0;
                            }}
                            b=1;
                            if(o<z)
                            {for(w=p+1;w>=h;w++)
                            {
                                if(o+b>=3&&o+b<=10)
                                {if(board[o-b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }
                            if((o+b>z&&o+b<xKing)||(o+b<z&&o+b>xKing))
                            {if(w==h+1)
                            {
                                u9=0;
                            }}
                        }
                        }
            }

        }
        }
        }
        }
       if(u1==0){return;}else if(u2==0){return;}else if(u3==0){return;} else if(u4==0){return;}
        if(u5==0){return;}else if(u6==0){return;}else if(u7==0){return;} else if(u8=0){return;}else if(u9=0){return;}}
        u1=1,u2=1,u3=1,u4=1;
         if(abs(z-xKing)==abs(h-yKing)&&abs(z-xKing)>1)
        {
        if(type2=='Q'||type2=='B')
        {

        for(int o=1;o<9;o++)
        {
            for(int p=3;p<11;p++)
            {if((z-xKing==h-yKing)&&z-xKing>0)
            {
                if (board[o][p][counter]=='p')
                {
                    if(o-z+1==p-h&&board[o-1][p][counter]==' ')
                    {
                        u1=0;
                    }
                }
            }
            if((z-xKing==yKing-h)&&z-xKing>0)
            {
                if (board[o][p][counter]=='p')
                {
                    if(z-o+1==p-h&&board[o-1][p][counter]==' ')
                    {
                        u2=0;
                    }
                }

            }
            if((xKing-z==h-yKing)&&xKing-z>0)
            {
                if (board[o][p][counter]=='p')
                {
                    if(o-z-1==h-p&&board[o-1][p][counter]==' ')
                    {
                        u3=0;
                    }
                }
            }
            if((xKing-z==yKing-h)&&xKing-z>0)
            {
                if (board[o][p][counter]=='p')
                {
                    if(z-o-1==h-p&&board[o-1][p][counter]==' ')
                    {
                        u4=0;
                    }
                }
            }
        }
           }
            }

           if(u1==0){return;}else if(u2==0){return;}else if(u3==0){return;} else if(u4==0){return;}}
        int flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        int right=1,left=1,bottom=1,up=1,upright=1,lowright=1,upleft=1,lowleft=1;
        i=xKing;j=yKing;z=i-1;
        if((i-1)>=1&&(i-1)<=8)//checks the upper place
        {if(board[i-1][j][counter]==' '||board[i-1][j][counter]=='P'||board[i-1][j][counter]=='R'||board[i-1][j][counter]=='N'
            ||board[i-1][j][counter]=='B'||board[i-1][j][counter]=='Q')
            {

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='R'&&board[x][i][counter]!='Q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='R'&&board[x][i][counter]!='Q')
        {
            flag2=0;
        }
        if(((z-1)>=2&&(z-1)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if (board[z-1][j-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if (board[z-1][j+1][counter]!='P')
            {
                flag4=0;
            }
        }
        m=1;
        temp=temp|flag1|flag2|flag3|flag4;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q')
        {
            flag4=0;
        }
        up=temp|flag1|flag2|flag3|flag4;
        }}
        i=xKing;j=yKing;z=i+1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((i+1)>=1&&(i+1)<=8)//checks the lower place
        {if(board[i+1][j][counter]==' '||board[i+1][j][counter]=='P'||board[i+1][j][counter]=='R'||board[i+1][j][counter]=='N'
            ||board[i+1][j][counter]=='B'||board[i+1][j][counter]=='Q')
            {

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag2=0;
        }
        if(((z-1)>=2&&(z-1)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if (board[z-1][j-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if (board[z-1][j+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag1|flag2|flag3|flag4;
         m=1;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='B'&&board[i][y+m][counter]!='Q')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='B'&&board[i][y-m][counter]!='Q')
        {
            flag4=0;
        }
        bottom=flag1|flag2|flag3|flag4|temp;
        }}
        i=xKing;j=yKing;z=j-1;
         flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
           if((j-1)>=3&&(j-1)<=10)//checks the left place
        {if(board[i][j-1][counter]==' '||board[i][j-1][counter]=='P'||board[i][j][counter]=='R'||board[i][j-1][counter]=='N'
            ||board[i][j-1][counter]=='B'||board[i][j-1][counter]=='Q')
            {
        if((((i-2)>=1&&(i-2)<=8)&&((z-1)>=3&&(z-1)<=10)))
        {
            if(board[i-2][z-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((i-1)>=1&&(i-1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i-1][z-2][counter]!='N')
            {
                flag2=0;
            }
        }else
        {
            flag2=0;
        }
        if (((i+1)>=1&&(i+1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i+1][z+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i+2][z+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((i-1)>=1&&(i-1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i-1][z+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((i+1)>=1&&(i+1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i+1][z-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((i-2)>=1&&(i-2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i-2][z+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if(board[i+2][z-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag2=0;
        }
        if(((i-1)>=2&&(i-1)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if (board[i-1][z-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((i-1)>=2&&(i-1)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if (board[i-1][z+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag1|flag2|flag3|flag4;
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        temp=flag1|flag2;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='B'&&board[i][z-m][counter]!='Q')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]=='B'&&board[i][z-m][counter]=='Q')
        {
            flag4=0;
        }
        left=temp|flag1|flag2|flag3|flag4;

        }}
       i=xKing;j=yKing;z=j+1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((j+1)>=3&&(j+1)<=10)//checks the right place
        {if(board[i][j+1][counter]==' '||board[i][j+1][counter]=='P'||board[i][j+1][counter]=='R'||board[i][j+1][counter]=='N'
            ||board[i][j+1][counter]=='B'||board[i][j+1][counter]=='Q')
           {
        if((((z-2)>=3&&(z-2)<=10)&&((i-1)>=1&&(i-1)<=8)))
        {
            if(board[i-1][z-2][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=3&&(z-1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z-1][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=3&&(z+1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z+1][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z+2][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=3&&(z-1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z-1][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=3&&(z+1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z+1][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=3&&(z-2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z-2][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i-1)>=1&&(i-1)<=8))
        {
            if(board[i-1][z+2][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='R'&&board[i][z][counter]!='Q')
        {
            flag2=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(((i-1)>=2&&(i-1)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if (board[i-1][z-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((i-1)>=2&&(i-1)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if (board[i-1][z+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag1|flag2|flag3|flag4;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='B'&&board[i][z-m][counter]!='Q')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='B'&&board[i][z+m][counter]!='Q')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='B'&&board[i][z-m][counter]!='Q')
        {
            flag4=0;
        }
        right=temp|flag1|flag2|flag3|flag4;
        }}
        i=xKing;j=yKing;z=i-1,h=j-1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j-1)>=3&&(j-1)<=10&&(i-1)>=1&&(i-1)<=8)//checks left upper place
            {if(board[i-1][j-1][counter]==' '||board[i-1][j-1][counter]=='P'||board[i-1][j-1][counter]=='R'||board[i-1][j-1][counter]=='N'
            ||board[i-1][j-1][counter]=='B'||board[i-1][j-1][counter]=='Q')
                {

        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z-1)>=2&&(z-1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z-1][h-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z-1][h+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag8=0;
        }
         upleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
        i=xKing;j=yKing;z=i-1,h=j+1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j+1)>=3&&(j+1)<=10&&(i-1)>=1&&(i-1)<=8)//checks right upper place
            {if(board[i-1][j+1][counter]==' '||board[i-1][j+1][counter]=='P'||board[i-1][j+1][counter]=='R'||board[i-1][j+1][counter]=='N'
            ||board[i-1][j+1][counter]=='B'||board[i-1][j+1][counter]=='Q')
                {
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z-1)>=2&&(z-1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z-1][h-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z-1][h+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
         m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag8=0;
        }
         upright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
        i=xKing;j=yKing;z=i+1,h=j-1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j-1)>=3&&(j-1)<=10&&(i+1)>=1&&(i+1)<=8)//checks left lower place
            {if(board[i+1][j-1][counter]==' '||board[i+1][j-1][counter]=='P'||board[i+1][j-1][counter]=='R'||board[i+1][j-1][counter]=='N'
            ||board[i+1][j-1][counter]=='B'||board[i+1][j-1][counter]=='Q')
                {
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z-1)>=2&&(z-1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z-1][h-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z-1][h+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag8=0;
        }
        lowleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
            flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        i=xKing;j=yKing;z=i+1,h=j+1;
            if((j+1)>=3&&(j+1)<=10&&(i+1)>=1&&(i+1)<=8)//checks right lower place
            {if(board[i+1][j+1][counter]==' '||board[i+1][j+1][counter]=='P'||board[i+1][j+1][counter]=='R'||board[i+1][j+1][counter]=='N'
            ||board[i+1][j+1][counter]=='B'||board[i+1][j+1][counter]=='Q')
                {
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='N')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='N')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='N')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='N')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='N')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='N')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='N')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='N')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z-1)>=2&&(z-1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z-1][h-1][counter]!='P')
            {
                flag3=0;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z-1][h+1][counter]!='P')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='R'&&board[i][y][counter]!='Q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='R'&&board[i][h][counter]!='Q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='R'&&board[z][i][counter]!='Q')
        {
            flag4=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='B'&&board[i][h+m][counter]!='Q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        int l=i,w=h-m;
        char tempo=board[i][h-m][counter];
        if(board[i][h-m][counter]!='B'&&board[i][h-m][counter]!='Q')
        {
            flag8=0;
        }
        lowright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        }}

            if((lowright==1)&&(lowleft==1)&&(upright==1)&&(upleft==1)&&(left==1)&&(right==1)&&(up==1)&&(bottom==1))
        {
            checkmate=1;
        }


        }
    else
    {
        int i,j,check=0,z,h,xKing,yKing,m=1;
        char type1=' ',type2;
        for(xKing=1;xKing<9;xKing++)
        {
            for( yKing=3;yKing<11;yKing++)
            {
                if (board[xKing][yKing][counter]=='K')
                {
                    break;
                }
            }
            if (board[xKing][yKing][counter]=='K')
                {
                    break;
                }
        }
        int x=xKing,y=yKing;
        i=x;j=y;
        if((i+1)>=1&&(i+1)<=8)
        {
            if((j-1)>=3&&(j-1)<=10)
            {
               if(board[i+1][j-1][counter]=='p')
               {
                check=1,z=i+1,h=j-1;
               }
           }
           if ((j+1)>=3&&(j+1)<=10)
           {
              if (board[i+1][j+1][counter]=='p')
             {
               check=1,z=i+1,h=j+1;
             }
          }
        }
        if((((i-2)>=1&&(i-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[i-2][j-1][counter]=='n')
            {
               check=1,z=i-2,h=j-1;
            }
        }
         if (((i-1)>=1&&(i-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i-1][j-2][counter]=='n')
            {
                check=1,z=i-1,h=j-2;
            }
        }
        if (((i+1)>=1&&(i+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i+1][j+2][counter]=='n')
            {
               check=1,z=i+1,h=j+2;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i+2][j+1][counter]=='n')
            {
                check=1,z=i+2,h=j+1;
            }
        }
        if (((i-1)>=1&&(i-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[i-1][j+2][counter]=='n')
            {
                check=1,z=i-1,h=j+2;
            }
        }
        if(((i+1)>=1&&(i+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[i+1][j-2][counter]=='n')
            {
                check=1,z=i+1,h=j-2;
            }
        }
        if (((i-2)>=1&&(i-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[i-2][j+1][counter]=='n')
            {
               check=1,z=i-2,h=j+1;
            }
        }
        if (((i+2)>=1&&(i+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[i+2][j-1][counter]=='n')
            {
                check=1,z=i+2,h=j-1;
            }
        }
        for(i=x+1;i<9;i++)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='r'||board[i][y][counter]=='q')
        {
            check=1,z=i,h=y;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][y][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]=='r'||board[i][y][counter]=='q')
        {
            check=1,z=i,h=y;
        }
        for(i=y+1;i<11;i++)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='r'||board[x][i][counter]=='q')
        {
            check=1,z=x,h=i;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[x][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]=='r'||board[x][i][counter]=='q')
        {
            check=1,z=x,h=i;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='b'||board[i][y+m][counter]=='q')
        {
            check=1,z=i,h=y+m;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='b'||board[i][y-m][counter]=='q')
        {
            check=1,z=i,h=y-m;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y+m][counter]=='b'||board[i][y+m][counter]=='q')
        {
           check=1,z=i,h=y+m;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
        }
        if(board[i][y-m][counter]=='b'||board[i][y-m][counter]=='q')
        {
            check=1,z=i,h=y-m;
        }
        if(check==0)
        {
            return;
        }
        type2=board[z][h][counter];//type 2 is the piece that causes the check
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                type1=board[i][h][counter];
                break;
            }
        }
            if(type1=='R'||type1=='Q')
            {
                return;
            }
            type1=' ';
            for(i=z-1;i>=1;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                type1=board[i][h][counter];
                break;
            }
        }
            if(type1=='R'||type1=='Q')
            {
                return;
            }
            type1=' ';
            for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                type1=board[z][i][counter];
                break;
            }
        }
            if(type1=='R'||type1=='Q')
            {
                return;
            }
            type1=' ';
            for(i=h-1;i>=3;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                type1=board[z][i][counter];
                break;
            }
        }
            if(type1=='R'||type1=='Q')
            {
                return;
            }
            type1=' ';
             m=1;
            for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                type1=board[i][h-m][counter];
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        m=1;
        if(type1=='B'||type1=='Q')
        {
            return;
        }
        type1=' ';
           for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                type1=board[i][h+m][counter];
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        m=1;
        if(type1=='B'||type1=='Q')
        {
            return;
        }
        type1=' ';
           for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                type1=board[i][h-m][counter];
                break;
            }
            m++;
            }
        }m=1;
            if(type1=='B'||type1=='Q')
        {
            return;
        }
        type1=' ';
           for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                type1=board[i][h+m][counter];
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(type1=='B'||type1=='Q')
        {
            return;
        }
        type1=' ';
        if(((z-1)>=2&&(z-1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z-1][h-1][counter]=='P')
            {
                return;
            }
        }
        if(((z-1)>=2&&(z-1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z-1][h+1][counter]=='P')
            {
                return;
            }
        }
            if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]=='N')
            {
                return;
            }
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]=='N')
            {
                return;
            }
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]=='N')
            {
                return;
            }
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]=='N')
            {
                return;
            }
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]=='N')
            {
                return;
            }
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]=='N')
            {
                return;
            }
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]=='N')
            {
                return;
            }
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]=='N')
            {
                return;
            }
        }
        int u1=1,u2=1,u3=1,u4=1,u5=1,u6=1,u7=1,u8=1,u9=1;
        if((abs(h-yKing)>1&&abs(z-xKing)==0)
           ||abs(z-xKing)>1&&abs(h-yKing)==0)
        {if(type2=='r'||type2=='q')
        {
            for(int o=1;o<9;o++)
        {
            for(int p=3;p<11;p++)
            {
                if (board[o][p][counter]=='P')
                {
                    if(xKing==z)
                    {
                        if(z-o==1&&z>o&&board[o+1][p][counter]==' ')
                        {
                            u1=0;
                        }
                    }
                }
                if (board[o][p][counter]=='R'||board[o][p][counter]=='Q')
                {
                    if(xKing==z)
                    {
                        if(o>z)
                        { int w;
                            for(w=o-1;w>=z;w--)
                            {
                                if(board[w][p][counter]!=' ')
                                {
                                    break;
                                }
                            }
                            if(w==z-1)
                            {
                                u2=0;
                            }
                        }
                        else if (z>o)
                        { int w;
                            for(w=o+1;w>=z;w++)
                            {
                                if(board[w][p][counter]!=' ')
                                {
                                    break;
                                }

                        }
                        if(w==z+1)
                        {
                            u3=0;
                        }
                    }
                }
                else if(yKing==h)
                {
                     if(p>h)
                        { int w;
                            for(w=p-1;w>=h;w--)
                            {
                                if(board[o][w][counter]!=' ')
                                {
                                    break;
                                }
                            }
                            if(w==h-1)
                            {
                                u4=0;
                            }
                        }
                        else if(p<h)
                        { int w;
                            for(w=p-1;w<=h;w++)
                            {
                                if(board[o][w][counter]!=' ')
                                {
                                    break;
                                }
                            }
                            if(w==h+1)
                            {
                                u5=0;
                            }
                        }
                }
            }
            if(board[o][p][counter]=='B'||board[o][p][counter]=='Q')
            { int b=1;
                if(p>h)
                        { int w;
                        for(w=p-1;w>=h;w--)
                            {
                                if(o-b>=3&&o-b<=10)
                                {if(board[o-b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }if((o-b>z&&o-b<xKing)||(o-b<z&&o-b>xKing))
                            {if(w==h-1)
                            {
                                u6=0;
                            }}
                            b=1;
                            for(w=p+1;w>=h;w--)
                            {
                                if(o+b>=3&&o+b<=10)
                                {if(board[o+b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }if((o+b>z&&o+b<xKing)||(o+b<z&&o+b>xKing))
                            {if(w==h-1)
                            {
                                u7=0;
                            }}}
                    b=1;
                    if(p<h)
                        { int w;
                        if(o>z)
                            {for(w=p+1;w>=h;w++)
                            {
                                if(o-b>=3&&o-b<=10)
                                {if(board[o-b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }
                            if((o-b>z&&o-b<xKing)||(o-b<z&&o-b>xKing))
                            {if(w==h+1)
                            {
                                u8=0;
                            }}
                            b=1;
                            if(o<z)
                            {for(w=p+1;w>=h;w++)
                            {
                                if(o+b>=3&&o+b<=10)
                                {if(board[o-b][w][counter]!=' ')
                                {
                                    break;
                                }
                                b++;
                            } else{break;}
                            }
                            if((o+b>z&&o+b<xKing)||(o+b<z&&o+b>xKing))
                            {if(w==h+1)
                            {
                                u9=0;
                            }}
                        }
                        }
            }

        }
        }
        }
        }
        if(u1==0){return;}else if(u2==0){return;}else if(u3==0){return;} else if(u4==0){return;}
        if(u5==0){return;}else if(u6==0){return;}else if(u7==0){return;} else if(u8=0){return;}else if(u9=0){return;}}
        u1=1,u2=1,u3=1;
        if(abs(z-xKing)==abs(h-yKing)&&abs(z-xKing)>1)
        {if(type2=='q'||type2=='b')
        {

        for(int o=1;o<9;o++)
        {
            for(int p=3;p<11;p++)
            {if((z-xKing==h-yKing)&&z-xKing>0)
            {
                if (board[o][p][counter]=='P')
                {
                    if(z-o-1==h-p&&board[o+1][p][counter]==' ')
                    {
                        u1=0;
                    }
                }
            }
            if((z-xKing==yKing-h)&&z-xKing>0)
            {
                if (board[o][p][counter]=='P')
                {int s=z-o-1,d=p-h;
                    if((z-o-1==p-h)&&board[o+1][p][counter]==' ')
                    {
                        u2=0;
                    }
                }

            }
            if((xKing-z==h-yKing)&&xKing-z>0)
            {
                if (board[o][p][counter]=='P')
                {
                    if(o-z+1==h-p&&board[o+1][p][counter]==' ')
                    {
                        u3=0;
                    }
                }
            }
            if((xKing-z==yKing-h)&&xKing-z>0)
            {
                if (board[o][p][counter]=='P')
                {
                    if(o-z+1==p-h&&board[o+1][p][counter]==' ')
                    {
                        u4=0;
                    }
                }
            }
        }
           }
            }
            ;
            if(u1==0){return;}else if(u2==0){return;}else if(u3==0){return;} else if(u4==0){return;}}
        int flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        int right=1,left=1,bottom=1,up=1,upright=1,lowright=1,upleft=1,lowleft=1;
        i=xKing;j=yKing;z=i-1;
        if((i-1)>=1&&(i-1)<=8)//checks the upper place
        {if(board[i-1][j][counter]==' '||board[i-1][j][counter]=='p'||board[i-1][j][counter]=='r'||board[i-1][j][counter]=='n'
            ||board[i-1][j][counter]=='b'||board[i-1][j][counter]=='q')
            {

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='r'&&board[x][i][counter]!='q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[x][i][counter]!='r'&&board[x][i][counter]!='q')
        {
            flag2=0;
        }
        if(((z+1)>=2&&(z+1)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if (board[z+1][j-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if (board[z+1][j+1][counter]!='p')
            {
                flag4=0;
            }
        }
        m=1;
        temp=temp|flag1|flag2|flag3|flag4;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q')
        {
            flag4=0;
        }
        up=temp|flag1|flag2|flag3|flag4;
        }}
        i=xKing;j=yKing;z=i+1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((i+1)>=1&&(i+1)<=8)//checks the lower place
        {if(board[i+1][j][counter]==' '||board[i+1][j][counter]=='p'||board[i+1][j][counter]=='r'||board[i+1][j][counter]=='n'
            ||board[i+1][j][counter]=='b'||board[i+1][j][counter]=='q')
            {

        if((((z-2)>=1&&(z-2)<=8)&&((j-1)>=3&&(j-1)<=10)))
        {
            if(board[z-2][j-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z-1][j-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z+1][j+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z+2][z+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((j+2)>=3&&(j+2)<=10))
        {
            if(board[z-1][j+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((j-2)>=3&&(j-2)<=10))
        {
            if(board[z+1][j-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if(board[z-2][j+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if(board[z+2][j-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=y+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag1=0;
        }
        for(i=y-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag2=0;
        }
        if(((z+1)>=2&&(z+1)<=8)&&((j-1)>=3&&(j-1)<=10))
        {
            if (board[z+1][j-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((j+1)>=3&&(j+1)<=10))
        {
            if (board[z+1][j+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag1|flag2|flag3|flag4;
         m=1;
        for(i=z+1;i<9;i++)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q')
        {
            flag1=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q')
        {
            flag2=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(y+m>=3&&y+m<=10)
            {
             if(board[i][y+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y+m][counter]!='b'&&board[i][y+m][counter]!='q')
        {
            flag3=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(y-m>=3&&y-m<=10)
            {
             if(board[i][y-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][y-m][counter]!='b'&&board[i][y-m][counter]!='q')
        {
            flag4=0;
        }
        bottom=flag1|flag2|flag3|flag4|temp;
        }}
        i=xKing;j=yKing;z=j-1;
         flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
           if((j-1)>=3&&(j-1)<=10)//checks the left place
        {if(board[i][j-1][counter]==' '||board[i][j-1][counter]=='p'||board[i][j][counter]=='r'||board[i][j-1][counter]=='n'
            ||board[i][j-1][counter]=='b'||board[i][j-1][counter]=='q')
            {
        if((((i-2)>=1&&(i-2)<=8)&&((z-1)>=3&&(z-1)<=10)))
        {
            if(board[i-2][z-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((i-1)>=1&&(i-1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i-1][z-2][counter]!='n')
            {
                flag2=0;
            }
        }else
        {
            flag2=0;
        }
        if (((i+1)>=1&&(i+1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i+1][z+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i+2][z+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((i-1)>=1&&(i-1)<=8)&&((z+2)>=3&&(z+2)<=10))
        {
            if(board[i-1][z+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((i+1)>=1&&(i+1)<=8)&&((z-2)>=3&&(z-2)<=10))
        {
            if(board[i+1][z-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((i-2)>=1&&(i-2)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if(board[i-2][z+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((i+2)>=1&&(i+2)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if(board[i+2][z-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag2=0;
        }
        if(((i+1)>=2&&(i+1)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if (board[i+1][z-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((i+1)>=2&&(i+1)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if (board[i+1][z+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag1|flag2|flag3|flag4;
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        temp=flag1|flag2;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='b'&&board[i][z-m][counter]!='q')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]=='b'&&board[i][z-m][counter]=='q')
        {
            flag4=0;
        }
        left=temp|flag1|flag2|flag3|flag4;

        }}
       i=xKing;j=yKing;z=j+1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if((j+1)>=3&&(j+1)<=10)//checks the right place
        {if(board[i][j+1][counter]==' '||board[i][j+1][counter]=='p'||board[i][j+1][counter]=='r'||board[i][j+1][counter]=='n'
            ||board[i][j+1][counter]=='b'||board[i][j+1][counter]=='q')
           {
        if((((z-2)>=3&&(z-2)<=10)&&((i-1)>=1&&(i-1)<=8)))
        {
            if(board[i-1][z-2][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=3&&(z-1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z-1][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=3&&(z+1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z+1][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z+2][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=3&&(z-1)<=10)&&((i+2)>=1&&(i+2)<=8))
        {
            if(board[i+2][z-1][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=3&&(z+1)<=10)&&((i-2)>=1&&(i-2)<=8))
        {
            if(board[i-2][z+1][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=3&&(z-2)<=10)&&((i+1)>=1&&(i+1)<=8))
        {
            if(board[i+1][z-2][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=3&&(z+2)<=10)&&((i-1)>=1&&(i-1)<=8))
        {
            if(board[i-1][z+2][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        for(i=x+1;i<9;i++)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag1=0;
        }
        for(i=x-1;i>0;i--)
        {
            if(board[i][z][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][z][counter]!='r'&&board[i][z][counter]!='q')
        {
            flag2=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(((i+1)>=2&&(i+1)<=8)&&((z-1)>=3&&(z-1)<=10))
        {
            if (board[i+1][z-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((i+1)>=2&&(i+1)<=8)&&((z+1)>=3&&(z+1)<=10))
        {
            if (board[i+1][z+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag1|flag2|flag3|flag4;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q')
        {
            flag1=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='b'&&board[i][z-m][counter]!='q')
        {
            flag2=0;
        }
        m=1;
        for(i=x-1;i>0;i--)
        {
            if(z+m>=3&&z+m<=10)
            {
             if(board[i][z+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z+m][counter]!='b'&&board[i][z+m][counter]!='q')
        {
            flag3=0;
        }
        m=1;
        for(i=x+1;i<9;i++)
        {
           if(z-m>=3&&z-m<=10)
            {
             if(board[i][z-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][z-m][counter]!='b'&&board[i][z-m][counter]!='q')
        {
            flag4=0;
        }
        right=temp|flag1|flag2|flag3|flag4;
        }}
        i=xKing;j=yKing;z=i-1,h=j-1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j-1)>=3&&(j-1)<=10&&(i-1)>=1&&(i-1)<=8)//checks left upper place
            {if(board[i-1][j-1][counter]==' '||board[i-1][j-1][counter]=='p'||board[i-1][j-1][counter]=='r'||board[i-1][j-1][counter]=='n'
            ||board[i-1][j-1][counter]=='b'||board[i-1][j-1][counter]=='q')
                {

        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z+1)>=2&&(z+1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z+1][h-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z+1][h+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag8=0;
        }
         upleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
        i=xKing;j=yKing;z=i-1,h=j+1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j+1)>=3&&(j+1)<=10&&(i-1)>=1&&(i-1)<=8)//checks right upper place
            {if(board[i-1][j+1][counter]==' '||board[i-1][j+1][counter]=='p'||board[i-1][j+1][counter]=='r'||board[i-1][j+1][counter]=='n'
            ||board[i-1][j+1][counter]=='b'||board[i-1][j+1][counter]=='q')
                {
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z+1)>=2&&(z+1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z+1][h-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z+1][h+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
         m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag8=0;
        }
         upright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
        i=xKing;j=yKing;z=i+1,h=j-1;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
            if((j-1)>=3&&(j-1)<=10&&(i+1)>=1&&(i+1)<=8)//checks left lower place
            {if(board[i+1][j-1][counter]==' '||board[i+1][j-1][counter]=='p'||board[i+1][j-1][counter]=='r'||board[i+1][j-1][counter]=='n'
            ||board[i+1][j-1][counter]=='b'||board[i+1][j-1][counter]=='q')
                {
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z+1)>=2&&(z+1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z+1][h-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z+1][h+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag8=0;
        }
        lowleft=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
            }}
            flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        i=xKing;j=yKing;z=i+1,h=j+1;
            if((j+1)>=3&&(j+1)<=10&&(i+1)>=1&&(i+1)<=8)//checks right lower place
            {if(board[i+1][j+1][counter]==' '||board[i+1][j+1][counter]=='p'||board[i+1][j+1][counter]=='r'||board[i+1][j+1][counter]=='n'
            ||board[i+1][j+1][counter]=='b'||board[i+1][j+1][counter]=='q')
                {
        if((((z-2)>=1&&(z-2)<=8)&&((h-1)>=3&&(h-1)<=10)))
        {
            if(board[z-2][h-1][counter]!='n')
            {
                flag1=0;
            }
        }
        else
        {
            flag1=0;
        }
         if (((z-1)>=1&&(z-1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z-1][h-2][counter]!='n')
            {
                flag2=0;
            }
        }
        else
        {
            flag2=0;
        }
        if (((z+1)>=1&&(z+1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z+1][h+2][counter]!='n')
            {
                flag3=0;
            }
        }
        else
        {
            flag3=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z+2][h+1][counter]!='n')
            {
                flag4=0;
            }
        }
        else
        {
            flag4=0;
        }
        if (((z-1)>=1&&(z-1)<=8)&&((h+2)>=3&&(h+2)<=10))
        {
            if(board[z-1][h+2][counter]!='n')
            {
                flag5=0;
            }
        }
        else
        {
            flag5=0;
        }
        if(((z+1)>=1&&(z+1)<=8)&&((h-2)>=3&&(h-2)<=10))
        {
            if(board[z+1][h-2][counter]!='n')
            {
                flag6=0;
            }
        }
        else
        {
            flag6=0;
        }
        if (((z-2)>=1&&(z-2)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if(board[z-2][h+1][counter]!='n')
            {
                flag7=0;
            }
        }
        else
        {
            flag7=0;
        }
        if (((z+2)>=1&&(z+2)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if(board[z+2][h-1][counter]!='n')
            {
                flag8=0;
            }
        }
        else
        {
            flag8=0;
        }
        int temp=flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        flag1=1,flag2=1,flag3=1,flag4=1,flag5=1,flag6=1,flag7=1,flag8=1;
        if(((z+1)>=2&&(z+1)<=8)&&((h-1)>=3&&(h-1)<=10))
        {
            if (board[z+1][h-1][counter]!='p')
            {
                flag3=0;
            }
        }
        if(((z+1)>=2&&(z+1)<=8)&&((h+1)>=3&&(h+1)<=10))
        {
            if (board[z+1][h+1][counter]!='p')
            {
                flag4=0;
            }
        }
        temp=temp|flag3|flag4;
        flag3=1,flag4=1;
        for(i=z+1;i<9;i++)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][y][counter]!='r'&&board[i][y][counter]!='q')
        {
            flag1=0;
        }
        for(i=z-1;i>0;i--)
        {
            if(board[i][h][counter]!=' ')
            {
                break;
            }
        }
        if(board[i][h][counter]!='r'&&board[i][h][counter]!='q')
        {
            flag2=0;
        }
        for(i=h+1;i<11;i++)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag3=0;
        }
        for(i=h-1;i>2;i--)
        {
            if(board[z][i][counter]!=' ')
            {
                break;
            }
        }
        if(board[z][i][counter]!='r'&&board[z][i][counter]!='q')
        {
            flag4=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag5=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag6=0;
        }
        m=1;
        for(i=z-1;i>0;i--)
        {
           if(h+m>=3&&h+m<=10)
            {
             if(board[i][h+m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h+m][counter]!='b'&&board[i][h+m][counter]!='q')
        {
            flag7=0;
        }
        m=1;
        for(i=z+1;i<9;i++)
        {
            if(h-m>=3&&h-m<=10)
            {
             if(board[i][h-m][counter]!=' ')
            {
                break;
            }
            m++;
            }
            else
            {
                break;
            }
        }
        if(board[i][h-m][counter]!='b'&&board[i][h-m][counter]!='q')
        {
            flag8=0;
        }
        lowright=temp|flag1|flag2|flag3|flag4|flag5|flag6|flag7|flag8;
        }}

            if((lowright==1)&&(lowleft==1)&&(upright==1)&&(upleft==1)&&(left==1)&&(right==1)&&(up==1)&&(bottom==1))
        {
            checkmate=1;
        }


    }

}
