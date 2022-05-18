//
//  render_method.cpp
//  Golf - big project
//
//  Created by Dư Võ on 5/19/22.
//

#include "render_method.hpp"

void renderObject(Entity entity, SDL_Renderer *renderer)
{
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

void renderPowerbar(Entity entity, SDL_Renderer *renderer)
{
    SDL_Rect source;
    source.x = 0;
    source.y = 0;

    SDL_QueryTexture(entity.getTexture(), NULL, NULL, &source.w, &source.h);
    source.w *= entity.getScale().x;

    SDL_Rect destination;
    destination.x = entity.getPos().x;
    destination.y = entity.getPos().y;
    destination.w = source.w;
    destination.h = source.h;

    SDL_RenderCopy(renderer, entity.getTexture(), &source, &destination);
}

void renderArrow(Entity entity, SDL_Renderer *renderer)
{
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

void renderSword(Entity entity, SDL_Renderer *renderer)
{
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

    // rotation pivot
    SDL_Point rotationCenter = {5, 100};

    SDL_RenderCopyEx(renderer, entity.getTexture(), NULL, &destination, entity.getAngle(), &rotationCenter, SDL_FLIP_NONE);
}

void renderRequirements(int _currentStrokes, int _currentBounces, SDL_Renderer *renderer, Vector requirements)
{
    string strokes = to_string((int)requirements.x);
    string currentStrokes = to_string(_currentStrokes);
    string bounces = to_string((int)requirements.y);
    string currentBounces = to_string(_currentBounces);

    string stringTxt = "Strokes: " + currentStrokes + " / " + strokes + "   Bounces: " + currentBounces + " / " + bounces;

    const char *text = stringTxt.c_str();

    renderText(28, text, renderer, 10, 36);
}

void renderLevelText(int lvl, int currentStrokes, int currentBounces, SDL_Renderer *renderer, Vector requirements)
{
    string level = to_string(lvl);
    string stringTxt = "LEVEL " + level;

    const char *text = stringTxt.c_str();
    renderText(36, text, renderer, 10, 10);
    renderRequirements(currentStrokes, currentBounces, renderer, requirements);
}

void renderReplay(SDL_Renderer *renderer, int height)
{
    renderTextCenter("Press R to play again", renderer, height / 2 + 30);
}

void renderLose(int loseContext, SDL_Renderer *renderer, int height)
{
    const string loseMessage = loseContext == 1 ? "Maximum strokes exceeded" : loseContext == 2 ? "Maximum bounces exceeded"
                                                                           : loseContext == 3   ? "Touched spike"
                                                                                                : "Touched spinning blade";
    renderTextCenter(loseMessage.c_str(), renderer, height / 2);
}

void renderStartScreen(SDL_Renderer *renderer, int height)
{
    renderTextCenter("Dungeon Golf", renderer, height / 2 - 100, true);
    renderTextCenter("Press ENTER to start", renderer, height / 2);
}
