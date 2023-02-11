#include <iostream>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>

using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    system("mode con cols=50 lines=25");
    system("color 70");
    cout << "                    Start!!!\n";
    system("pause");
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

}


void GameOver() 
{
    system("cls");
    cout << "                    GAMEOVER!!!\n";
    cout << "                    Schore: "<< score<<"\n";
    gameOver = true;
    system("pause");
}

void Draw() {
    Sleep(300);
    system("cls");
    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruitY && j == fruitX)
                cout << "$";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << "o";
                    }

                if (!print)
                    cout << " ";
            }


        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;

}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;
        case 'z':
            gameOver = true;
            break;

        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
        GameOver();
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            GameOver();
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

}


int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }

    return 0;

}