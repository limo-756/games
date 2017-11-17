#include <bits/stdc++.h>
using namespace std;
#define DRAW 0
#define SPACE 0
#define COMPUTER 1
#define PLAYER -1
#define ROW 1
#define COL 3
#define D1  4
#define D2  2
int gameStatus = DRAW;
int checkEntry(int *p,int incrementer)
{
    if(*p == PLAYER && *(p + incrementer) == PLAYER && *(p + 2*incrementer) == PLAYER)
        return PLAYER;
    if(*p == COMPUTER && *(p + incrementer) == COMPUTER && *(p + 2*incrementer) == COMPUTER)
        return COMPUTER;
    else
        return 0;
}
bool checkSpace(int matrix[3][3])
{
    int spaceNum = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if(matrix[i][j] == SPACE)
                spaceNum++;
    return spaceNum == 0;
}
bool gameOver(int matrix[3][3])
{
    if( checkEntry(&matrix[0][0], ROW) )
        gameStatus = checkEntry(&matrix[0][0], ROW);
    else if( checkEntry(&matrix[1][0], ROW) )
        gameStatus = checkEntry(&matrix[1][0], ROW);
    else if( checkEntry(&matrix[2][0], ROW) )
        gameStatus = checkEntry(&matrix[2][0], ROW);
    else if( checkEntry(&matrix[0][0], COL) )
        gameStatus = checkEntry(&matrix[0][0], COL);
    else if( checkEntry(&matrix[0][1], COL) )
        gameStatus = checkEntry(&matrix[0][1], COL);
    else if( checkEntry(&matrix[0][2], COL) )
        gameStatus = checkEntry(&matrix[0][2], COL);
    else if( checkEntry(&matrix[0][0], D1) )
        gameStatus = checkEntry(&matrix[0][0], D1);
    else if( checkEntry(&matrix[0][2], D2) )
        gameStatus = checkEntry(&matrix[0][2], D2);
    if(gameStatus == COMPUTER || gameStatus == PLAYER || !checkSpace(matrix))
        return true;
    else
        return false;
}
void computerTurn(int matrix[3][3])
{

}
int main(int argc, char const *argv[])
{
    cout << "This is tic tac toe game created by Anurag Sharma" << endl;
    char choice;
    bool chance;
    do
    {
        cout << "Do you want to play first y|Y for Yes n|N for No" << endl;
        cin >> choice;
    }while(choice!='Y' ||choice!='y' ||choice!='N' ||choice!='n');
    if(choice == 'Y' || choice == 'y')
        chance = false;
    else
        chance = true;
    int matrix[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            matrix[i][j] = SPACE;
    while(!gameOver(matrix))
    {
        if(chance)
        {
            computerTurn(matrix);
            chance = false;
        }
        else
        {
            int x,y;
            do
            {
                cout << "Enter coordinates x->[1,2,3] y->[1,2,3] with space" << endl;
                cin >> x >> y;
                x--;y--;
                if(x > 2 || x < 0 || y > 2 || y < 0)
                {
                    cout << "Enter a valid coordinate" << endl;
                    continue;
                }
                if(matrix[x][y] != SPACE)
                {
                    cout << "Coordinate already taken" << endl;
                    continue;
                }
            } while (true);
            matrix[x][y] = PLAYER;
            chance = true;
        }
    }
    if(gameStatus == DRAW)
        cout << "Match is a draw" << endl;
    else if(gameStatus == COMPUTER)
        cout << "Computer Win" << endl;
    else if(gameStatus == PLAYER)
        cout << "Opponent Win" << endl;
    return 0;
}