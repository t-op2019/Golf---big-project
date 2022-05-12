//
//  background_functions.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "background_functions.hpp"

// basic background functions (load/unload textures, render and rerender screen
// *********************************************************************************

SDL_Window* window;
SDL_Renderer* renderer;
string windowTitle;
int width, height;

int lvl;
// gameState: state of the game
// 0: title screen
// 1: in game
// 2: end screen
// 3: fail stage
int gameState = 1;

bool* wonGame = NULL;

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

SDL_Texture *background, *playButton, *ballTxture, *ballShadow, *holeTxture, *point, *powerBar, *powerBarBg, *wall, *spikeTileInactive, *spikeTileActive, *spikeWall, *stickyWall, *axe;

Ball ball = Ball(Vector(0, 0), ballTxture, point, powerBar, powerBarBg, 0);
Hole hole = Hole(Vector(0, 0), holeTxture);
vector<Tile> tiles = {};
vector<Spike> spikes = {};
vector<Axe> axes = {};

// requirements to pass the stage
// requirements.x: maximum number of strokes
// requirements.y: maximum number of bounces
Vector requirements = Vector(0, 0);

void setVariables(SDL_Window* _window, SDL_Renderer* _renderer, const string _windowTitle, int _width, int _height, int _lvl, int& _gameState, bool* _wonGame) {
    window = _window;
    renderer = _renderer;
    windowTitle = _windowTitle;
    width = _width;
    height = _height;
    lvl = _lvl;
    gameState = _gameState;
    wonGame = _wonGame;
}

