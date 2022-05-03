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

int lvl = 0;
// gameState: state of the game
// 0: title screen
// 1: in game
// 2: end screen
// 3: fail stage
int gameState = 1;

bool mouseDown = false;
bool mousePressed = false;

SDL_Event event;

// use to keep track of frame
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double delta = 0;

int counter = 0;

SDL_Texture *background, *playButton, *stages[9], *ball, *ballShadow, *spikeTxture, *holeTxture, *point, *powerMeterForeground, *powerMeterBackground, *powerMeterOverlay, *tileDark32, *tileLight32, *tileDark64, *tileLight64, *spikeTileInactive, *spikeTileActive, *spikeWall, *crackedWall, *stickyWall;
Ball balls[2] = {Ball(Vector(0, 0), ball, point, powerMeterForeground, powerMeterBackground, 0), Ball(Vector(0, 0), ball, point, powerMeterForeground, powerMeterBackground, 1)};
Hole hole = Hole(Vector(0, 0), holeTxture);
vector<Tile> tiles = {};
vector<Spike> spikes = {};
vector<Vector> requirements = {};

void setVariables(SDL_Window* _window, SDL_Renderer* _renderer, const string _windowTitle, int _width, int _height, int _lvl, int& _gameState) {
    window = _window;
    renderer = _renderer;
    windowTitle = _windowTitle;
    width = _width;
    height = _height;
    lvl = _lvl;
    gameState = _gameState;
}

void loadAllTexture() {
    initSDL(window, renderer, windowTitle, width, height);
    const string defaultRoutes = "assets/images/";
    bool stagesLoaded = true;
    
    background = loadTexture(defaultRoutes + "bg.png", renderer);
    ball = loadTexture(defaultRoutes + "ball.png", renderer);
    ballShadow = loadTexture(defaultRoutes + "ball_shadow.png", renderer);
    spikeTxture = loadTexture(defaultRoutes + "spike_active.png", renderer);
    holeTxture = loadTexture(defaultRoutes + "hole.png", renderer);
    playButton = loadTexture(defaultRoutes + "click2start.png", renderer);
    point = loadTexture(defaultRoutes + "point.png", renderer);
    powerMeterForeground = loadTexture(defaultRoutes + "powermeter_fg.png", renderer);
    powerMeterBackground = loadTexture(defaultRoutes + "powermeter_bg.png", renderer);
    powerMeterOverlay = loadTexture(defaultRoutes + "powermeter_overlay.png", renderer);
    tileDark32 = loadTexture(defaultRoutes + "tile32_dark.png", renderer);
    tileDark64 = loadTexture(defaultRoutes + "tile64_dark.png", renderer);
    tileLight32 = loadTexture(defaultRoutes + "tile32_light.png", renderer);
    tileLight64 = loadTexture(defaultRoutes + "tile64_light.png", renderer);
    spikeTileInactive = loadTexture(defaultRoutes + "spike_tile_inactive.png", renderer);
    spikeTileActive = loadTexture(defaultRoutes + "spike_tile_active.png", renderer);
    spikeWall = loadTexture(defaultRoutes + "spike_wall.png", renderer);
    crackedWall = loadTexture(defaultRoutes + "cracked_wall.png", renderer);
    stickyWall = loadTexture(defaultRoutes + "sticky_wall.png", renderer);
    
//    for (int i = 0; i < 9; i++) {
//        stages[i] = loadTexture(defaultRoutes + "hangman" + to_string(i) + ".png", renderer);
//        if (stages[i] == NULL) {
//            stagesLoaded = false;
//            break;
//        }
//    }
    
    if (background == NULL | stagesLoaded == false | playButton == NULL | ball == NULL | ballShadow == NULL | spikeTxture == NULL | holeTxture == NULL | point == NULL | powerMeterForeground == NULL | powerMeterBackground == NULL | powerMeterOverlay == NULL | tileDark64 == NULL | spikeTileActive == NULL | spikeTileInactive == NULL | spikeWall == NULL | crackedWall == NULL | stickyWall == NULL) {
        unloadAllTexture();
        exit(1);
    }
    balls[0] = Ball(Vector(0, 0), ball, point, powerMeterForeground, powerMeterBackground, 0);
    balls[1] = Ball(Vector(0, 0), ball, point, powerMeterForeground, powerMeterBackground, 1);
    hole = Hole(Vector(0, 0), holeTxture);
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
    
    // get controls
        switch (event.type) {
            case SDL_QUIT:
                _isPlaying = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = true;
                    mousePressed = true;
                    if (gameState == 1) {
                        balls[0].update(delta, mouseDown, mousePressed, tiles, spikes, hole, gameState);
                        for (int i = 0; i < spikes.size(); i++) {
                            spikes[i].update(counter);
                        }
                        refresh();
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                    balls[0].setStroke(balls[0].getStroke() + 1);
                }
                break;
        }
    
    if (gameState == 1) {
        balls[0].update(delta, mouseDown, mousePressed, tiles, spikes, hole, gameState);
        for (int i = 0; i < spikes.size(); i++) {
            spikes[i].update(counter);
        }
        refresh();
    }
    
    if (gameState == 3) {
        loadLevels(lvl);
        gameState = 1;
    }
    
    // if ball is shrunk all the way -> win -> next lvl
    if (balls[0].getScale().x < -1) {
        counter = 0;
        balls[0].reset();
        lvl++;
        loadLevels(lvl);
    }
}

