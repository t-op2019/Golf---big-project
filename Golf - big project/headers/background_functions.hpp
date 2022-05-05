//
//  background_functions.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "SDL_Utils.hpp"
#include "level_loader.hpp"
#include "Entity.hpp"
#include "Tile.hpp"
#include "Spike.hpp"
#include "Ball.hpp"
#include "Hole.hpp"

using namespace std;

void setVariables(SDL_Window* _window, SDL_Renderer* _renderer, const string _windowTitle, int _width, int _height,int _lvl, int& _gameState);

void loadAllTexture();

void unloadAllTexture();

void update(bool& _isPlaying, SDL_Event event);

void refresh();

void renderPresent();

void renderBackground();

void renderObject(Entity entity);

void renderArrow(Entity& entity);

vector<Tile> loadTiles(int lvl);

vector<Tile> loadSpikes(int lvl);

vector<Spike> loadIntervalSpikes(int lvl);

void loadLevels(int lvl);
