//
//  Entity.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

class Vector {
public:
    Vector()
    :x(0.0f), y(0.0f)
    {}
    
    Vector(double _x, double _y)
    :x(_x), y(_y)
    {}
    
    void print() {
        cout << x << ", " << y << endl;
    };
    
    double x, y;
};

class Entity {
public:
    Entity(Vector pos, SDL_Texture* texture);
    Vector getPos();
    void setPos(double x, double y);
    Vector getScale();
    void setScale(double w, double h);
    double getAngle();
    void setAngle(double angle);
    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* _texture);
    void update(double delta);
    SDL_Rect getFrame();
    
private:
    Vector pos;
    Vector scale = Vector(1, 1);
    double angle;
    SDL_Rect currentFrame;
    SDL_Texture* texture;
};
