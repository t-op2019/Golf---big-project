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
#include "Line.hpp"
#include "Hole.hpp"
#include "Tile.hpp"
#include "Spike.hpp"
#include "Line.hpp"

using namespace std;

class Ball : public Entity {
public:
    Ball(Vector _pos, SDL_Texture* _texture, SDL_Texture* _pointArrowTexture, SDL_Texture* _powerMeterForeground, SDL_Texture* _powerMeterBackground, int _index);
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
    
    void setStroke(int _stroke);
    void setWin(bool _win);
    void setInitialMousePos(double x, double y);
    void setVelocity(double x, double y);
    void setArrowVelocity(double x, double y);
    void setLauchVelocity(double x, double y);
    void update(SDL_Renderer* renderer, double delta, bool isMouseDown, bool isMousePressed, vector<Tile> tiles, vector<Spike> spikes, Hole hole, int &_gameState);
    void reset();
    void setLines(vector<SDL_Point> points);
    SDL_Point* getLines();
    void setNumOfLines(int num);
    int getNumOfLines();
    
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
    int index;
    int stroke = 0;
    int bounce = 0;
    int directionX = 1, directionY = 1;
    bool win = false;
    bool swung = false;
    
    // the constant friction that slows down the speed of the ball
    double friction = 0.001;
    vector<Entity> points;
    vector<Entity> powerBar;
    int numOfLines = 0;
    SDL_Point lines[];
};
