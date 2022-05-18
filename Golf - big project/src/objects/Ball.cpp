//
//  Ball.cpp
//  Golf - big project
//
//  Created by Dư Võ on 4/14/22.
//

#include "Ball.hpp"

Ball::Ball(Vector _pos, SDL_Texture *_texture, SDL_Texture *_pointArrowTexture, SDL_Texture *_powerMeterForeground, SDL_Texture *_powerMeterBackground) : Entity(_pos, _texture)
{
    int x = getPos().x + (getFrame().w - getFrame().w * getScale().x) / 2;
    int y = getPos().y + (getFrame().h - getFrame().h * getScale().y) / 2;
    int w = getFrame().w * getScale().x;
    int h = getFrame().h * getScale().y;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    points.push_back(Entity(Vector(-699, -699), _pointArrowTexture));
    powerBar.push_back(Entity(Vector(-699, -699), _powerMeterBackground));
    powerBar.push_back(Entity(Vector(-699, -699), _powerMeterForeground));
}

SDL_Rect *Ball::getRect(int x, int y)
{
    rect.x = x;
    rect.y = y;
    return &rect;
}

vector<Entity> Ball::getPoints()
{
    return points;
}

vector<Entity> Ball::getPowerBar()
{
    return powerBar;
}

int Ball::getStroke()
{
    return stroke;
}

int Ball::getBounce()
{
    return bounce;
}

void Ball::setStroke(int _stroke)
{
    stroke = _stroke;
}

void Ball::setBounce(int _bounce)
{
    bounce = _bounce;
}

Vector Ball::getVelocity()
{
    return velocity;
}

Vector Ball::getArrowVelocity()
{
    return arrowVelocity;
}

void Ball::setVelocity(double x, double y)
{
    velocity.x = x;
    velocity.y = y;
}

void Ball::setArrowVelocity(double x, double y)
{
    arrowVelocity.x = x;
    arrowVelocity.y = y;
}

Vector Ball::getInitialMousePos()
{
    return initialMousePos;
}

void Ball::setInitialMousePos(double x, double y)
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Ball::setLauchVelocity(double x, double y)
{
    lauchedVelocity.x = x;
    lauchedVelocity.y = y;
}

bool Ball::hasWon()
{
    return win;
}

void Ball::setWin(bool _win)
{
    win = _win;
}

void Ball::setSwung(bool _swung)
{
    swung = _swung;
}

// reset swung to false after 100 for loops (timeout)
void Ball::resetSwung(int counter)
{
    if (counter % 20 == 0)
    {
        swung = false;
    }
}

// reset all of the ball's parameter to its original state
void Ball::reset()
{
    setVelocity(0, 0);
    setArrowVelocity(0, 0);
    setWin(false);
    setStroke(0);
    setBounce(0);
    velocityValue = 0;
    lauchedVelocityValue = 0;
}

