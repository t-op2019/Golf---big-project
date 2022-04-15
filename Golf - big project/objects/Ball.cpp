//
//  Ball.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "Ball.hpp"

#include <cmath>

Ball::Ball(Vector _pos, SDL_Texture* _texture, SDL_Texture* _pointArrowTexture, SDL_Texture* _powerMeterForeground, SDL_Texture* _powerMeterBackground, int _index) :Entity(_pos, _texture) {
    index = _index;
    points.push_back(Entity(Vector(-64, -64), _pointArrowTexture));
    powerBar.push_back(Entity(Vector(-64, -64), _powerMeterBackground));
    powerBar.push_back(Entity(Vector(-64, -64), _powerMeterForeground));
}

vector<Entity> Ball::getPoints() {
    return points;
}

vector<Entity> Ball::getPowerBar() {
    return powerBar;
}

int Ball::getStroke() {
    return stroke;
}

Vector Ball::getVelocity() {
    return velocity;
}

void Ball::setVelocity(double x, double y) {
    velocity.x = x;
    velocity.y = y;
}

Vector Ball::getInitialMousePos() {
    return initialMousePos;
}

void Ball::setInitialMousePos(double x, double y) {
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Ball::setLauchVelocity(double x, double y) {
    lauchedVelocity.x = x;
    lauchedVelocity.y = y;
}

bool Ball::hasWon() {
    return win;
}

void Ball::setWin(bool _win) {
    win = _win;
}


// function for updating the ball positions when swung, hit walls and hit goals
void Ball::update(double delta, bool isMouseDown, bool isMousePressed, vector<Tile> tiles, vector<Hole> holes) {
    if (win) {
        // shifts the position of ball to the center of hole's position by 0.1 * delta if the ball's texture is in the hole's texture
        if (getPos().x < target.x) {
            setPos(getPos().x + 0.1 * delta, getPos().y);
        } else if (getPos().x > target.x) {
            setPos(getPos().x - 0.1 * delta, getPos().y);
        }
        if (getPos().y < target.y) {
            setPos(getPos().x, getPos().y + 0.1 * delta);
        } else if (getPos().y > target.y) {
            setPos(getPos().x, getPos().y - 0.1 * delta);
        }
        
        // decrease the size the of ball gradually as it enters the hole
        setScale(getScale().x - 0.001 * delta, getScale().y - 0.001 * delta);
    }
    
    // loop through all the holes
    for (Hole hole : holes) {
        // bias range for the ball to hit the target hole
        if (getPos().x + 4 > hole.getPos().x && getPos().x < hole.getPos().x + 4 && getPos().y + 4 > hole.getPos().y && getPos().y < hole.getPos().y + 4) {
            setWin(true);
            target.x = hole.getPos().x;
            target.y = hole.getPos().y + 4;
        }
    }
    
    if (isMousePressed && canMove) {
        int mouseX = 0, mouseY = 0;
        // get the mouse position and set its coordinates onto mouseX and mouseY
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePos(mouseX, mouseY);
    }
    
    if (isMouseDown && canMove) {
        int mouseX = 0, mouseY = 0;
        // get the mouse position and set its coordinates onto mouseX and mouseY
        SDL_GetMouseState(&mouseX, &mouseY);
        // change the value of powerConstant to change the velocity limit (the bigger the powerConstant, the harder the player can swing)
        const int powerConstant = 150;
        // calculate velocity using the current and initial mouse potitions
        setVelocity((mouseX - getInitialMousePos().x) / -powerConstant, (mouseY - getInitialMousePos().y) / -powerConstant);
        setLauchVelocity((mouseX - getInitialMousePos().x) / -powerConstant, (mouseY - getInitialMousePos().y) / -powerConstant);
        // calculate velocity value
        velocityValue = SDL_sqrt(SDL_pow(SDL_abs(getVelocity().x), 2) + SDL_pow(SDL_abs(getVelocity().y), 2));
        lauchedVelocityValue = velocityValue;
        
        // setup pointing arrow's direction
        points.at(0).setPos(getPos().x, getPos().y - 24);
        points.at(0).setAngle(SDL_atan2(velocity.y, velocity.x) * (180 / M_PI) + 90);
        
        // determine the direction of x and y of the velocity (whether it be positive or negative) to change its direction
        directionX = velocity.x / abs(velocity.x);
        directionY = velocity.y / abs(velocity.y);
        
        // setup the power meter bar
        powerBar.at(0).setPos(getPos().x + 40, getPos().y - 32);
        powerBar.at(1).setPos(getPos().x + 44, getPos().y + 4 - 32 * powerBar.at(1).getScale().y);
        
        // if the player's swing power exceeds the limit, set the velocity value to be 1 (at limit)
        if (velocityValue > 1) {
            velocityValue = 1;
            lauchedVelocityValue = 1;
        }
        
        // set the power meter bar according to the velocity value (scale y means how long the meter will be)
        powerBar.at(1).setScale(1, velocityValue / 1);
    } else {
        points.at(0).setPos(-64, -64);
        powerBar.at(0).setPos(-64, -64);
        powerBar.at(0).setPos(-64, -64);
    }
}
