//
//  background_functions.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "background_functions.hpp"
#include "render_method.hpp"

// basic background functions (load/unload textures, render and rerender screen
// *********************************************************************************

SDL_Window *window;
SDL_Renderer *renderer;
string windowTitle;
int width, height;

int lvl;
// gameState: state of the game
// 0: title screen
// 1: in game
// 2: end screen
// 3: fail stage
int gameState;

// loseContext: reason for losing
// 1: maximum strokes exceeded
// 2: maximum bounces exceeded
// 3: touched spike
// 4: touched spinning blade
int loseContext = 0;

bool *wonGame = NULL;

bool mouseDown = false;
bool mousePressed = false;

SDL_Event event;

// use to keep track of frame
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double delta = 0;

// interval counter
int counter = 0;

// current position of the hole
Vector currentHolePos = Vector(0, 0);

Vector initialBallPos = Vector(0, 0);
Vector initialBallVelocity = Vector(0, 0);

SDL_Texture *background, *playButton, *ballTxture, *ballShadow, *holeTxture, *point, *powerBar, *powerBarBg, *wall, *spikeTileInactive, *spikeTileActive, *spikeWall, *stickyWall, *axe;

Ball ball = Ball(Vector(0, 0), ballTxture, point, powerBar, powerBarBg);
vector<Ball> balls = {};
Hole hole = Hole(Vector(0, 0), holeTxture);
vector<Tile> tiles = {};
vector<Spike> spikes = {};
vector<Axe> axes = {};

// requirements to pass the stage
// requirements.x: maximum number of strokes
// requirements.y: maximum number of bounces
Vector requirements = Vector(0, 0);

void setVariables(SDL_Window *_window, SDL_Renderer *_renderer, const string _windowTitle, int _width, int _height, int _lvl, int &_gameState, bool *_wonGame, Vector initialPos, Vector initialVelocity)
{
    window = _window;
    renderer = _renderer;
    windowTitle = _windowTitle;
    width = _width;
    height = _height;
    lvl = _lvl;
    gameState = _gameState;
    wonGame = _wonGame;
    initialBallPos = Vector(initialPos.x, initialPos.y);
    initialBallVelocity = Vector(initialVelocity.x, initialVelocity.y);
}

// load all neccessary textures
void loadAllTexture()
{
    // default path to images folder
    const string defaultRoutes = "src/assets/images/";

    background = loadTexture(defaultRoutes + "bg.png", renderer);
    ballTxture = loadTexture(defaultRoutes + "ball.png", renderer);
    ballShadow = loadTexture(defaultRoutes + "ball_shadow.png", renderer);
    holeTxture = loadTexture(defaultRoutes + "hole.png", renderer);
    playButton = loadTexture(defaultRoutes + "click2start.png", renderer);
    point = loadTexture(defaultRoutes + "point.png", renderer);
    powerBar = loadTexture(defaultRoutes + "power_bar.png", renderer);
    powerBarBg = loadTexture(defaultRoutes + "power_bar_bg.png", renderer);
    wall = loadTexture(defaultRoutes + "tile64_dark.png", renderer);
    spikeTileInactive = loadTexture(defaultRoutes + "spike_tile_inactive.png", renderer);
    spikeTileActive = loadTexture(defaultRoutes + "spike_tile_active.png", renderer);
    spikeWall = loadTexture(defaultRoutes + "spike_wall.png", renderer);
    stickyWall = loadTexture(defaultRoutes + "sticky_wall.png", renderer);
    axe = loadTexture(defaultRoutes + "axe.png", renderer);

    if (background == NULL | playButton == NULL | ballTxture == NULL | ballShadow == NULL | holeTxture == NULL | point == NULL | powerBar == NULL | powerBarBg == NULL | wall == NULL | spikeTileActive == NULL | spikeTileInactive == NULL | spikeWall == NULL | stickyWall == NULL)
    {
        unloadAllTexture();
        exit(1);
    }

    Ball ballSet = Ball(Vector(0, 0), ballTxture, point, powerBar, powerBarBg);
    balls.push_back(ballSet);
    // ball = ballSet;
    hole = Hole(Vector(0, 0), holeTxture);
    loadLevel(lvl, tiles, spikes, axes, balls[0], hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
}

// unload all textures and quit SDL
void unloadAllTexture()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(ballTxture);
    SDL_DestroyTexture(ballShadow);
    SDL_DestroyTexture(holeTxture);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(point);
    SDL_DestroyTexture(powerBar);
    SDL_DestroyTexture(powerBarBg);
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(spikeTileActive);
    SDL_DestroyTexture(spikeTileInactive);
    SDL_DestroyTexture(stickyWall);
    SDL_DestroyTexture(spikeWall);
    SDL_DestroyTexture(axe);

    quitSDL(window, renderer);
}