// function for updating the ball positions when swung, hit walls and hit goals
void Ball::update(SDL_Renderer *renderer, double delta, bool isMouseDown, bool isMousePressed, vector<Tile> tiles, vector<Spike> spikes, vector<Axe> &axes, Hole hole, int &_gameState, int &_loseContext)
{
    //    cout << swung << endl;
    if (win)
    {
        // shifts the position of ball to the center of hole's position by 0.1 * delta if the ball's texture is in the hole's texture
        if (getPos().x < target.x)
        {
            setPos(getPos().x + 0.1 * delta, getPos().y);
        }
        else if (getPos().x > target.x)
        {
            setPos(getPos().x - 0.1 * delta, getPos().y);
        }
        if (getPos().y < target.y)
        {
            setPos(getPos().x, getPos().y + 0.1 * delta);
        }
        else if (getPos().y > target.y)
        {
            setPos(getPos().x, getPos().y - 0.1 * delta);
        }

        setVelocity(velocity.x - delta * velocity.x, velocity.y - delta * velocity.y);
        setArrowVelocity(arrowVelocity.x - delta * arrowVelocity.x, arrowVelocity.y - delta * arrowVelocity.y);

        // decrease the size the of ball gradually as it enters the hole
        setScale(getScale().x - 0.05 * delta, getScale().y - 0.05 * delta);

        setVelocity(0, 0);
        setArrowVelocity(0, 0);
    }

    // check if ball is in hole ---------------------------------------------------------------------------
    // bias range for the ball to hit the target hole
    if (getPos().x + 8 > hole.getPos().x && getPos().x < hole.getPos().x + 8 && getPos().y + 8 > hole.getPos().y && getPos().y < hole.getPos().y + 8)
    {
        setWin(true);
        target.x = hole.getPos().x;
        target.y = hole.getPos().y + 8;
    }

    // boundary check (if the ball hits the boundary, change the direction of the velocity vector) ---------------
    if (getPos().x + getFrame().w > 800)
    {
        if (_gameState != 0)
            bounce++;
        setVelocity(-abs(getVelocity().x), getVelocity().y);
        setArrowVelocity(-abs(getArrowVelocity().x), getArrowVelocity().y);
        directionX = -1;
    }
    else if (getPos().x < 0)
    {
        if (_gameState != 0)
            bounce++;
        //        cout << directionX << endl;
        setVelocity(abs(getVelocity().x), getVelocity().y);
        setArrowVelocity(abs(getArrowVelocity().x), getArrowVelocity().y);
        directionX = 1;
    }
    else if (getPos().y + getFrame().h > 600)
    {
        if (_gameState != 0)
            bounce++;
        setVelocity(getVelocity().x, -abs(getVelocity().y));
        setArrowVelocity(getArrowVelocity().x, -abs(getArrowVelocity().y));
        directionY = -1;
    }
    else if (getPos().y < 0)
    {
        if (_gameState != 0)
            bounce++;
        setVelocity(getVelocity().x, abs(getVelocity().y));
        setArrowVelocity(getArrowVelocity().x, abs(getArrowVelocity().y));
        directionY = 1;
    }

    // get the next coordinate for x and y
    double newCoordinateX = getPos().x;
    double newCoordinateY = getPos().y;

    // check for axe collision ------------------------------------------------------------------------------------
    for (Axe &axe : axes)
    {
        axe.setRotationRate(velocityValue);
        Vector axeOrigin = axe.getOrigin();
        Vector axeEndpoint = axe.getEndpoint();
        double ballAndOriginAngle = SDL_atan2((newCoordinateY + 8 - axeOrigin.y), (newCoordinateX + 8 - axeOrigin.x)) / M_PI * 180;
        double axeAngle = SDL_atan2((axeEndpoint.y - axeOrigin.y), (axeEndpoint.x - axeOrigin.x)) / M_PI * 180;

        double distance = sqrt(pow(newCoordinateX + 8 - axeOrigin.x, 2) + pow(newCoordinateY + 8 - axeOrigin.y, 2));

        bool ballInRadius = distance < 92;

        if (abs(ballAndOriginAngle - axeAngle) <= 4 && ballInRadius && _gameState != 0)
        {
            reset();
            _gameState = 3;
            _loseContext = 3;
        }
    }

    // check for obstacle collision -------------------------------------------------------------------------------
    for (Tile &tile : tiles)
    {
        double newCoordinateX = getPos().x + getVelocity().x * delta * (isMouseDown ? 0.25 : 1);
        double newCoordinateY = getPos().y + getVelocity().y * delta * (isMouseDown ? 0.25 : 1);
        bool hitX = false;
        bool hitY = false;

        // check if the ball hit the vertical edge of the wall
        if (newCoordinateX + 16 > tile.getPos().x && newCoordinateX < tile.getPos().x + tile.getFrame().w && getPos().y + 16 > tile.getPos().y && getPos().y < tile.getPos().y + tile.getFrame().h - 3)
        {
            // if the wall is spiked, then reset the level
            if (tile.getIsSpike())
            {
                reset();
                _gameState = 3;
                _loseContext = 3;
            }
            else if (tile.getIsSticky() && !swung)
            {
                // if the wall is sticky, then decrease all velocity
                setPos(directionX == 1 ? tile.getPos().x - 16 : tile.getPos().x + 64, newCoordinateY);
                setVelocity(0, 0);
                setArrowVelocity(0, 0);
                velocityValue = 0;
                lauchedVelocityValue = 0;
            }
            else
            {
                if (_gameState != 0)
                    bounce++;
                // setPos(directionX == 1 ? tile.getPos().x - 16 : tile.getPos().x + 64, newCoordinateY);
                setVelocity(getVelocity().x * -1, getVelocity().y);
                setArrowVelocity(getArrowVelocity().x * -1, getArrowVelocity().y);
                directionX *= -1;
                //                    break;
            }
            hitX = true;
        }
        // check if the ball hit the horizontal edge of the wall
        if (getPos().x + 16 > tile.getPos().x && getPos().x < tile.getPos().x + tile.getFrame().w && newCoordinateY + 16 > tile.getPos().y && newCoordinateY < tile.getPos().y + tile.getFrame().h - 3)
        {
            if (tile.getIsSpike())
            {
                reset();
                _gameState = 3;
                _loseContext = 3;
            }
            else if (tile.getIsSticky() && !swung)
            {
                setPos(newCoordinateX, directionY == 1 ? tile.getPos().y - 16 : tile.getPos().y + 64);
                setVelocity(0, 0);
                setArrowVelocity(0, 0);
                velocityValue = 0;
                lauchedVelocityValue = 0;
            }
            else
            {
                bounce++;
                // setPos(newCoordinateX, directionY == 1 ? tile.getPos().y - 16 : tile.getPos().y + 64);
                setVelocity(getVelocity().x, getVelocity().y * -1);
                setArrowVelocity(getArrowVelocity().x, getArrowVelocity().y * -1);
                directionY *= -1;
                //                    break;
            }
            hitY = true;
        }
        if (hitX || hitY)
        {
            break;
        }
    }

    // check if ball is running through active spikes
    for (Spike spike : spikes)
    {
        if (spike.getOpen())
        {
            if (getPos().x > spike.getPos().x && getPos().x + 16 < spike.getPos().x + spike.getFrame().w && getPos().y > spike.getPos().y && getPos().y + 16 < spike.getPos().y + spike.getFrame().h - 2)
            {
                reset();
                _gameState = 3;
                _loseContext = 3;
            }
        }
    }

    // if mouse is pressed when the ball is stopped, then set the initial position of the mouse
    if (isMousePressed && !win)
    {
        int mouseX = 0, mouseY = 0;
        // get the mouse position and set its coordinates onto mouseX and mouseY
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePos(mouseX, mouseY);
    }

    // if mouse is dragged when the ball is stopped, calculate velocity and various other elements
    if (isMouseDown && !win)
    {

        setArrowVelocity(getVelocity().x, getVelocity().y);
        int mouseX = 0, mouseY = 0;
        // get the mouse position and set its coordinates onto mouseX and mouseY
        SDL_GetMouseState(&mouseX, &mouseY);
        // change the value of powerConstant to change the velocity limit (the smaller the powerConstant, the harder the player can swing)
        const int powerConstant = 25;
        // calculate unit vector velocity using the current and initial mouse potitions
        double currentXVelocity = (mouseX - getInitialMousePos().x) / -powerConstant;
        double currentYVelocity = (mouseY - getInitialMousePos().y) / -powerConstant;
        double currentVelocityValue = sqrt(currentXVelocity * currentXVelocity + currentYVelocity * currentYVelocity);
        double currentAngle = -SDL_atan2(currentYVelocity, currentXVelocity) * (180 / M_PI);

        // limit the total velocity to 5
        if (currentVelocityValue <= 5)
        {
            setArrowVelocity(currentXVelocity, currentYVelocity);
            setLauchVelocity(currentXVelocity, currentYVelocity);
            velocityValue = currentVelocityValue;
            lauchedVelocityValue = velocityValue;
        }
        else
        {
            currentXVelocity = SDL_cos(currentAngle / 180 * M_PI) * 5;
            currentYVelocity = SDL_sin(currentAngle / 180 * M_PI) * -5;
            setArrowVelocity(currentXVelocity, currentYVelocity);
            setLauchVelocity(currentXVelocity, currentYVelocity);
            velocityValue = 5;
            lauchedVelocityValue = 5;
        }

        // setup pointing arrow's direction
        points.at(0).setPos(getPos().x, getPos().y - 24);
        points.at(0).setAngle(SDL_atan2(getArrowVelocity().y, getArrowVelocity().x) * (180 / M_PI) + 90);

        // set length of the pointing arrow proportional to the velocity value
        points.at(0).setScale(1, velocityValue / 1.2);

        // determine the direction of x and y of the velocity (whether it be positive or negative) to change its direction
        directionX = getArrowVelocity().x / abs(getArrowVelocity().x);
        directionY = getArrowVelocity().y / abs(getArrowVelocity().y);

        // setup the power meter bar
        powerBar.at(0).setPos(getPos().x, getPos().y + 20);
        powerBar.at(1).setScale(velocityValue / 5, 1);
        powerBar.at(1).setPos(getPos().x + 5, getPos().y + 25);

        // draw path prediction line
        //        Vector startPos = Vector(getPos().x + 8, getPos().y + 8);
        //        vector<SDL_Point> points = updateLine(tiles, arrowVelocity, startPos);
        //        setLines(points);

        setPos(getPos().x + getVelocity().x * delta * 0.25, getPos().y + getVelocity().y * delta * 0.25);
    }
    else
    {
        // setNumOfLines(0);
        setVelocity(getArrowVelocity().x, getArrowVelocity().y);
        points.at(0).setPos(-699, -699);
        powerBar.at(0).setPos(-699, -699);
        powerBar.at(1).setPos(-699, -699);
        canMove = false;
        // shift the position of the ball towards the direction of the velocity (times delta to move it bit by bit, therefore creating an animation)
        setPos(getPos().x + getVelocity().x * delta, getPos().y + getVelocity().y * delta);
    }
}
