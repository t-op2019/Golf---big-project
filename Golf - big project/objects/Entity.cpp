//
//  Entity.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "Entity.hpp"

Entity::Entity(Vector _pos, SDL_Texture* _texture) :pos(_pos), texture(_texture) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(_texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTexture() {
    return texture;
}

double Entity::getAngle() {
    return angle;
}

Vector Entity::getPos() {
    return pos;
}

void Entity::setPos(double x, double y) {
    pos.x = x;
    pos.y = y;
}

void Entity::setAngle(double _angle) {
    angle = _angle;
}

Vector Entity::getScale() {
    return scale;
}

void Entity::setScale(double w, double h) {
    scale.x = w;
    scale.y = h;
}

SDL_Rect Entity::getFrame() {
    return currentFrame;
}
