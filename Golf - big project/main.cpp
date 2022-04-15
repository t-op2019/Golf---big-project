//
//  main.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "headers/Ball.hpp"
#include "headers/game_functions.hpp"
#include "headers/background_functions.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    const string windowTitle = "Power Golf";
    int width = 800, height = 600;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    // set important global variables for functions in background_functions.cpp to use
    setVariables(window, renderer, windowTitle, width, height);
    
    loadAllTexture();
    
    bool isPlaying = true;
    
    SDL_Event event;
    while (isPlaying) {
            
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isPlaying = false;
            }
        }
        
        playGame(isPlaying);
    }
    
    unloadAllTexture();
    
    return 0;
}
