//
//  background_functions.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include "SDL_Utils.hpp"
#include <iostream>
#include <vector>
using namespace std;

void setVariables(SDL_Window* _window, SDL_Renderer* _renderer, const string _windowTitle, int _width, int _height);

void loadAllTexture();

void unloadAllTexture();

void refresh();

void renderPresent();

void renderBackground();
