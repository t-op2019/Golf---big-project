//
//  Ball.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Entity.hpp"
#include "Hole.hpp"
#include "Tile.hpp"

using namespace std;

class Ball : public Entity {
public:
    Ball(Vector _pos, SDL_Texture* _texture, SDL_Texture* _pointArrowTexture, SDL_Texture* _powerMeterForeground, SDL_Texture* _powerMeterBackground, int _index);
    Vector getVelocity();
    Vector getInitialMousePos();
    vector<Entity> getPoints();
    vector<Entity> getPowerBar();
    int getStroke();
    bool hasWon();
    
    void setWin(bool _win);
    void setInitialMousePos(double x, double y);
    void setVelocity(double x, double y);
    void setLauchVelocity(double x, double y);
    void update(double delta, bool isMouseDown, bool isMousePressed, vector<Tile> tiles, vector<Hole> holes);
    
private:
    Vector velocity;
    Vector target;
    Vector lauchedVelocity;
    double velocityValue;
    double lauchedVelocityValue;
    Vector initialMousePos;
    bool canMove;
    bool playedSwingSound;
    int index;
    int stroke = 0;
    int directionX = 1, directionY = 1;
    bool win = false;
    
    // the constant friction that slows down the speed of the ball
    double friction = 0.001;
    vector<Entity> points;
    vector<Entity> powerBar;
};
