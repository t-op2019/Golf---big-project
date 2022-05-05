//
//  level_loader.hpp
//  Golf - big project
//
//  Created by Dư Võ on 5/5/22.
//

#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Tile.hpp"
#include "Hole.hpp"
#include "Spike.hpp"
#include "Ball.hpp"

using namespace std;

vector<Tile> loadWalls(int lvl, SDL_Texture* wallTexture, SDL_Texture* spikedWallTexture);
vector<Spike> loadSpikes(int lvl, SDL_Texture* spikeTextureActive, SDL_Texture* spikeTextureInactive);
void loadLevel(int lvl,vector<Tile>& tiles,vector<Spike>& spikes,Ball& ball,Hole& hole, Vector& holePos, Vector& requirements, SDL_Texture* wallTexture, SDL_Texture* spikedWallTexture, SDL_Texture* stickyWallTexture, SDL_Texture* spikeTextureActive, SDL_Texture* spikeTextureInactive);
