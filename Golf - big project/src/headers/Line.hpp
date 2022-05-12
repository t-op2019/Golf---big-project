//
//  Line.hpp
//  Golf - big project
//
//  Created by Dư Võ on 5/3/22.
//

#pragma once

#include "Tile.hpp"

using namespace std;

class Line : public Entity {
public:
    Line(Vector _pos, Vector _destination, SDL_Texture* _texture);
    Vector getDestination();
    void setDestination(Vector _destination);
    void setLength(double _length);
private:
    double length;
    Vector destination;
};

vector<SDL_Point> updateLine(vector<Tile> tiles, Vector velocity, Vector startPos);
