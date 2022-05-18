//
//  Ball.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include "Line.hpp"
#include "Hole.hpp"
#include "Tile.hpp"
#include "Spike.hpp"
#include "Line.hpp"
#include "Axe.hpp"

using namespace std;

class Ball : public Entity
{
public:
    Ball(Vector _pos, SDL_Texture *_texture, SDL_Texture *_pointArrowTexture, SDL_Texture *_powerMeterForeground, SDL_Texture *_powerMeterBackground);
    Vector getVelocity();
    Vector getArrowVelocity();
    Vector getInitialMousePos();
    vector<Entity> getPoints();
    vector<Entity> getPowerBar();
    int getStroke();
    int getBounce();
    bool hasWon();
    void setSwung(bool _swung);
    void resetSwung(int counter);

    SDL_Rect *getRect(int x, int y);

    void setStroke(int _stroke);
    void setBounce(int _bounce);
    void setWin(bool _win);
    void setInitialMousePos(double x, double y);
    void setVelocity(double x, double y);
    void setArrowVelocity(double x, double y);
    void setLauchVelocity(double x, double y);
    void update(SDL_Renderer *renderer, double delta, bool isMouseDown, bool isMousePressed, vector<Tile> tiles, vector<Spike> spikes, vector<Axe> &axes, Hole hole, int &_gameState, int &_loseContext);
    void reset();

private:
    Vector velocity;
    Vector arrowVelocity;
    Vector target;
    Vector lauchedVelocity;
    double velocityValue;
    double lauchedVelocityValue;
    Vector initialMousePos;
    bool canMove;
    bool playedSwingSound;
    int stroke = 0;
    int bounce = 0;
    int directionX = 1, directionY = 1;
    bool win = false;
    bool swung = false;

    SDL_Rect rect;

    vector<Entity> points;
    vector<Entity> powerBar;
};
