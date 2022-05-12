//
//  Tile.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/15/22.
//

#include "Tile.hpp"

Tile::Tile(Vector _pos, SDL_Texture* _texture, bool _isSpike, bool _isSticky) : Entity(_pos, _texture) {
    int x = getPos().x + (getFrame().w - getFrame().w * getScale().x) / 2;
    int y = getPos().y + (getFrame().h - getFrame().h * getScale().y) / 2;
    int w = getFrame().w * getScale().x;
    int h = getFrame().h * getScale().y;
    
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    isSpike = _isSpike;
    isSticky = _isSticky;
}

bool Tile::getIsSpike() {
    return isSpike;
}

void Tile::setIsSpike(bool _isSpike) {
    isSpike = _isSpike;
}

bool Tile::getIsSticky() {
    return isSticky;
}

void Tile::setIsSticky(bool _isSticky) {
    isSticky = _isSticky;
}

SDL_Rect* Tile::getRect() {
    return &rect;
}