void refresh() {
    // clear screen
    SDL_RenderClear(renderer);
    renderBackground();
    renderObject(hole);
    
    // render spiked tiles
    for (Spike spike : spikes) {
        renderObject(spike);
    }
    
    // render ball(s)
    for (Ball ball : balls) {
        if (!ball.hasWon()) {
            renderTexture(ballShadow, renderer, ball.getPos().x, ball.getPos().y + 4);
        }
        // render pointer arrow
        for (Entity& arrow : ball.getPoints()) {
            renderObject(arrow);
        }
        // render powerbar
        for (Entity& powerbar : ball.getPowerBar()) {
            renderObject(powerbar);
        }
        renderTexture(powerMeterOverlay, renderer, ball.getPowerBar().at(0).getPos().x, ball.getPowerBar().at(0).getPos().y);
        // render ball texture
        renderObject(ball);
    }
    
    // render tiles
    for (Tile tile : tiles) {
        renderObject(tile);
    }
    
    renderPresent();
}

void unloadAllTexture() {
    SDL_DestroyTexture(background);
    
    for (int i = 0; i < 9; i++) {
        SDL_DestroyTexture(stages[i]);
    }
    
    quitSDL(window, renderer);
}

void renderPresent() {
    SDL_RenderPresent(renderer);
}

void renderBackground() {
    renderTexture(background, renderer, 0, 0, width, height);
}

void renderObject(Entity& entity) {
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
    SDL_RenderCopyEx(renderer, entity.getTexture(), NULL, &destination, entity.getAngle(), 0, SDL_FLIP_NONE);
}

void renderObject(Entity& entity, SDL_Texture* customTexture) {
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
    
    renderTexture(customTexture, renderer, x, y, w, h);
    SDL_RenderCopyEx(renderer, customTexture, NULL, &destination, entity.getAngle(), 0, SDL_FLIP_NONE);
}

vector<Tile> loadTiles(int lvl) {
    vector<Tile> temp = {};
    switch (lvl) {
        case 0:
            temp.push_back(Tile(Vector(64 * 3, 64 * 3), tileDark64, false, false));
            break;
        case 1:
            temp.push_back(Tile(Vector(64 * 3, 64 * 3), crackedWall, false, true));
        default:
            break;
    }
    return temp;
}

vector<Tile> loadSpikes(int lvl) {
    vector<Tile> temp = {};
    switch (lvl) {
        case 0:
            temp.push_back(Tile(Vector(64 - 8, 64 * 3 - 8), spikeWall, true, false));
            break;
            
        default:
            break;
    }
    return temp;
}

vector<Spike> loadIntervalSpikes(int lvl) {
    vector<Spike> temp = {};
    switch (lvl) {
        case 1:
//            temp.push_back(Spike(Vector(16 + 32 * 3, 16 + 32), spikeTileInactive, spikeTileActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 3, 16 + 32 * 2), spikeTileInactive, spikeTileActive, 100));
//            temp.push_back(Spike(Vector(16 + 32 * 3, 16 + 32 * 3), spikeTileInactive, spikeTileActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 4, 16 + 32), spikeTileInactive, spikeTileActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 4, 16 + 32 * 3), spikeTileInactive, spikeTileActive, 100));
//            temp.push_back(Spike(Vector(16 + 32 * 5, 16 + 32 * 3), spikeTileInactive, spikeTileActive, 100));
            temp.push_back(Spike(Vector(16 + 32 * 5, 16 + 32 * 2), spikeTileInactive, spikeTileActive, 100));
//            temp.push_back(Spike(Vector(16 + 32 * 5, 16 + 32), spikeTileInactive, spikeTileActive, 100));
            break;
            
        default:
            break;
    }
    return temp;
}

void loadLevels(int lvl) {
    balls[0].setVelocity(0, 0);
    balls[0].setScale(1, 1);
    balls[0].setWin(false);
    
    tiles = loadTiles(lvl);
    spikes = loadIntervalSpikes(lvl);
    const vector<Tile> spikes = loadSpikes(lvl);
    for (int i = 0; i < spikes.size(); i++) {
        tiles.push_back(spikes[i]);
    }
    
    switch (lvl) {
        case 0:
            balls[0].setPos(24 + 32 * 4, 24 + 32 * 11);
            hole.setPos(24 + 32 * 4, 24 + 32 * 2);
            break;
            
        case 1:
            balls[0].setPos(24 + 32 * 10, 24 + 32 * 14);
            hole.setPos(24 + 32 * 4, 24 + 32 * 2);
        default:
            break;
    }
}
