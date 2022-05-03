//
//  Tile.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/15/22.
//

#include "Tile.hpp"

Tile::Tile(Vector _pos, SDL_Texture* _texture, bool _isSpike, bool _isCracked) : Entity(_pos, _texture) {
    isSpike = _isSpike;
    isCracked = _isCracked;
}
