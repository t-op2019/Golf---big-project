//
//  render_method.hpp
//  Golf - big project
//
//  Created by Dư Võ on 5/19/22.
//

#pragma once

#include <iostream>
#include "Entity.hpp"
#include "SDL_Utils.hpp"

using namespace std;

void renderObject(Entity entity, SDL_Renderer *renderer);

void renderPowerbar(Entity entity, SDL_Renderer *renderer);

void renderArrow(Entity entity, SDL_Renderer *renderer);

void renderSword(Entity entity, SDL_Renderer *renderer);

void renderLevelText(int lvl, int currentStrokes, int currentBounces, SDL_Renderer *renderer, Vector requirements);

void renderReplay(SDL_Renderer *renderer, int height);

void renderLose(int loseContext, SDL_Renderer *renderer, int height);

void renderStartScreen(SDL_Renderer *renderer, int height);
