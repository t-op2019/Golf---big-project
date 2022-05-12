//
//  SDL_Utils.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

using namespace std;

// basic SDL functions
// ***********************************************************
void init();

void logSDLError(const string &message, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string &windowTitle, int width, int height);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitTilKeypress();

string interpretKey(SDL_KeyboardEvent* key);

// ***********************************************************



// render images and textures functions
// ***********************************************************

// get image from file and load texture
SDL_Texture* loadTexture(const string &file, SDL_Renderer* renderer);

// render background texture
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);

// render texture at coordinate (x,y) and width, height of w and h
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);

// render a clickable button
SDL_Rect renderButton(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);

// ***********************************************************



// render text and input
// ***********************************************************

void renderText(int fontSize, const char* input, SDL_Renderer* renderer, int x, int y);

// ***********************************************************
