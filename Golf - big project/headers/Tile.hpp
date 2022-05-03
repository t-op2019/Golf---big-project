//
//  Tile.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/15/22.
//

#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Entity.hpp"

class Tile : public Entity {
public:
    Tile(Vector _pos, SDL_Texture* _texture, bool _isSpike, bool _isCracked);
    bool isSpike;
    bool isCracked;
};

