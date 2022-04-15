//
//  Hole.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/15/22.
//

#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Entity.hpp"

class Hole : public Entity {
public:
    Hole(Vector _pos, SDL_Texture* _texture);
};