void loadAllTexture() {
    initSDL(window, renderer, windowTitle, width, height);
    const string defaultRoutes = "assets/images/";
    
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
    
    if (background == NULL | playButton == NULL | ballTxture == NULL | ballShadow == NULL | holeTxture == NULL | point == NULL | powerBar == NULL | powerBarBg == NULL | wall == NULL | spikeTileActive == NULL | spikeTileInactive == NULL | spikeWall == NULL | stickyWall == NULL) {
        unloadAllTexture();
        exit(1);
    }
    
    ball = Ball(Vector(0, 0), ballTxture, point, powerBar, powerBarBg, 0);
    hole = Hole(Vector(0, 0), holeTxture);
    loadLevel(lvl, tiles, spikes, axes, ball, hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
}

void unloadAllTexture() {
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

void update(bool& _isPlaying, SDL_Event _event) {
    event = _event;
    // update frame
    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    delta = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.15;
    counter++;
    //    cout << counter << endl;
    mousePressed = false;
    
    // if the number of strokes or bounces exceeds the maximum number, reset the level
    if (ball.getStroke() > requirements.x || ball.getBounce() > requirements.y) {
        gameState = 3;
        ball.reset();
    }
    
    // get controls
    
    // reset level if player hit R key
    if (interpretKey(&event.key) == "R") {
        if (*wonGame) {
            lvl = -1;
            gameState = 1;
            *wonGame = false;
        } else {
            gameState = 3;
        }
        ball.reset();
    }
    
    // get other events
    switch (event.type) {
        case SDL_QUIT:
            _isPlaying = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseDown = true;
                mousePressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseDown = false;
                ball.setSwung(true);
                ball.setStroke(ball.getStroke() + 1);
            }
            break;
    }
    
    if (gameState == 1) {
        ball.update(renderer, delta, mouseDown, mousePressed, tiles, spikes, axes, hole, gameState);
        // update spinning spikes
        for (int i = 0; i < axes.size(); i++) {
            axes[i].update(delta, mouseDown);
        }
        // update spiked tiles
        for (int i = 0; i < spikes.size(); i++) {
            spikes[i].update(counter);
        }
        ball.resetSwung(counter);
    }
    
    if (gameState == 3) {
        loadLevel(lvl, tiles, spikes, axes, ball, hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
        gameState = 1;
    }
    
    if (ball.hasWon() && lvl == 2) {
        *wonGame = true;
    } else if (ball.getScale().x < -1) {
        //        if (lvl != 2) {
        counter = 0;
        ball.reset();
        lvl++;
        loadLevel(lvl, tiles, spikes, axes, ball, hole, currentHolePos, requirements, wall, spikeWall, stickyWall, spikeTileActive, spikeTileInactive, axe);
        
    };
    
    // if ball is shrunk all the way -> win -> next lvl
    
    
    refresh();
}

void refresh() {
    // clear screen
    //    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    renderBackground();
    
    // render hole
    hole.setPos(currentHolePos.x, currentHolePos.y);
    renderObject(hole);
    
    // render spiked tiles
    for (Spike spike : spikes) {
        renderObject(spike);
    }
    
    // render tiles
    for (Tile tile : tiles) {
        renderObject(tile);
    }
    
    // render level text
    renderLevelText(lvl, ball.getStroke(), ball.getBounce());
    
    // render ball
    if (!ball.hasWon()) {
        renderTexture(ballShadow, renderer, ball.getPos().x, ball.getPos().y + 4);
    }
    // render pointer arrow
    for (Entity& arrow : ball.getPoints()) {
        renderArrow(arrow);
    }
    // render powerbar
    for (Entity& powerbar : ball.getPowerBar()) {
        renderPowerBar(powerbar);
    }
    // render ball texture
    renderObject(ball);
    
    // render spinning axes
    for (Axe axe : axes) {
        renderSword(axe);
        //        Ball testBall = Ball(Vector(axe.getEndpoint().x, axe.getEndpoint().y), ballTxture, point, powerBar, powerBarBg, 1);
        //        renderObject(testBall);
    }
    
    // render path prediction line
    //    int numOfLines = ball.getNumOfLines();
    //    if (numOfLines > 0) {
    //        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    //        SDL_RenderDrawLines(renderer, ball.getLines(), numOfLines);
    //    }
    
    if (*wonGame) {
        //        cout << "what the fuck" << endl;
        renderText(36, "YOU HAVE WON!", renderer, width / 2 - 100, height / 2);
        renderText(36, "Press R to play again", renderer, width / 2 - 120, height / 2 + 30);
    }
    
    renderPresent();
}

void renderPresent() {
    SDL_RenderPresent(renderer);
}

void renderBackground() {
    renderTexture(background, renderer, 0, 0, width, height);
}

void renderObject(Entity entity) {
    SDL_Rect destination;
    // get position x and y of the object and centers it with various scales
    int x = entity.getPos().x + (entity.getFrame().w - entity.getFrame().w * entity.getScale().x) / 2;
    int y = entity.getPos().y + (entity.getFrame().h - entity.getFrame().h * entity.getScale().y) / 2;
    // get width and height of the object (calculated after being scaled)
    int w = entity.getFrame().w * entity.getScale().x;
    int h = entity.getFrame().h * entity.getScale().y;
    
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    
    renderTexture(entity.getTexture(), renderer, x, y, w, h);
}

void renderPowerBar(Entity entity) {
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    //    source.w;
    //    source.h;
    
    SDL_QueryTexture(entity.getTexture(), NULL, NULL, &source.w, &source.h);
    source.w *= entity.getScale().x;
    
    SDL_Rect destination;
    destination.x = entity.getPos().x;
    destination.y = entity.getPos().y;
    destination.w = source.w;
    destination.h = source.h;
    
    SDL_RenderCopy(renderer, entity.getTexture(), &source, &destination);
}

void renderArrow(Entity& entity) {
    SDL_Rect destination;
    // get position x and y of the object and centers it with various scales
    int x = entity.getPos().x + (entity.getFrame().w - entity.getFrame().w * entity.getScale().x) / 2;
    int y = entity.getPos().y + (entity.getFrame().h - entity.getFrame().h * entity.getScale().y) / 2;
    // get width and height of the object (calculated after being scaled)
    int w = entity.getFrame().w * entity.getScale().x;
    int h = entity.getFrame().h * entity.getScale().y;
    
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    
    SDL_RenderCopyEx(renderer, entity.getTexture(), NULL, &destination, entity.getAngle(), 0, SDL_FLIP_NONE);
}

void renderSword(Entity& entity) {
    SDL_Rect destination;
    // get position x and y of the object and centers it with various scales
    int x = entity.getPos().x + (entity.getFrame().w - entity.getFrame().w * entity.getScale().x) / 2;
    int y = entity.getPos().y + (entity.getFrame().h - entity.getFrame().h * entity.getScale().y) / 2;
    // get width and height of the object (calculated after being scaled)
    int w = entity.getFrame().w * entity.getScale().x;
    int h = entity.getFrame().h * entity.getScale().y;
    
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    
    SDL_Point rotationCenter = {5, 100};
    
    SDL_RenderCopyEx(renderer, entity.getTexture(), NULL, &destination, entity.getAngle(), &rotationCenter, SDL_FLIP_NONE);
}

void renderLevelText(int lvl, int currentStrokes, int currentBounces) {
    string level = to_string(lvl);
    string stringTxt = "LEVEL " + level;
    
    const char* text = stringTxt.c_str();
    renderText(36, text, renderer, 20, 12);
    renderRequirements(currentStrokes, currentBounces);
}

void renderRequirements(int _currentStrokes, int _currentBounces) {
    string strokes = to_string((int)requirements.x);
    string currentStrokes = to_string(_currentStrokes);
    string bounces = to_string((int)requirements.y);
    string currentBounces = to_string(_currentBounces);
    
    string stringTxt = "Strokes: " + currentStrokes + " / " + strokes + "   Bounces: " + currentBounces + " / " + bounces;
    
    const char* text = stringTxt.c_str();
    
    renderText(28, text, renderer, width - 320, 16);
}
