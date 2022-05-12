//
//  Spike.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/28/22.
//

#include "Spike.hpp"

Spike::Spike(Vector _pos, SDL_Texture* _closeTexture, SDL_Texture* _openTexture, int _interval) : Entity(_pos, _closeTexture) {
    interval = _interval;
    closeTexture = _closeTexture;
    openTexture = _openTexture;
};

void Spike::setNewTexture(SDL_Texture* _texture) {
    setTexture(_texture);
}

bool Spike::getOpen() {
    return isOpen;
}

void Spike::setOpen(bool _isOpen) {
    isOpen = _isOpen;
}

int Spike::getInterval() {
    return interval;
}

void Spike::setInterval(int _interval) {
    interval = _interval;
}

void Spike::update(int currentInterval) {
    if (currentInterval % interval == 0) {
        setOpen(!isOpen);
        setNewTexture(isOpen ? openTexture : closeTexture);
    }
}
