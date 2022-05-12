//
//  Tile.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/15/22.
//

#pragma once

#include "Entity.hpp"

class Tile : public Entity {
public:
    Tile(Vector _pos, SDL_Texture* _texture, bool _isSpike, bool _isCracked);
    SDL_Rect* getRect();
    bool getIsSpike();
    void setIsSpike(bool _isSpike);
    bool getIsSticky();
    void setIsSticky(bool _isSticky);
private:
    bool isSpike;
    bool isSticky;
    SDL_Rect rect;
};

