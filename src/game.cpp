#include "game.h"

bool gameOver;
const int width = 20;
const int height = 20;
int playerX, blockX, blockY, score;

// For handling raw input mode
struct termios orig_termios;

// Enables raw mode for real-time input
void EnableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Disables raw mode (when the game ends)
void DisableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// Check for keyboard hit
int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void Setup() {
    gameOver = false;
    playerX = width / 2;
    blockX = rand() % width;
    blockY = 0;
    score = 0;
}

void Draw() {
    system("clear");  // Clear the screen on Unix systems

    // Draw top border
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    // Draw the game field
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) std::cout << "#";  // Left border

            if (i == height - 1 && j == playerX)
                std::cout << "A";  // Player

            else if (i == blockY && j == blockX)
                std::cout << "B";  // Falling block

            else
                std::cout << " ";  // Empty space

            if (j == width - 1) std::cout << "#";  // Right border
        }
        std::cout << std::endl;
    }

    // Draw bottom border
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    std::cout << "Score: " << score << std::endl;
}

void Input() {
    if (kbhit()) {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        switch (ch) {
            case 'a':  // Move player left
                playerX--;
                break;
            case 'd':  // Move player right
                playerX++;
                break;
            case 'x':  // Quit the game
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    blockY++;  // Move block down each frame

    if (blockY >= height) {
        blockY = 0;
        blockX = rand() % width;  // Reset block to a new random position
        score++;
    }

    // Check collision between player and block
    if (blockY == height - 1 && blockX == playerX) {
        gameOver = true;
    }
}
