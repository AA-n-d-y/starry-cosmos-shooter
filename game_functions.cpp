/*

Implementing the methods declared in the header file

*/


/// Implementing necessary header files

#include "game_functions.hpp"


//// Implementing the class methods

/// Constructor
sGame::sGame() {

    // Initialize SDL, TTF, and create the window and renderer

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {

        window = SDL_CreateWindow("Starry Cosmos Shooter", SDL_WINDOWPOS_CENTERED, \
            SDL_WINDOWPOS_CENTERED, 1200, 700, SDL_FALSE);

        renderHolder = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderHolder, 36, 36, 36, 255);
        renderer();

        // Load the spaceship onto the screen
        SDL_Surface* imageTmp = IMG_Load("gameimages/astronaut.png"); //holding the image and need to turn this into a texture
        spaceship = SDL_CreateTextureFromSurface(renderHolder, imageTmp); // turning it to a texture
        SDL_FreeSurface(imageTmp); // freeing the tmp image
        imageTmp = NULL;

        // Change the height, width, and position of the spaceship
        spaceshipSize.h = 80;
        spaceshipSize.w = 80;
        spaceshipSize.x = 550 + 500 * cos(theta);  // setting its initial position
        spaceshipSize.y = 700 + 500 * sin(theta);


        // Load the planet onto the screen
        imageTmp = IMG_Load("gameimages/planet.png"); //holding the image and need to turn this into a texture
        planet = SDL_CreateTextureFromSurface(renderHolder, imageTmp); // turning it to a texture
        SDL_FreeSurface(imageTmp); // freeing the tmp image
        imageTmp = NULL;

        // Change the height, width, and position of the spaceship
        planetSize.h = 300;
        planetSize.w = 550;
        planetSize.x = 325; // setting its initial position
        planetSize.y = 425;


        // Load the points block onto the screen
        imageTmp = IMG_Load("gameimages/pointball.png"); // holding the image and need to turn this into a texture
        block = SDL_CreateTextureFromSurface(renderHolder, imageTmp); // turning it to a texture
        SDL_FreeSurface(imageTmp); // freeing the tmp image
        imageTmp = NULL;

        // Change the height, width, and position of the points block
        blockSize.h = 40;
        blockSize.w = 40;
        radius = 550 / 2;
        blockSize.x = 580 + radius * cos(bTheta); // setting its initial position
        blockSize.y = 685 + radius * sin(bTheta);
        

        // Creating the stars
        for (int i = 0; i < 5; i++) {

            int random = experimental::randint(0, 2);
            imageTmp = IMG_Load(stars[random]); //holding the image and need to turn this into a texture
            star[i] = SDL_CreateTextureFromSurface(renderHolder, imageTmp); // turning it to a texture
            SDL_FreeSurface(imageTmp); // freeing the tmp image
            imageTmp = NULL;

            // Change the height, width, and position of the stars
            int positions[4];
            positions[0] = experimental::randint(20, 450);
            positions[1] = experimental::randint(700, 1140);
            positions[2] = experimental::randint(20, 100);
            positions[3] = experimental::randint(350, 640);

            starSize[i].h = 50;
            starSize[i].w = 50;
            starSize[i].x = positions[rand() % 2]; // setting its initial position
            starSize[i].y = positions[rand() % 3 + 2];
            
            // Condition to not spawn the stars on one another
            for (int j = 0; j < 5; j++) {
                if ((j != i && starSize[i].x + 25 > starSize[j].x && starSize[i].x + 25 < \
                        starSize[j].x + 50 && starSize[i].y + 25 > starSize[j].y && \
                        starSize[i].y + 25 < starSize[j].y + 50) || (j != i && starSize[i].x < \
                        starSize[j].x + 50 && starSize[i].x + 25 > starSize[j].x + 50 && \
                        starSize[i].y < starSize[j].y + 50 && starSize[i].y + 25 > starSize[j].y + 50)) {

                    starSize[i].x = positions[rand() % 2];
                    starSize[j].x = positions[rand() % 2];
                }
            }

            // Condition to not spawn the stars directly on the spaceship
            if ((starSize[i].x > 550 + 500 * cos(theta) && starSize[i].x < 630 + 500 * cos(theta) \
                    && starSize[i].y > 700 + 500 * sin(theta) && starSize[i].y < \
                    780 + 500 * sin(theta)) || (starSize[i].x + 50 > 550 + 500 * cos(theta) && \
                    starSize[i].x + 50 < 630 + 500 * cos(theta) && starSize[i].y + 50 > 700 + 500 \
                    * sin(theta) && starSize[i].y + 50 < 780 + 500 * sin(theta))) {

                starSize[i].y = positions[rand() % 3 + 2];
            }

            // Condition to not spawn the stars directly on the planet
            if ((starSize[i].x + 50 > 325 && starSize[i].x + 50 < 875 && starSize[i].y + 50 > 425) \
                    || (starSize[i].x > 325 && starSize[i].x < 875 && starSize[i].y + 50 > 425)) {

                starSize[i].y -= 425 - 60;
            }

            // Setting initial speeds for the stars
            xSpeed[i] = speeds[rand() % 2];
            ySpeed[i] = speeds[rand() % 2];
        }


        /// Displaying the score
        
        font = TTF_OpenFont(("Roboto/Roboto-Regular.ttf"), 25);
        SDL_Color textColour = {255, 255, 255, 255};

        // Turning the score variable into a string and then turning it into a C char array
        string textScore = to_string(score);
        imageTmp = TTF_RenderText_Solid(font, (textScore).c_str(), textColour);
        textBox = SDL_CreateTextureFromSurface(renderHolder, imageTmp);
        SDL_FreeSurface(imageTmp);
        imageTmp = NULL;

        // Change the height, width, and position of the textbox
        textBoxSize.h = 150;
        textBoxSize.w = 100;
        textBoxSize.x = 60; // setting its initial position
        textBoxSize.y = 30;

        TTF_CloseFont(font);
        font = NULL;


    } else {
        cout << "Error in starting the game" << endl;
        running = false;
    }
}


