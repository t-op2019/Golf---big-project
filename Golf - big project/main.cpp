//
//  main.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "headers/Ball.hpp"
#include "headers/background_functions.hpp"
#include "headers/Entity.hpp"
#include "headers/Ball.hpp"
#include "headers/Hole.hpp"
#include "headers/Tile.hpp"
#include <iostream>

using namespace std;

void playGame(int gameState, SDL_Event event);

bool isPlaying = true;

int main(int argc, const char * argv[]) {
    const string windowTitle = "Power Golf";
    int width = 800, height = 600;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    int lvl = 0;
    int gameState = 1;
    
    // set important global variables for functions in background_functions.cpp to use
    setVariables(window, renderer, windowTitle, width, height, lvl, gameState);
    SDL_Event event;
    loadAllTexture();
    loadLevels(lvl);
    while (SDL_PollEvent(&event) || isPlaying) {
        playGame(gameState, event);
    }
    
    unloadAllTexture();
    
    return 0;
}

void playGame(int gameState, SDL_Event event) {
    if (gameState != 0) {
        update(isPlaying, event);
//        refresh();
    }
}
