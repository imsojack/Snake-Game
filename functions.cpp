#include "header.h"

using namespace std;
bool gameOver;
const int width = 26; //map dimensions
const int height = 17;
int x, y, foodX, foodY, points; //x & y is snake head
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection direction;

void Setup() {
    gameOver = false;
    direction = STOP;
    x = width / 2; //snake head will start in the middle
    y = height / 2;
    foodX = rand() % width; //create random number from 0 to width - 1 (location in the map) for the fruit
    foodY = rand() % height;
    points = 0;
}

void Draw() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); //similar use to system("cls") but helps flickering problem
    for (int i = 0; i < width + 2; i++) //plus 2 just to make it look nicer
        cout << '-'; //top wall
    cout << "\n";

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|"; //print left-side wall
            if (i == y && j == x)
                cout << "O"; //print snake head
            else if (i == foodY && j == foodX)
                cout << "X"; //print fruit
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++) {

                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; //print entire snake tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; //print blank space for gameplay if snake is not there
            }
            if (j == width - 1)
                cout << "|"; //prints right-side wall
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << '-'; //bottom wall
    cout << "\n";
    cout << "\n" << "Score: " << points << "\n";
}

void Input() {
    if (_kbhit()) //returns if keyboard is pressed 
    {
        switch (_getch()) //returns ascii value of character
        {
        case 'a': //setting WASD input to up, down, left, right
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'x': //special case to just end game
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; //sets tail to follow the snake head
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i]; //sets current head position (will become head position - 1)
        prev2Y = tailY[i]; 
        tailX[i] = prevX; //sets current head position again
        tailY[i] = prevY; 
        prevX = prev2X; //sets current position to the position it was last move
        prevY = prev2Y;
    }
    switch (direction) //moves x and y coordinates (snake head) around based on WASD input
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
    default:
        break;
    }

    //makes vertical speed manageable (for my computer)
    if (direction == UP || direction == DOWN) {
        Sleep(20); //can change this value based on strength of cpu
    }

    /* Normal Snake Rules
    if (x > width || x < 0 || y > height || y < 0) //ends game if snake head goes outside the map (all 4 sides)
        gameOver = true;
    */

    //Custom rules so that the snake can go through walls and come out on opposite side
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y) //ends game if you hit your own tail
            gameOver = true;

    if (x == foodX && y == foodY)
    {
        points += 10; //10 points for every food the snake eats
        foodX = rand() % width; //spawn new food in a new location if snake head is currently on current food
        foodY = rand() % height;
        nTail++; //increase tail by 1 after the snake eats
    }
}

void gameSpeedFast() {
    if (direction == LEFT || direction == RIGHT) {
        Sleep(15);
    } //horizontal and vertical speed will now be slower and more equal to each other
    
    if (direction == UP || direction == DOWN) {
        Sleep(35);
    }
}

void gameSpeedMedium() {
    if (direction == LEFT || direction == RIGHT) {
        Sleep(40);
    } //horizontal and vertical speed will now be slower and more equal to each other
    
    if (direction == UP || direction == DOWN) {
        Sleep(80);
    }
}

void gameSpeedSlow() {
    if (direction == LEFT || direction == RIGHT) {
        Sleep(50);
    } //horizontal and vertical speed will now be slower and more equal to each other
    Sleep(100);
    if (direction == UP || direction == DOWN) {
        Sleep(175);
    }
}

int welcomeScreen(void) {
    int choice = 0;

    cout << "\n Welcome to Snake!\n\n";
    cout << " Please select a game speed: \n";
    cout << " (note that the speed of your computer will drastically impact the speed of the game)\n\n";
    cout << " 1 = slow\n";
    cout << " 2 = medium\n";
    cout << " 3 = fast\n";
    cout << " 4 = very fast\n\n";
 
    printf(" Hit enter after you select a number...\n");
    scanf("%d", &choice);

    return choice;
}

void runApp() {
    int choice = 0;
    srand(time(NULL)); //allows food spawn to be random

    choice = welcomeScreen();

    switch (choice)
    {
    case 1: 
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            gameSpeedSlow();
        }
        break;

    case 2: 
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            gameSpeedMedium();
        }
        break;
    case 3:
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            gameSpeedFast();
        }
    case 4:
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
        }
        break;
    default: printf("Invalid input");
        break;
    }
}
