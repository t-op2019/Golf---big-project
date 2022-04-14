//
//  ball.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "ball.h"
#include <iostream>

using namespace std;

Ball::Ball(SDL_Renderer* _renderer) {
    x = 400;
    y = 300;
    renderer = _renderer;
}

void Ball::helloWorld() {
    cout << "The ball radius is " << Ball::radius << endl;
}
