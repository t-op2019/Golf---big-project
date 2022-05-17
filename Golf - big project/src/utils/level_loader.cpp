//
//  level_loader.cpp
//  Golf - big project
//
//  Created by Dư Võ on 5/5/22.
//

#include "level_loader.hpp"
#include <cmath>

vector<Tile> loadWalls(int lvl, SDL_Texture *wallTexture, SDL_Texture *spikedWallTexture, SDL_Texture *stickyWallTexture)
{
    vector<Tile> temp = {};
    switch (lvl)
    {
    case 0:
        for (int i = 0; i <= 10; i++)
        {
            temp.push_back(Tile(Vector(60 * i, 600 - 60 * 3), wallTexture, false, false));
        }
        for (int i = 1; i <= 10; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * i, 60 * 2), wallTexture, false, false));
        }

        break;

    case 1:
        for (int i = 1; i <= 9; i++)
        {
            temp.push_back(Tile(Vector(800 - 60, 600 - 60 * i), wallTexture, false, false));
        }
        for (int i = 1; i <= 7; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * 4 - 8, 600 - 60 * i - 8), spikedWallTexture, true, false));
        }
        for (int i = 2; i <= 7; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * i, 600 - 60 * 9), wallTexture, false, false));
        }
        for (int i = 8; i >= 2; i--)
        {
            temp.push_back(Tile(Vector(800 - 60 * 7, 600 - 60 * i), wallTexture, false, false));
        }
        for (int i = 8; i <= 11; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * i, 600 - 60 * 2), wallTexture, false, false));
        }
        for (int i = 3; i <= 8; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * 11 - 8, 600 - 60 * i - 8), spikedWallTexture, true, false));
        }

        break;

    case 2:
        temp.push_back(Tile(Vector(800 - 60 - 8, 0 - 8), spikedWallTexture, true, false));
        for (int i = 1; i <= 7; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * 3, 600 - 60 * i), wallTexture, false, false));
        }
        temp.push_back(Tile(Vector(800 - 60 * 3, 600 - 60 * 8), stickyWallTexture, false, true));
        for (int i = 4; i <= 11; i++)
        {
            temp.push_back(Tile(Vector(800 - 60 * i, 600 - 60 * 8), wallTexture, false, false));
        }
        for (int i = 7; i >= 3; i--)
        {
            temp.push_back(Tile(Vector(800 - 60 * 11, 600 - 60 * i), wallTexture, false, false));
        }
        temp.push_back(Tile(Vector(0 - 8, 600 - 60 * 8 - 8), spikedWallTexture, true, false));
        temp.push_back(Tile(Vector(0 - 8, 600 - 60 - 8), spikedWallTexture, true, false));
        temp.push_back(Tile(Vector(800 - 60 * 4, 600 - 60), stickyWallTexture, false, true));

        break;

    default:
        break;
    }
    return temp;
}

vector<Spike> loadSpikes(int lvl, SDL_Texture *spikeTextureActive, SDL_Texture *spikeTextureInactive)
{
    vector<Spike> temp = {};
    switch (lvl)
    {
    case 2:
        for (int j = 0; j <= 1; j++)
        {
            for (int i = 5; i <= 9; i++)
            {
                temp.push_back(Spike(Vector(800 - 60 * i, 60 * j), spikeTextureInactive, spikeTextureActive, 100));
            }
        }
        for (int j = 5; j <= 6; j++)
        {
            for (int i = 5; i <= 7; i++)
            {
                temp.push_back(Spike(Vector(800 - 60 * j, 600 - 60 * i), spikeTextureInactive, spikeTextureActive, 50));
            }
        }
        for (int i = 5; i <= 6; i++)
        {
            temp.push_back(Spike(Vector(800 - 60 * 4, 600 - 60 * i), spikeTextureInactive, spikeTextureActive, 50));
        }

        break;

    default:
        break;
    }
    return temp;
}

vector<Axe> loadAxes(int lvl, SDL_Texture *axeTexture)
{
    vector<Axe> temp = {};
    switch (lvl)
    {
    case 2:
        temp.push_back(Axe(Vector(200, 300), axeTexture, 90, 2));
        temp.push_back(Axe(Vector(400, 300), axeTexture, 0, 2));
        break;

    case 3:
        temp.push_back(Axe(Vector(400, 300), axeTexture, 90, 2));

    default:
        break;
    }
    return temp;
};

void loadLevel(int lvl, vector<Tile> &tiles, vector<Spike> &spikes, vector<Axe> &axes, Ball &ball, Hole &hole, Vector &holePos, Vector &requirements, SDL_Texture *wallTexture, SDL_Texture *spikedWallTexture, SDL_Texture *stickyWallTexture, SDL_Texture *spikeTextureActive, SDL_Texture *spikeTextureInactive, SDL_Texture *axeTexture)
{
    ball.setVelocity(0, 0);
    ball.setScale(1, 1);
    ball.setWin(false);
    tiles = loadWalls(lvl, wallTexture, spikedWallTexture, stickyWallTexture);
    spikes = loadSpikes(lvl, spikeTextureActive, spikeTextureInactive);
    // axes = loadAxes(lvl, axeTexture);

    switch (lvl)
    {
    case 0:
        ball.setPos(60 - 8, 600 - 60 - 8);
        hole.setPos(800 - 60 - 8, 60 - 8);
        requirements = Vector(7, 14);
        break;

    case 1:
        ball.setPos(800 - 60 * 2 - 8, 600 - 60 - 8);
        hole.setPos(800 - 60 * 9 - 8, 600 - 60 * 3 - 8);
        requirements = Vector(8, 10);
        break;

    case 2:
        ball.setPos(800 - 60 - 8, 600 - 60 - 8);
        hole.setPos(800 - 60 * 4 + 30 - 8, 600 - 60 * 7 + 30 - 8);
        requirements = Vector(6, 8);
        break;

    case 3:
        ball.setPos(800 - 60 - 8, 600 - 60 - 8);
        hole.setPos(0, 0);
        requirements = Vector(99, 99);
        break;

    default:
        Vector initialBallPos = Vector(rand() % 785, rand() % 585);
        Vector initialBallVelocity = Vector(sqrt(5) / (double)(rand() % 3 + 1), sqrt(5) / (double)(rand() % 3 + 1));
        ball.setPos(initialBallPos.x, initialBallPos.y);
        ball.setVelocity(initialBallVelocity.x, initialBallVelocity.y);
        ball.setArrowVelocity(initialBallVelocity.x, initialBallVelocity.y);
        hole.setPos(-69, -69);
        requirements = Vector(699, 699);
        break;
    }
    holePos = Vector(hole.getPos().x, hole.getPos().y);
}