/// Destructor
sGame::~sGame() {

    /// Ending the game

    SDL_DestroyTexture(spaceship);
    spaceship = NULL;

    SDL_DestroyTexture(planet);
    planet = NULL;

    SDL_DestroyTexture(beam);
    beam = NULL;

    SDL_DestroyTexture(block);
    block = NULL;

    SDL_DestroyTexture(textBox);
    textBox = NULL;

    SDL_DestroyTexture(textBox2);
    textBox2 = NULL;

    SDL_DestroyTexture(textBox3);
    textBox3 = NULL;

    for (int i = 0; i < 5; i++) {
        SDL_DestroyTexture(star[i]);
        star[i] = NULL;
    }

    SDL_DestroyRenderer(renderHolder);
    renderHolder = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    running = false;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


/// Ending the program
bool sGame::programEnd() {
    return exitGame;
}


/// Screen renderer
void sGame::renderer() {

    SDL_RenderClear(renderHolder);

    if (spaceship != NULL) {
        SDL_RenderCopy(renderHolder, spaceship, NULL, &spaceshipSize); // use this to set the size of the spaceship and display it
    }
    if (planet != NULL) {
        SDL_RenderCopy(renderHolder, planet, NULL, &planetSize); // use this to set the size of the planet and display it
    }
    if (beam != NULL) {
        SDL_RenderCopy(renderHolder, beam, NULL, &beamSize); // use this to set the size of a beam and display it
    }
    if (block != NULL) {
        SDL_RenderCopy(renderHolder, block, NULL, &blockSize); // use this to set the size of the block and display it
    }
    if (textBox != NULL) {
        SDL_RenderCopy(renderHolder, textBox, NULL, &textBoxSize); // use this to set the size of the text and display it
    }
    if (textBox2 != NULL) {
        SDL_RenderCopy(renderHolder, textBox2, NULL, &textBoxSize2); // use this to set the size of the second text and display it
    }
    if (textBox3 != NULL) {
        SDL_RenderCopy(renderHolder, textBox3, NULL, &textBoxSize3); // use this to set the size of the third text and display it
    }
    for (int i = 0; i < 5; i++) {
        if (star[i] != NULL) {
            SDL_RenderCopy(renderHolder, star[i], NULL, &(starSize[i])); // use this to set the size of a star and display it
        }
    }

    SDL_RenderPresent(renderHolder);
}


/// Return the run status of the game
bool sGame::runStatus() {
    return running;
}


/// Updating the game
void sGame::gameUpdate() {

    /// Stars

    // Moving the stars    
    for (int i = 0; i < 5; i++) {
        starSize[i].x = starSize[i].x + xSpeed[i];
        starSize[i].y = starSize[i].y + ySpeed[i];

        /// Star physics conditions

        // Stars hitting the right corner of the planet
        if (starSize[i].x > 600 && starSize[i].x < 875 && starSize[i].y > 560) {
            xSpeed[i] *= -1;
            ySpeed[i] *= -1;
        }

        // Stars hitting the left corner of the planet
        if (starSize[i].x + 50 > 325 && starSize[i].x < 600 && starSize[i].y > 560) {
            xSpeed[i] *= -1;
            ySpeed[i] *= -1;
        }

        // Stars hitting the top of the planet
        if (starSize[i].x + 25 > 380 && starSize[i].x < 820 && starSize[i].y > 440 && starSize[i].y < 525) {
            xSpeed[i] *= -1;
            ySpeed[i] *= -1;
        }

        // Stars hitting the horizontal boundaries of the window
        if (starSize[i].x + 50 > 1200 || starSize[i].x < 0) {
            xSpeed[i] *= -1;
            ySpeed[i] *= 1;
        }

        // Stars hitting the vertical boundaries of the window
        if (starSize[i].y + 50 > 700 || starSize[i].y < 0) {
            xSpeed[i] *= 1;
            ySpeed[i] *= -1;
        }
    
        // Stars hitting other stars
        for (int j = 0; j < 5; j++) {
            if ((j != i && starSize[i].x + 25 > starSize[j].x && starSize[i].x + 25 < starSize[j].x + 50 && \
                    starSize[i].y + 25 > starSize[j].y && starSize[i].y + 25 < starSize[j].y + 50) || \
                    (j != i && starSize[i].x < starSize[j].x + 50 && starSize[i].x + 25 > starSize[j].x + 50 && \
                    starSize[i].y < starSize[j].y + 50 && starSize[i].y + 25 > starSize[j].y + 50)) {

                xSpeed[i] *= 1;
                ySpeed[i] *= -1;
                xSpeed[j] *= 1;
                ySpeed[j] *= -1;
            }
        }

        // Stars hitting the spaceship (game over)
        if ((starSize[i].x > spaceshipSize.x && starSize[i].x < spaceshipSize.x + 80 && starSize[i].y > \
                spaceshipSize.y && starSize[i].y < spaceshipSize.y + 80) || (starSize[i].x + 50 < \
                spaceshipSize.x + 80 && starSize[i].x + 50 > spaceshipSize.x && starSize[i].y + 50 > \
                spaceshipSize.y && starSize[i].y + 50 < spaceshipSize.y + 80)) {

            /// Displaying the end screen

            spaceshipSize.h = 130;
            spaceshipSize.w = 130;
            spaceshipSize.x = 540;
            spaceshipSize.y = 70;

            SDL_DestroyTexture(planet);
            planet = NULL;
                
            SDL_DestroyTexture(textBox);
            textBox = NULL;
                
            SDL_DestroyTexture(beam);
            beam = NULL;

            SDL_DestroyTexture(block);
            block = NULL;

            for (int i = 0; i < 5; i++) {
                SDL_DestroyTexture(star[i]);
                star[i] = NULL;
            }
                
            // Loading end game text
            font = TTF_OpenFont(("Roboto/Roboto-Regular.ttf"), 60);
            SDL_Color textColour = {137, 207, 240, 255};

            // Turning the score variable into a string, concatenating them, then turning it all into a C char array
            string endText = "Final score: " + to_string(score);
            SDL_Surface* imageTmp = TTF_RenderText_Solid(font, (endText).c_str(), textColour);
            textBox2 = SDL_CreateTextureFromSurface(renderHolder, imageTmp);
            SDL_FreeSurface(imageTmp);
            imageTmp = NULL;

            // Change the height, width, and position of a textbox
            textBoxSize2.h = 100;
            textBoxSize2.w = 400;
            textBoxSize2.x = 400; 
            textBoxSize2.y = 240;

            // Creating a second textbox
            endText = "Press R to play again";
            imageTmp = TTF_RenderText_Solid(font, (endText).c_str(), textColour);
            textBox3 = SDL_CreateTextureFromSurface(renderHolder, imageTmp);
            SDL_FreeSurface(imageTmp);
            imageTmp = NULL;

            // Change the height, width, and position of the second textbox
            textBoxSize3.h = 100;
            textBoxSize3.w = 550;
            textBoxSize3.x = 330; 
            textBoxSize3.y = 350;

            TTF_CloseFont(font);       
            font = NULL;          
        }
    }    


    /// Beam physics

    // Speed of the beam
    beamSize.y += 45;

    // Beam hitting the points block
    if ((beamSize.x > blockSize.x && beamSize.x < blockSize.x + 40 && beamSize.y + 30 > \
            blockSize.y && beamSize.y + 30 < blockSize.y + 40) || (beamSize.x + 20 > blockSize.x && \
            beamSize.x + 20 < blockSize.x + 40 && beamSize.y + 30 > blockSize.y && \
            beamSize.y + 30 < blockSize.y + 40)) {

        SDL_DestroyTexture(beam);
        beam = NULL;
        score++;
        if (score % 5 == 0 && score > 0) {
            // Speeding up the ball after every 5 points
            bMultiplier += 0.25;
            bTheta += bSpeed * bMultiplier * (pi/180);
            blockSize.x = 580 + radius * cos(bTheta); 
            blockSize.y = 685 + radius * sin(bTheta);
        }      

        /// Displaying the updated score

        SDL_DestroyTexture(textBox);
        textBox = NULL;
        font = TTF_OpenFont(("Roboto/Roboto-Regular.ttf"), 25);
        SDL_Color textColour = {255, 255, 255, 255};

        // Turning the score variable into a string and then turning it into a C char array
        string textScore = to_string(score);
        SDL_Surface* imageTmp = TTF_RenderText_Solid(font, (textScore).c_str(), textColour);
        textBox = SDL_CreateTextureFromSurface(renderHolder, imageTmp);
        SDL_FreeSurface(imageTmp);
        imageTmp = NULL;

        // Change the height, width, and position of the new textbox depending on the score
        if (score < 10) {
            textBoxSize.h = 150;
            textBoxSize.w = 100;
            textBoxSize.x = 60; 
            textBoxSize.y = 30;
        } else if (score >= 10 && score <= 99) {
            textBoxSize.h = 150;
            textBoxSize.w = 120;
            textBoxSize.x = 60; 
            textBoxSize.y = 30;
        } else {
            textBoxSize.h = 150;
            textBoxSize.w = 140;
            textBoxSize.x = 60; 
            textBoxSize.y = 30;            
        }
        TTF_CloseFont(font);
        font = NULL;
    } 
    
    if (beamSize.y > 710) {
        SDL_DestroyTexture(beam);
        beam = NULL;
    }


    /// Points block physics
    
    // Speed of the ball
    bTheta += bSpeed * bMultiplier * (pi/180);
    blockSize.x = 580 + radius * cos(bTheta); 
    blockSize.y = 685 + radius * sin(bTheta);

    // Reaching the right corner of the planet
    if (blockSize.y > 660 && blockSize.x > 600) {
        bTheta += -bSpeed * bMultiplier * (pi/180);
        blockSize.x = 580 + radius * cos(bTheta);
        blockSize.y = 685 + radius * sin(bTheta);
        bSpeed *= -1;
    }

    // Reaching the left corner of the planet
    if (blockSize.y > 660 && blockSize.x < 600) {
        bTheta += -bSpeed * bMultiplier * (pi/180);
        blockSize.x = 580 + radius * cos(bTheta);
        blockSize.y = 685 + radius * sin(bTheta);
        bSpeed *= -1;
    }
}


/// Handling the events in the game
void sGame::events() {

    SDL_Event event;
    SDL_PollEvent(&event); // reading the event queue and storing event information into the event variable 
    
    switch (event.type) {
        // Clicking the X on the window
        case SDL_QUIT:
            exitGame = false;
            sGame::~sGame();
            break;
    }

    /// Controls for the spaceship
    
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);

    // Pressing r
    if (keyStates[SDL_SCANCODE_R] && planet == NULL) {
        running = false;
        SDL_DestroyTexture(spaceship);
        spaceship = NULL;
        SDL_DestroyTexture(textBox2);
        textBox2 = NULL;
        SDL_DestroyTexture(textBox3);
        textBox3 = NULL;
    }

    // Pressing a
    if (keyStates[SDL_SCANCODE_A] && planet != NULL) {
        theta += -0.5 * (pi/180);
        spaceshipSize.x = 550 + 500 * cos(theta);
        spaceshipSize.y = 700 + 500 * sin(theta);

        // Hitting the bottom left of the screen            
        if (spaceshipSize.y > 620 && spaceshipSize.x < 600) {
            theta += 0.5 * (pi/180);
            spaceshipSize.x = 550 + 500 * cos(theta);
            spaceshipSize.y = 700 + 500 * sin(theta);
        }        
    }

    // Pressing d
    if (keyStates[SDL_SCANCODE_D] && planet != NULL) {
        theta += 0.5 * (pi/180);
        spaceshipSize.x = 550 + 500 * cos(theta);
        spaceshipSize.y = 700 + 500 * sin(theta);

        // Hitting the bottom right of the screen            
        if (spaceshipSize.y > 620 && spaceshipSize.x > 600) {
            theta += -0.5 * (pi/180);
            spaceshipSize.x = 550 + 500 * cos(theta);
            spaceshipSize.y = 700 + 500 * sin(theta);
        }
    }

    // Pressing spacebar
    if (keyStates[SDL_SCANCODE_SPACE] && planet != NULL) {
        // Loading a beam onto the screen
        SDL_Surface* imageTmp = IMG_Load("gameimages/beam.png"); 
        beam = SDL_CreateTextureFromSurface(renderHolder, imageTmp); 
        SDL_FreeSurface(imageTmp); 
        imageTmp = NULL;

        // Change the height, width, and position of a beam
        beamSize.h = 30;
        beamSize.w = 20;
        beamSize.x = spaceshipSize.x + 30; 
        beamSize.y = spaceshipSize.y + 30;        
    }

    // Pressing a and spacebar
    if (keyStates[SDL_SCANCODE_A] && keyStates[SDL_SCANCODE_SPACE] && planet != NULL) {
        theta += -0.05 * (pi/180);
        spaceshipSize.x = 550 + 500 * cos(theta);
        spaceshipSize.y = 700 + 500 * sin(theta);
                    
        if (spaceshipSize.y > 620 && spaceshipSize.x < 600) {
            theta += 0.05 * (pi/180);
            spaceshipSize.x = 550 + 500 * cos(theta);
            spaceshipSize.y = 700 + 500 * sin(theta);
        }

        SDL_Surface* imageTmp = IMG_Load("gameimages/beam.png"); 
        beam = SDL_CreateTextureFromSurface(renderHolder, imageTmp); 
        SDL_FreeSurface(imageTmp);
        imageTmp = NULL;

        beamSize.h = 30;
        beamSize.w = 20;
        beamSize.x = spaceshipSize.x + 30;
        beamSize.y = spaceshipSize.y + 30;       
    }

    // Pressing d and spacebar
    if (keyStates[SDL_SCANCODE_D] && keyStates[SDL_SCANCODE_SPACE] && planet != NULL) {
        theta += 0.05 * (pi/180);
        spaceshipSize.x = 550 + 500 * cos(theta);
        spaceshipSize.y = 700 + 500 * sin(theta);
                    
        if (spaceshipSize.y > 620 && spaceshipSize.x > 600) {
            theta += -0.05 * (pi/180);
            spaceshipSize.x = 550 + 500 * cos(theta);
            spaceshipSize.y = 700 + 500 * sin(theta);
        }

        SDL_Surface* imageTmp = IMG_Load("gameimages/beam.png"); 
        beam = SDL_CreateTextureFromSurface(renderHolder, imageTmp); 
        SDL_FreeSurface(imageTmp); 
        imageTmp = NULL;

        beamSize.h = 30;
        beamSize.w = 20;
        beamSize.x = spaceshipSize.x + 30;
        beamSize.y = spaceshipSize.y + 30;                
    }
}



/// End of file