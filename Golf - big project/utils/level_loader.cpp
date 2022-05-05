//
//  level_loader.cpp
//  Golf - big project
//
//  Created by Dư Võ on 5/5/22.
//

#include "level_loader.hpp"

vector<Tile> loadWalls(int lvl, SDL_Texture* wallTexture, SDL_Texture* spikedWallTexture, SDL_Texture* stickyWallTexture) {
    vector<Tile> temp = {};
    switch (lvl) {
        case 0:
            temp.push_back(Tile(Vector(64 - 8, 64 * 3 - 8), spikedWallTexture, true, false));
            temp.push_back(Tile(Vector(0, 0), wallTexture, false, false));
            break;
        case 1:
            temp.push_back(Tile(Vector(64 - 8, 64 * 3 - 8), stickyWallTexture, false, true));
        default:
            break;
    }
    return temp;
}

vector<Spike> loadSpikes(int lvl, SDL_Texture* spikeTextureActive, SDL_Texture* spikeTextureInactive) {
    vector<Spike> temp = {};
    switch (lvl) {
        case 1:
            temp.push_back(Spike(Vector(16 + 32 * 3, 16 + 32 * 2), spikeTextureInactive, spikeTextureActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 4, 16 + 32), spikeTextureInactive, spikeTextureActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 4, 16 + 32 * 3), spikeTextureInactive, spikeTextureActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 5, 16 + 32 * 2), spikeTextureInactive, spikeTextureActive, 100));
            break;
            
        default:
            break;
    }
    return temp;
}

void loadLevel(int lvl, vector<Tile>& tiles,vector<Spike>& spikes,Ball& ball,Hole& hole, Vector& holePos, Vector& requirements, SDL_Texture* wallTexture, SDL_Texture* spikedWallTexture, SDL_Texture* stickyWallTexture, SDL_Texture* spikeTextureActive, SDL_Texture* spikeTextureInactive) {
    ball.setVelocity(0, 0);
    ball.setScale(1, 1);
    ball.setWin(false);
    tiles = loadWalls(lvl, wallTexture, spikedWallTexture, stickyWallTexture);
    spikes = loadSpikes(lvl, spikeTextureActive, spikeTextureInactive);
    
    switch (lvl) {
        case 0:
            ball.setPos(24 + 32 * 4, 24 + 32 * 11);
            hole.setPos(24 + 32 * 4, 24 + 32 * 2);
            holePos = Vector(24 + 32 * 4, 24 + 32 * 2);
            requirements = Vector(3, 3);
            break;
            
        case 1:
            ball.setPos(24 + 32 * 10, 24 + 32 * 14);
            hole.setPos(24 + 32 * 4, 24 + 32 * 2);
            holePos = Vector(24 + 32 * 4, 24 + 32 * 2);
            requirements = Vector(2, 2);
        default:
            break;
    }
}
