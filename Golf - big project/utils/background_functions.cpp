//
//  background_functions.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "background_functions.hpp"

// basic background functions (load/unload textures, render and rerender screen
// *********************************************************************************

SDL_Window* window;
SDL_Renderer* renderer;
string windowTitle;
int width, height;

SDL_Texture *background, *playButton, *stages[9], *ball, *ballShadow, *hole, *point;

void setVariables(SDL_Window* _window, SDL_Renderer* _renderer, const string _windowTitle, int _width, int _height) {
    window = _window;
    renderer = _renderer;
    windowTitle = _windowTitle;
    width = _width;
    height = _height;
}

void loadAllTexture() {
    initSDL(window, renderer, windowTitle, width, height);
    const string defaultRoutes = "assets/images/";
    bool stagesLoaded = true;
    
    background = loadTexture(defaultRoutes + "bg.png", renderer);
    ball = loadTexture(defaultRoutes + "ball.png", renderer);
    ballShadow = loadTexture(defaultRoutes + "ball_shadow.png", renderer);
    hole = loadTexture(defaultRoutes + "hole.png", renderer);
    playButton = loadTexture(defaultRoutes + "click2start.png", renderer);
    point = loadTexture(defaultRoutes + "point.png", renderer);
    
//    for (int i = 0; i < 9; i++) {
//        stages[i] = loadTexture(defaultRoutes + "hangman" + to_string(i) + ".png", renderer);
//        if (stages[i] == NULL) {
//            stagesLoaded = false;
//            break;
//        }
//    }
    
    if (background == NULL | stagesLoaded == false | playButton == NULL | ball == NULL | ballShadow == NULL | hole == NULL | point == NULL) {
        unloadAllTexture();
        exit(1);
    }
    
    refresh();
}

void refresh() {
    renderBackground();
    renderPresent();
}

void unloadAllTexture() {
    SDL_DestroyTexture(background);
    
    for (int i = 0; i < 9; i++) {
        SDL_DestroyTexture(stages[i]);
    }
    
    quitSDL(window, renderer);
}

void renderPresent() {
    SDL_RenderPresent(renderer);
}

void renderBackground() {
    renderTexture(background, renderer, 0, 0, width, height);
}
