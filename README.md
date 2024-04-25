# Starry Cosmos Shooter

A game where the user is a spaceship that can move in an orbit around a planet, with the objective of hitting a moving ball with beams to gain the highest number of points possible. 
There are also stars surrounding the planet, and if the spaceship hits even one of the stars, the game will end. The game is written in C++ and it used SDL 2 to help with its creation.
<br> <br>

Here is a short clip of some gameplay: <br>
[![Gameplay]()](https://github.com/AA-n-d-y/space-shooter-game/assets/138430862/24e94296-dd45-4611-8401-5345d79a8dc6)
<br> <br>

## Controls

- A:          to move left
- D:          to move right
- Spacebar:   to shoot beams
- R:          to restart the game after it ends


## How to run the game (for Windows only)

1. **First, install all of the included files and also install the files from the Resources section. Users should also have minGW installed.** <br> <br>

2. In the main directory, you should have **the two cpp files and hpp file**, the **Makefile**, the **gameimages folder**,
   and the **Roboto folder**, which contains **Roboto-Regular.ttf**. <br> <br>
   
3. Next, create a folder called **sdl_includes** and, within it, two subfolders called **include** and **lib**. <br> <br>

4. In the subfolder called **include**, you should paste all the files from **SDL, SDL images, and SDL ttf** that are in the <br>
   **x86_64-w64-mingw32/include/SDL2/** directories (**All the header files**).
   After that is done, the subfolder called **include** inside of **sdl_includes** should only contain header files if the steps above were done correctly. <br> <br>
   
5. Again, in the subfolder called **lib** inside **sdl_includes**, paste all of the files from **SDL, SDL images, and SDL ttf** that are in the <br>
   **x86_64-w64-mingw32/lib/** directories
   (**All of the .a and .la files, and even the cmake and pkgconfig folders**). <br> <br>
   
6. Furthermore, paste into the main directory **all of the .dll files from SDL, SDL images, and SDL ttf.** They can be found in the <br>
   **x86_64-w64-mingw32/bin/** directory for each SDL. <br> <br>
   
7. The photo below represents what the directory should look like once everything is done correctly.
   **The files inside the subfolder called include are not shown in this image due to the sheer number of them.**
   Make sure the formatting of everything is the same as in the photo or else the game will not run properly. <br> <br>
   ![Example](https://github.com/AA-n-d-y/Personal-Projects/assets/138430862/3225ae34-8036-4693-bd72-b6884f90d12f) <br> <br>
   
8. **Finally, to run the game, open the terminal, type in make all and press enter, then type in ./game and press enter. After that, the game should be working as intended.
   If for some reason the game crashes or fails to load, re-enter ./game and press enter until it works.**


## Resources

This game was made using SDL, SDL image, SDL ttf, and the Roboto font. <br>

[Install SDL (mingw tar version)](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) <br>

[Install SDL image (mingw tar version)](https://github.com/libsdl-org/SDL_image/releases) <br>

[Install SDL ttf (mingw tar version)](https://github.com/libsdl-org/SDL_ttf/releases) <br>

[Install the Roboto font family](https://fonts.google.com/specimen/Roboto)
