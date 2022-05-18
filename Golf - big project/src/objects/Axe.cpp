//
//  Axe.cpp
//  Golf - big project
//
//  Created by Dư Võ on 5/9/22.
//

#include "Axe.hpp"

Axe::Axe(Vector _pos, SDL_Texture *_texture, double _initialAngle, double _rotationRate) : Entity(_pos, _texture)
{
    double renderAngle = abs(_initialAngle - 90);
    origin = Vector(_pos.x + 5, _pos.y + 100);
    double radiantAngle = _initialAngle / 180 * M_PI;
    endpoint = Vector(origin.x + (SDL_cos(radiantAngle) * 100), origin.y - (SDL_sin(radiantAngle) * 100));
    setPos(_pos.x, _pos.y);
    setAngle(renderAngle);
    initialAngle = _initialAngle;
    rotationRate = _rotationRate;

    int x = getPos().x + (getFrame().w - getFrame().w * getScale().x) / 2;
    int y = getPos().y + (getFrame().h - getFrame().h * getScale().y) / 2;
    int w = getFrame().w * getScale().x;
    int h = getFrame().h * getScale().y;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

double Axe::getInitialAngle()
{
    return initialAngle;
}

void Axe::setInitialAngle(double _initialAngle)
{
    initialAngle = _initialAngle;
}

void Axe::update(double delta, bool mouseDown)
{
    double currentAngle = getAngle();
    if (mouseDown)
    {
        setAngle(currentAngle + delta * 0.25 * rotationRate);
        initialAngle = currentAngle + delta * 0.25 * rotationRate;
    }
    else
    {
        setAngle(currentAngle + delta * rotationRate);
        initialAngle = currentAngle + delta * 0.25 * rotationRate;
    }

    double newRadiantAngle = (initialAngle - 90) / 180 * M_PI;
    endpoint = Vector(origin.x + (SDL_cos(newRadiantAngle) * 100), origin.y + (SDL_sin(newRadiantAngle) * 100));

    //    cout << endpoint.x << " " << endpoint.y << endl;
}

SDL_Rect *Axe::getRect()
{
    return &rect;
}

void Axe::setOrigin(Vector _pos)
{
    origin = _pos;
}

void Axe::setEndpoint(Vector _pos)
{
    endpoint = _pos;
}

Vector Axe::getOrigin()
{
    return origin;
}

Vector Axe::getEndpoint()
{
    return endpoint;
}

double Axe::getRotationRate()
{
    return rotationRate;
}

void Axe::setRotationRate(double _rotationRate)
{
    rotationRate = _rotationRate;
}
