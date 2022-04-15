//
//  game_functions.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "game_functions.hpp"

void playGame(bool &isPlaying) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isPlaying = false;
        }
    }
//    cout << "Playing game" << endl;
//    isPlaying = false;
}
