//
//  Line.cpp
//  Golf - big project
//
//  Created by Dư Võ on 5/3/22.
//

#include "Line.hpp"

Line::Line(Vector _pos, Vector _destination, SDL_Texture* _texture) : Entity(_pos, _texture) {
    destination = _destination;
}

Vector Line::getDestination() {
    return destination;
}

void Line::setDestination(Vector _destination) {
    destination = _destination;
}

void Line::setLength(double _length) {
    length = _length;
}

vector<SDL_Point> updateLine(vector<Tile> tiles, Vector velocity, Vector startPos) {
    // set start and end position of the line to be drawn
    Vector tempVelocity = Vector(velocity.x * 1, velocity.y * 1);
//    Vector startPos = getPos();
    SDL_Point startPoint = {(int)startPos.x, (int)startPos.y};
    // colection of points to draw
    vector<SDL_Point> points = {};
    points.push_back(startPoint);
    
    const int lineLength = 300;
    
    for (int i = 1; i <= lineLength; i++) {
        unsigned long currentPointsSize = points.size();
        Vector endPos = Vector(points[currentPointsSize - 1].x + tempVelocity.x, points[currentPointsSize - 1].y + tempVelocity.y);
        SDL_Point currentPoint = {(int)endPos.x, (int)endPos.y};
        
        for (Tile tile : tiles) {
            // if the destination point is inside of a tile, then change the velocity direction
            if (SDL_PointInRect(&currentPoint, tile.getRect())) {
                // change velocity direction
                if (currentPoint.x > (*tile.getRect()).x && currentPoint.x < (*tile.getRect()).x + (*tile.getRect()).w) {
                    tempVelocity.y *= -1;
                }
                else if (currentPoint.y > (*tile.getRect()).y | currentPoint.y < (*tile.getRect()).y + (*tile.getRect()).h) {
                    tempVelocity.x *= -1;
                }
                points.push_back(currentPoint);
            }
        }
        if (i == lineLength) {
            points.push_back(currentPoint);
        }
    }
    return points;
}
