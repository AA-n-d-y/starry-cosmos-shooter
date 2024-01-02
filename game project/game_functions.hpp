/*

Header file that contains the class details and functions

*/


#ifndef GAME_FUNCTIONS_HPP
#define GAME_FUNCTIONS_HPP


/// Implementing necessary header files

#include <iostream>
#include <ostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <math.h>
#include <string>
#include <cstring>
#include <vector>
#include <experimental/random>
using namespace std;


/// Creating the game class

class sGame {

    /// Variables

    private:
        SDL_Window* window;
        SDL_Renderer* renderHolder;
        SDL_Texture* spaceship;
        SDL_Rect spaceshipSize;
        SDL_Texture* planet;
        SDL_Rect planetSize;
        SDL_Texture* beam;
        SDL_Rect beamSize;
        SDL_Texture* block;
        SDL_Rect blockSize;
        SDL_Texture* star[5];
        SDL_Rect starSize[5];
        SDL_Texture* textBox;
        SDL_Rect textBoxSize;
        SDL_Texture* textBox2;
        SDL_Rect textBoxSize2;
        SDL_Texture* textBox3;
        SDL_Rect textBoxSize3;
        TTF_Font* font;

        int score = 0;

        int speeds[2] = {-2, 2};
        int xSpeed[5];
        int ySpeed[5];
        const char* stars[4] = {"gameimages/bstar.png", "gameimages/gstar.png", "gameimages/rstar.png"};

        const double pi = 3.14159265358979323846;
        double theta = -90 * (pi/180);
        double radius;
        double bSpeed = speeds[rand() % 2];
        double bTheta = -90 * (pi/180);
        double bMultiplier = 1.0;

        bool exitGame = true;
        bool running = true;
        

    /// Methods

    public:

        // Constructor and destructor
        sGame();
        ~sGame();

        // Functions for the game
        void renderer();
        bool runStatus();
        void gameUpdate();
        void events();
        bool programEnd();
};


#endif



/// End of file