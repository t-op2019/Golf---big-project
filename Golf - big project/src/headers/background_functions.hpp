//
//  background_functions.hpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#pragma once

#include "SDL_Utils.hpp"
#include "level_loader.hpp"
#include "Tile.hpp"
#include "Spike.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Axe.hpp"

using namespace std;

void setVariables(SDL_Window *_window, SDL_Renderer *_renderer, const string _windowTitle, int _width, int _height, int _lvl, int &_gameState, bool *_wonGame, Vector initialPos, Vector initialVelocity);

void loadAllTexture();

void unloadAllTexture();

void loadStartScreen(bool &_isPlaying, SDL_Event _event);

void update(bool &_isPlaying, SDL_Event _event);

void refresh();

void renderPresent();

void renderBackground();

void renderObject(Entity entity);

void renderPowerBar(Entity entity);

void renderArrow(Entity &entity);

void renderSword(Entity &entity);

void renderLevelText(int lvl, int currentStrokes, int currentBounces);

void renderRequirements(int _currentStrokes, int _currentBounces);

void renderReplay();

void renderLose(int loseContext);

void renderStartScreen();
