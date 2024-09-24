#include "game.h"

int main() {
    EnableRawMode();  // Enable raw input mode for real-time input
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000);  // Control the speed of falling blocks (100ms delay)
    }

    DisableRawMode();  // Disable raw mode when the game is over
    return 0;
}
