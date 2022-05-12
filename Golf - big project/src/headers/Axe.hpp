//
//  Axe.hpp
//  Golf - big project
//
//  Created by Dư Võ on 5/9/22.
//

#pragma once

#include "Entity.hpp"

class Axe : public Entity {
public:
    Axe(Vector _pos, SDL_Texture* _texture, double _initialAngle, double _rotationRate);
    double getInitialAngle();
    void setInitialAngle(double _initialAngle);
    void update(double delta, bool mouseDown);
    SDL_Rect* getRect();
    void setOrigin(Vector _pos);
    void setEndpoint(Vector _pos);
    Vector getOrigin();
    Vector getEndpoint();
    double getRotationRate();
private:
    double initialAngle;
    double rotationRate;
    SDL_Rect rect;
    Vector origin;
    Vector endpoint;
};
