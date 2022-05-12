//
//  level_loader.hpp
//  Golf - big project
//
//  Created by Dư Võ on 5/5/22.
//

#pragma once

#include "Tile.hpp"
#include "Hole.hpp"
#include "Spike.hpp"
#include "Ball.hpp"
#include "Axe.hpp"

using namespace std;

vector<Tile> loadWalls(int lvl, SDL_Texture* wallTexture, SDL_Texture* spikedWallTexture);
vector<Spike> loadSpikes(int lvl, SDL_Texture* spikeTextureActive, SDL_Texture* spikeTextureInactive);
vector<Axe> loadAxes(int lvl, SDL_Texture* axeTexture);
void loadLevel(int lvl, vector<Tile>& tiles, vector<Spike>& spikes, vector<Axe>& axes, Ball& ball, Hole& hole, Vector& holePos, Vector& requirements, SDL_Texture* wallTexture, SDL_Texture* spikedWallTexture, SDL_Texture* stickyWallTexture, SDL_Texture* spikeTextureActive, SDL_Texture* spikeTextureInactive, SDL_Texture* axeTexture);
