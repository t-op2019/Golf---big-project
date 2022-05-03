//
//  Spike.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/28/22.
//

#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Entity.hpp"

class Spike : public Entity {
public:
    Spike(Vector _pos, SDL_Texture* _closeTexture, SDL_Texture* _openTexture, int _interval);
    void setNewTexture(SDL_Texture* _texture);
    int getInterval();
    void setInterval(int _interval);
    bool getOpen();
    void setOpen(bool _isOpen);
    void update(int currentInterval);
private:
    int interval;
    bool isOpen = false;
    SDL_Texture* closeTexture;
    SDL_Texture* openTexture;
};
