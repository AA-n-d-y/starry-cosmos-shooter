/*

The main game loop will be run in this file

*/


/// Implementing necessary header files

#include "game_functions.hpp"


/// Main function

int main (int argc, char* argv[]) {
    
    // This is the condition used to end the program
    bool gameState = true;

    /// Main while loop to keep the program running
    while (gameState == true) {

        // Variables
        
        sGame* gameHolder = new sGame;

        const int delayFrame = 1000/60;
        

        /// While loop to keep a game instance running

        while (gameHolder->runStatus()) {

            unsigned int timer;
            
            // Get the time since SDL initialized
            Uint64 timeSinceStart =  SDL_GetTicks64();

            // Updating the window
            gameHolder->events();
            gameHolder->gameUpdate();
            gameHolder->renderer();

            // Fixing the frame cap if necessary
            timer = SDL_GetTicks64() - timeSinceStart;
            if (delayFrame > timer) {
                SDL_Delay(delayFrame - timer);
            }
        }
        

        // Exiting the whole program
        bool ender = gameHolder->programEnd();
        if (ender == false) {
            gameState = false;
        }


        // Cleaning the game instance's memory
        delete gameHolder;
        gameHolder = nullptr;
    }
    
    return 0;
}



/// End of file