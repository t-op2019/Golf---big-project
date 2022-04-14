//
//  ball.h
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include <SDL2/SDL.h>

class Ball {
public:
    Ball(SDL_Renderer* _renderer);
    ~Ball();
    SDL_Renderer renderer;
    int radius, x, y;
    void helloWorld();
};
