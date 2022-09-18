#include <iostream> // default library for input-output
#include <Windows.h> // sleep function support
#include <conio.h> // console input-output

using namespace std;

bool wannaPlay;
bool gameOver; // pretty self-explanatory
const int width = 40; // map width
const int height = 20; // map height
int x, y, fruitX, fruitY, score; // head and fruit coordinates
int tailX[100], tailY[100]; // coordinates of parts of tail, the tail's max length is 100, could/should be increased(?)
int nTail; // tail length variable
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // movement direction
eDirection dir;

void Setup() // sets head & first fruit position; also sets gameOver to false, dir to STOP (since the snake doesn't have to move at the beginning) and score to 0;
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    for (int i = 0; i < nTail; i++)
    {
        tailX[i] = -1;
        tailY[i] = -1;
    }
    nTail = 0;
    fruitX = rand() % width; // creates a random number from 0 to (width - 1)
    fruitY = rand() % height; // creates a random number from 0 to (height - 1)
    score = 0;
}

void Draw()
{
    system("cls"); // linux - system("clear");
    cout << "##########################################\n";
    cout << "#                                        #\n";
    cout << "# .dP\"Y8  88b 88    db    88  dP 888888  #\n";
    cout << "# .`Ybo.\" 88Yb88   dPYb   88odP  88__    #\n";
    cout << "# .o.`Y8b 88 Y88  dP__Yb  88\"Yb  88\"\"    #\n";
    cout << "# .8bodP' 88  Y8 dP\"\"\"\"Yb 88  Yb 888888  #\n";
    cout << "#                                        #\n";
    cout << "#            made by elica44             #\n";
    cout << "##########################################\n";
    cout << "#            W/A/S/D to start            #\n";
    cout << "#       X to end the current game        #\n";
    cout << "##########################################\n";
    char snakeHead = 'Q';

    if (gameOver == false)
    {
        cout << "#              Score: " << score;
        if (score < 10)
            cout << "                  #\n";
        else if (score < 100)
            cout << "                 #\n";
        else if (score < 1000)
            cout << "                #\n";
        cout << "#                                        #\n";
        cout << "#                                        #\n";
    }
    else {
        cout << "#              Score: " << score;
        if (score < 10)
            cout << "                  #\n";
        else if (score < 100)
            cout << "                 #\n";
        else if (score < 1000)
            cout << "                #\n";
        cout << "#              GAME OVER                 #\n";
        cout << "#      R TO RESTART | Z TO QUIT          #\n";
        snakeHead = 'X';
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << snakeHead;
            else if (i == fruitY && j == fruitX)
                cout << "&";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";
}

// WASD movement

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'r':
            gameOver = false;
            Setup();
            break;
        case 'x':
            gameOver = true;
            break;
        case 'z':
            if (gameOver == true)
                wannaPlay = false;
            break;
        }
    }
}

void Logic()
{
    for (int i = nTail; i > 0; i--)
    {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = x;
    tailY[0] = y;
    switch (dir)
    {
    case LEFT:
        Sleep(25);
        x--;
        break;
    case RIGHT:
        Sleep(25);
        x++;
        break;
    case UP:
        Sleep(25); // movement up-down is a lot faster than movement left-right, hence the sleep; could alternatively modify the speed at which the snake moves depending on the direction, but sleep is ok for now and the game works quickly, despite the function's heaviness
        y--;
        break;
    case DOWN:
        Sleep(25); // movement up-down is a lot faster than movement left-right, hence the sleep; could alternatively modify the speed at which the snake moves depending on the direction, but sleep is ok for now and the game works fast, despite the function's heaviness
        y++;
        break;
    default:
        break;
    }
    /*if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    */
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width; // creates a random number from 0 to (width - 1)
        fruitY = rand() % height; // creates a random number from 0 to (height - 1)
        nTail++;
    }
}

int main()
{
    /* Intializes random number generator */
    time_t t;
    srand((unsigned)time(&t));
    wannaPlay = true;
    Setup();
    while (wannaPlay)
    {
        Draw();
        Input();
        Sleep(75);
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(50); // linux - sleep(10); - slows down the game
        }
    }
    return 0;
}