void loadStartScreen(bool &_isPlaying, SDL_Event _event)
{
    event = _event;
}

// update states of objects in the game
void update(bool &_isPlaying, SDL_Event _event)
{
    event = _event;
    // update frame
    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    delta = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.15;
    counter++;
    //    cout << counter << endl;
    mousePressed = false;

    // if the number of strokes or bounces exceeds the maximum number, reset the level
    if (balls[0].getStroke() > requirements.x || balls[0].getBounce() > requirements.y)
    {
        loseContext = balls[0].getStroke() > requirements.x ? 1 : 2;
        gameState = 3;
        // balls[0].reset();
    }

    // get controls
    if (interpretKey(&event.key) == "Return" && gameState == 0)
    {
        lvl = 0;
        gameState = 1;
        loseContext = 0;
        balls[0].reset();
        loadLevel(lvl, tiles, spikes, axes, balls[0], hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
    }

    // reset level if player hit R key
    if (interpretKey(&event.key) == "R")
    {
        if (*wonGame || gameState == 0)
        {
            gameState = 0;
            lvl = -1;
            *wonGame = false;
        }
        else
        {
            gameState = 1;
        }
        loseContext = 0;
        balls[0].reset();
        loadLevel(lvl, tiles, spikes, axes, balls[0], hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
    }

    // get other events
    switch (event.type)
    {
    case SDL_QUIT:
        _isPlaying = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            mouseDown = true;
            mousePressed = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            mouseDown = false;
            balls[0].setSwung(true);
            balls[0].setStroke(balls[0].getStroke() + 1);
        }
        break;
    }

    if (gameState == 0)
    {
        balls[0].update(renderer, delta, mouseDown, mousePressed, tiles, spikes, axes, hole, gameState, loseContext);
    }

    // if is in the game, update ball and other objects
    if (gameState == 1)
    {
        balls[0].update(renderer, delta, mouseDown, mousePressed, tiles, spikes, axes, hole, gameState, loseContext);
        // update spinning spikes
        for (int i = 0; i < axes.size(); i++)
        {
            axes[i].update(delta, mouseDown);
        }
        // update spiked tiles
        for (int i = 0; i < spikes.size(); i++)
        {
            spikes[i].update(counter);
        }
        balls[0].resetSwung(counter);
    }

    // if failed the level, stop the ball
    if (gameState == 3)
    {
        balls[0].reset();
        // loadLevel(lvl, tiles, spikes, axes, balls[0], hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
        // gameState = 1;
    }

    if (balls[0].hasWon() && lvl == 2)
    {
        *wonGame = true;
    }
    else if (balls[0].getScale().x < -1)
    {
        //        if (lvl != 2) {
        counter = 0;
        balls[0].reset();
        lvl++;
        loadLevel(lvl, tiles, spikes, axes, balls[0], hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
    };

    // if ball is shrunk all the way -> win -> next lvl

    refresh();
}

void refresh()
{
    // clear screen
    //    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, width, height);

    // render hole
    hole.setPos(currentHolePos.x, currentHolePos.y);
    renderObject(hole, renderer);

    // render spiked tiles
    for (Spike spike : spikes)
    {
        renderObject(spike, renderer);
    }

    // render tiles
    for (Tile tile : tiles)
    {
        renderObject(tile, renderer);
    }

    // render level text
    if (gameState != 0)
    {
        renderLevelText(lvl, balls[0].getStroke(), balls[0].getBounce(), renderer, requirements);
    }
    else
    {
        renderStartScreen(renderer, height);
    }

    // render ball
    if (!balls[0].hasWon())
    {
        renderTexture(ballShadow, renderer, balls[0].getPos().x, balls[0].getPos().y + 4);
    }
    // render pointer arrow
    for (Entity &arrow : balls[0].getPoints())
    {
        renderArrow(arrow, renderer);
    }
    // render powerbar
    for (Entity &powerbar : balls[0].getPowerBar())
    {
        renderPowerbar(powerbar, renderer);
    }
    // render ball texture
    renderObject(balls[0], renderer);

    // render spinning axes
    for (Axe &axe : axes)
    {
        renderSword(axe, renderer);
    }

    if (loseContext > 0)
    {
        renderLose(loseContext, renderer, height);
        renderReplay(renderer, height);
    }

    if (*wonGame)
    {
        renderText(36, "YOU HAVE WON!", renderer, width / 2 - 100, height / 2);
        renderReplay(renderer, height);
    }

    SDL_RenderPresent(renderer);
}
