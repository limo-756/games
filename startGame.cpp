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
#define infPosInt 2147483647
#define trace1(x)                cout <<#x<<": "<<x<< endl;
#define trace2(x, y)             cout <<#x<<": "<<x<<" | "<<#y<<": "<<y<< endl;
#define trace3(x, y, z)          cout <<#x<<": "<<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl;
#define trace4(a, b, c, d)       cout <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
#define trace5(a, b, c, d, e)    cout <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<<": "<<e<<endl;
int gameStatus = DRAW;
int compX,compY;
vector< pair<int,int> > winMoves,drawMoves;
int checkEntry(int *head,int incrementer)
{
    if(*head == PLAYER && *(head + incrementer) == PLAYER && *(head + 2*incrementer) == PLAYER)
        return PLAYER;
    if(*head == COMPUTER && *(head + incrementer) == COMPUTER && *(head + 2*incrementer) == COMPUTER)
        return COMPUTER;
    else
        return 0;
}
int checkSpace(int *matrix)
{
    int spaceNum = 0;
    for (int i = 0; i < 9; ++i)
        if(matrix[i] == SPACE)
                spaceNum++;
    return spaceNum;
}
bool gameOver(int *matrix)
{
    if( checkEntry(&matrix[0], ROW) )
        gameStatus = checkEntry(&matrix[0], ROW);
    else if( checkEntry(&matrix[3], ROW) )
        gameStatus = checkEntry(&matrix[3], ROW);
    else if( checkEntry(&matrix[6], ROW) )
        gameStatus = checkEntry(&matrix[6], ROW);
    else if( checkEntry(&matrix[0], COL) )
        gameStatus = checkEntry(&matrix[0], COL);
    else if( checkEntry(&matrix[1], COL) )
        gameStatus = checkEntry(&matrix[1], COL);
    else if( checkEntry(&matrix[2], COL) )
        gameStatus = checkEntry(&matrix[2], COL);
    else if( checkEntry(&matrix[0], D1) )
        gameStatus = checkEntry(&matrix[0], D1);
    else if( checkEntry(&matrix[2], D2) )
        gameStatus = checkEntry(&matrix[2], D2);
    if(gameStatus == COMPUTER || gameStatus == PLAYER || !checkSpace(matrix))
        return true;
    else
        return false;
}
int minMaxAlgo(int depth,int spaceNum,int *head,bool computer)
{
    if(gameOver(head))
    {
        int result = gameStatus;
        gameStatus = DRAW;
        return result;
    }
    if( spaceNum == 0)
        return 0;
    if(computer)
    {
        int bestValue = -infPosInt;
        // for (int k = 0; k < spaceNum; ++k)
        {
            for (int i = 0; i < 9; ++i)
                if(head[i] == SPACE)
                {
                    head[i] = COMPUTER;
                    int val = minMaxAlgo(depth+1,spaceNum-1,head,false);
                    if(val > bestValue)
                    {
                        bestValue = val;
                        compX = i/3;
                        compY = i%3;
                    }
                    head[i] = SPACE;
                    if(depth != 0 && val == COMPUTER)
                        return val;
                    if(depth == 0 && val == COMPUTER)
                        winMoves.push_back(make_pair(compX,compY));
                    if(depth == 0 && val == DRAW)
                        drawMoves.push_back(make_pair(compX,compY));
                }
        }
        return bestValue;
    }
    else
    {
        int bestValue = infPosInt;
        // for (int k = 0; k < spaceNum; ++k)
        {
            for (int i = 0; i < 9; ++i)
                if(head[i] == SPACE)
                {
                    head[i] = PLAYER;
                    int val = minMaxAlgo(depth+1,spaceNum-1,head,true);
                    if(val < bestValue)
                    {
                        bestValue = val;
                        compX = i/3;
                        compY = i%3;
                    }
                    head[i] = SPACE;
                    if(depth != 0 && val == PLAYER)
                        return val;
                }
        }
        return bestValue;
    }
}
void computerTurn(int matrix[3][3])
{
    srand((unsigned) time(0));
    winMoves.clear();
    drawMoves.clear();
    minMaxAlgo(0,checkSpace(&matrix[0][0]),&matrix[0][0],true);
    pair<int,int> turn;
    if(winMoves.size() > 0)
    {
        int index = rand()%winMoves.size();
        turn = winMoves[index];
    }
    else
    {
        int index = rand()%drawMoves.size();
        turn = drawMoves[index];
    }
    matrix[turn.first][turn.second] = COMPUTER;
    gameStatus = DRAW;
}
void printMatrix(int matrix[3][3])
{
    cout << "-----------------------------------------" << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if(matrix[i][j] == SPACE)
                cout << "_ ";
            else if(matrix[i][j] == COMPUTER)
                cout << "0 ";
            else if(matrix[i][j] == PLAYER)
                cout << "1 ";
        }
        cout << endl;
    }
}
int main(int argc, char const *argv[])
{
    cout << "This is tic tac toe game created by Anurag Sharma" << endl;
    string choice;
    bool chance;
    do
    {
        cout << "Do you want to play first y|Y for Yes n|N for No" << endl;
        cin >> choice;
    }while(choice!="Y" && choice!="y" && choice!="N" && choice!="n");
    if(choice == "Y" || choice == "y")
        chance = false;
    else
        chance = true;
    int matrix[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            matrix[i][j] = SPACE;
    while(!gameOver(&matrix[0][0]))
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
                else if(matrix[x][y] != SPACE)
                {
                    cout << "Coordinate already taken" << endl;
                    continue;
                }
                else
                    break;
            } while (true);
            matrix[x][y] = PLAYER;
            chance = true;
        }
        printMatrix(matrix);
    }
    if(gameStatus == DRAW)
        cout << "Match is a draw" << endl;
    else if(gameStatus == COMPUTER)
        cout << "Computer Win" << endl;
    else if(gameStatus == PLAYER)
        cout << "Opponent Win" << endl;
    return 0;
}