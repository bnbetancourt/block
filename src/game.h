#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>  // for usleep
#include <termios.h> // for non-blocking input on Unix

extern bool gameOver;
extern const int width;
extern const int height;
extern int playerX;
extern int blockX, blockY;
extern int score;

void Setup();
void Draw();
void Input();
void Logic();
void EnableRawMode();
void DisableRawMode();
int kbhit();

#endif
