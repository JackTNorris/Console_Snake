#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;

class Graph
{
public:
    string coordinate;
};
class Snake
{
public:
    string head = "0";
    string tail = "o";
    int spot;
    int prevSpot;
    int prevSpot2;
    int length;
    int vertSpeed;
    int horizSpeed;

};
class Fruit
{
public:
    int spot;
};
int main()
{
    Graph snakeGraph[602];
    enum Status {OVER,CONTINUE};
    enum Direction {LEFT, RIGHT, UP, DOWN};
    Snake playerSnake;
    int tailSpot[201];
    Fruit snakeFruit;
    srand(time(0));
    playerSnake.vertSpeed = 10;
    playerSnake.horizSpeed = 5;

        for(int i = 1; i < 200; i++)
        {
        tailSpot[i] = 0; // set tailSpot positions
        }

    Direction snakeDirection;
    Direction prevDirection;
    Status gameStatus = CONTINUE;
    playerSnake.spot = 94;
    playerSnake.length = 0;
    snakeFruit.spot = 1 + rand() % 599;
    if (snakeFruit.spot % 30 == 1 || snakeFruit.spot == 1)
    {
        snakeFruit.spot++; // if the snakefruit spot is equal to a left border or the snakehead, add one to the coordinate
    }
    if  (snakeFruit.spot % 30 == 0)
    {
        snakeFruit.spot--; // if the snake fruit spot is equal to a right border, subtract one from the coordinate
    }

    while (gameStatus == CONTINUE)
    {
        string everything = "";
        string score = "                SCORE: ";
        snakeGraph[0].coordinate = "________________________________";
        snakeGraph[1].coordinate = "||";
        snakeGraph[601].coordinate = "********************************\n";
        for (int i = 2; i <= 600; i++) // generate graph
        {
            snakeGraph[i].coordinate = " ";
            if (i % 30 == 0)
            {
                snakeGraph[i].coordinate = "||\n"; // right side
            }
            if (i % 30 == 1)
            {
                snakeGraph[i].coordinate = "||"; // leftside
            }
        }
        snakeGraph[snakeFruit.spot].coordinate = "X"; // fruit
        if (_kbhit()) // is the player hits a key
        {


            switch(_getch())
            {
                case 'a':
                case 'A':
                    if (snakeDirection == RIGHT && playerSnake.length > 0);
                    else
                    {
                        snakeDirection = LEFT;
                    }
                    break;
                case 's':
                case 'S':
                    if (snakeDirection == UP && playerSnake.length > 0);
                    else
                    {
                        snakeDirection = DOWN;
                    }
                    break;
                case 'd':
                case 'D':
                    if (snakeDirection == LEFT && playerSnake.length > 0);
                    else
                    {
                    snakeDirection = RIGHT;
                    }
                    break;
                case 'w':
                case 'W':
                    if (snakeDirection == DOWN && playerSnake.length > 0);
                    else
                    {
                    snakeDirection = UP;
                    }
                    break;
            }
        }
        switch(snakeDirection) //take current snake direction and tell snake to perform that action
        {
            case LEFT:
                playerSnake.prevSpot = playerSnake.spot;
                Sleep(playerSnake.horizSpeed);
                playerSnake.spot--;
                break;
            case RIGHT:
                playerSnake.prevSpot = playerSnake.spot;
                Sleep(playerSnake.horizSpeed);
                playerSnake.spot++;
                break;
            case UP:
                playerSnake.prevSpot = playerSnake.spot;
                Sleep(playerSnake.vertSpeed);
                playerSnake.spot-=30;
                break;
            case DOWN:
                playerSnake.prevSpot = playerSnake.spot;
                Sleep(playerSnake.vertSpeed);
                playerSnake.spot += 30;
                break;

        }


        if (playerSnake.spot > 600 || playerSnake.spot % 30 <=   1)
        {
            goto theEnd; // if the snake head hits the bottom of the board, the sides, or the top of the board, game over
        }
        snakeGraph[playerSnake.spot].coordinate = "0";
        if (playerSnake.spot == snakeFruit.spot)
        {
                snakeFruit.spot = 1 + rand() % 599;

                if (snakeFruit.spot % 30 == 1 || snakeFruit.spot == 1)
                {
                    snakeFruit.spot++;
                }
                if  (snakeFruit.spot % 30 == 0)
                {
                    snakeFruit.spot--;
                }
                playerSnake.length++;
        }
        for (int i = 1; i <= playerSnake.length; i++)
        {
            playerSnake.prevSpot2 = tailSpot[i];
            tailSpot[i] = playerSnake.prevSpot;
            playerSnake.prevSpot = playerSnake.prevSpot2;
            snakeGraph[tailSpot[i]].coordinate = "o";
            if (playerSnake.spot == tailSpot[i])
            {
                goto theEnd; // if the snakehead hits his tail, gameover
            }

        }


        for (int i = 0; i <= 601; i++)
        {
            everything += snakeGraph[i].coordinate;
            if (i == 0)
            {
                everything += score ;
                everything += playerSnake.length;
                everything += "\n"; //display graph with altered coordinates
            }
        }
        cout << everything;
        system("CLS"); // clear screen

    }
    theEnd:


    return 0;
}
