#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

//sets up snake and first piece of food
void Setup();

//draws gameboard, snake (tail), and score
void Draw();

//gets WASD input and sets a direction for each
void Input();

//implements tail logic, movement of snake, custom wall rules, score count, and random food generation
void Logic();

//slows down gameplay by a lot if implemented 
void gameSpeedSlow();

//slows down gameplay if implemented 
void gameSpeedMedium();

//regular gameplay if implemented 
void gameSpeedFast();

//game menu that lets user pick a game speed and starts the game
int welcomeScreen(void);

//runs entire application
void runApp();
