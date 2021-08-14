/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
*/

#include "movement.h"
#include <iostream>

using namespace std;

/**
 * Conversion Functions:
 * Various functions for converting between angles, coordinates, and cardinal directions (represented by Movement struct)
 */

/**
 * Calculates angle in radians to get from a start coord to an end coord
 * 
 * @param startx X-coord to start from
 * @param starty Y-cord to start from
 * @param endx X-coord to end at
 * @param endy Y-coord to end at
 * @returns Angle in radian to get from start to end
 */
double convertCoordsToRads(int startx, int starty, int endx, int endy)
{
    double dir = atan2(endy-starty, endx-startx);
    if (dir == -M_PI)
        dir = M_PI;
    return dir;
}

/**
 * Calculates cardinal directions to get from a start coord to an end coord
 * 
 * @param startx X-coord to start from
 * @param starty Y-cord to start from
 * @param endx X-coord to end at
 * @param endy Y-coord to end at
 * @returns Cardinal directions to get from start to end
 */
Movement convertCoordsToMovement(int startx, int starty, int endx, int endy)
{ 
    // Doesn't use convertRadsToMovement to avoid extra copying of Movement struct
    double rads = atan2(endy-starty, endx-startx);
    Movement dir;
    if (abs(rads) > M_PI * 4 / 6)
        dir.down = true;
    if (abs(rads) < M_PI * 2 / 6)
        dir.up = true;
    if (rads < M_PI  * 5 / 6 && rads > M_PI * 1 / 6)
        dir.right = true;
    if (rads > -M_PI * 5 / 6 && rads < -M_PI * 1 / 6)
        dir.left = true;
    return dir;
}

/**
 * Converts radians to cardinal directions
 * 
 * @param startx X-coord to start from
 * @param starty Y-cord to start from
 * @param endx X-coord to end at
 * @param endy Y-coord to end at
 * @returns Cardinal directions to get from start to end
 */
Movement convertRadsToMovement(double rads)
{
    Movement dir;
    if (abs(rads) > M_PI * 4 / 6)
        dir.down = true;
    if (abs(rads) < M_PI * 2 / 6)
        dir.up = true;
    if (rads < M_PI * 5 / 6 && rads > M_PI * 1 / 6)
        dir.right = true;
    if (rads > -M_PI * 5 / 6 && rads < -M_PI * 1 / 6)
        dir.left = true;
    return dir;
}

/**
 * Converts cardinal directions into an angle in radians
 * 
 * @param dir The directions to convert
 * @returns An angle in radians
 */
double convertMovementToRads(Movement &dir)
{
    // default value, will be returned if conversion failed
    double rads = -M_PI;
    if (dir.up)
    {
        rads = -M_PI / 2;
        if (dir.right)
            rads += M_PI / 4;
        if (dir.left)
            rads -= M_PI / 4;
    }
    else if (dir.down)
    {
        rads = M_PI / 2;
        if (dir.right)
            rads -= M_PI  /4;
        if (dir.left)
            rads += M_PI / 4;
    }
    else if (dir.right)
        rads = 0;
    else if (dir.left)
        rads = M_PI;
    return rads;
}

/**
 * Movement Functions:
 * These are based off of general movement function definitions so all parameters may not be used in specific implementations
 * 
 * General notes:
 * theta = 0 is defined to be right ->
 * negative theta is counterclockwise
 * positive theta is clockwise
 * left is negative x, right is positive x
 * up is negative y, down is positive y
 * basically opposite from what you might expect, be careful
 */

/**
 * Moves entity position to the left
 * 
 * @param posx X-coord of entity position
 * @param posy Y-coord of entity position
 * @param dir (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveLeft(double posx, double posy, Movement dir, double speed)
{
    Position pos;
    pos.x = posx - speed;
    pos.y = posy;
    return pos;
}

/**
 * Moves entity position according to cardinal directions (typically keyboard input)
 * 
 * @param posx X-coord of entity position
 * @param posy Y-coord of entity position
 * @param dir Directions to move
 * @param speed Amount to move
 * @returns Resulting position
 */
Position movePlayer(double posx, double posy, Movement dir, double speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    if (dir.left)
        pos.x -= speed;
    if (dir.up)
        pos.y -= speed;
    if (dir.down)
        pos.y += speed;
    if (dir.right)
        pos.x += speed;
    return pos;
}

/**
 * Moves projectile position to the left
 * 
 * @param startx (not used)
 * @param starty (not used)
 * @param posx current X-coord
 * @param posy current Y-coord
 * @param direction (not used)
 * @param thetaAim (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveLeft(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    pos.x -= speed;
    return pos;
}

/**
 * Moves projectile position based on an angle
 * 
 * @param startx (not used)
 * @param starty (not used)
 * @param posx current X-coord
 * @param posy current Y-coord
 * @param direction An angle in radians
 * @param thetaAim (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveDirection(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;

    pos.x += cos(direction) * 3 * speed;
    pos.y += sin(direction) * 3 * speed;

    return pos;
}

/**
 * Moves projectile in a spiral pattern
 * Reference: https://forum.unity.com/threads/moving-an-object-in-a-spiral-pattern-math-inside.465693/
 * 
 * @param startx Intitial X-coord
 * @param starty Initial Y-coord
 * @param posx Current X-coord
 * @param posy Current Y-coord
 * @param direction An angle in radians
 * @param thetaAim (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveSpiral(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;

    double dist = sqrt(pow(posx - startx, 2) + pow(posy - starty, 2));
    if (dist == 0)
        dist = 8;
    dist += 0.25; 
    direction += M_PI / (2 * dist);

    pos.x = cos(direction) * dist + startx;
    pos.y = sin(direction) * dist + starty;

    return pos;
}

/**
 * Moves projectile in a corkscrew pattern
 * Note: First attempt at a sine wave, this will currently spawn too far from the entity.  
 * 
 * @param startx Intitial X-coord
 * @param starty Initial Y-coord
 * @param posx (not used)
 * @param posy (not used)
 * @param direction An angle in radians
 * @param thetaAim (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveCorkscrew(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = speed * 2 * cos(direction) - 40 * sin(speed / 8) + startx;
    pos.y = speed * 2 * sin(direction) - 40 * cos(speed / 8) + starty;
    speed += 0.3;

    return pos;
}

/**
 * Moves projectile in a sine wave pattern
 * Note: It is not currently a perfectly tilted sine wave
 * Reference: https://www.wolframalpha.com/input/?i=plot+%7By%3D-cos%28t%29%2Bt%2Cx%3Dcos%28t%29%2Bt%7D+from+-12+to+12
 * 
 * @param startx Intitial X-coord
 * @param starty Initial Y-coord
 * @param posx (not used)
 * @param posy (not used)
 * @param direction An angle in radians
 * @param thetaAim (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveSine(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    
    if ((direction < 0 && direction > -M_PI / 2) || (direction > M_PI / 2 && direction < M_PI))
    {
        // Northeast and southwest
        pos.x = speed * 2 * cos(direction) - 40 * sin(speed / 20) + startx;
        pos.y = speed * 2 * sin(direction) - 40 * sin(speed / 20) + starty;
    }
    else
    {
        // Northwest and southeast
        pos.x = speed * 2 * cos(direction) - 40 * cos(speed / 20) + startx;
        pos.y = speed * 2 * sin(direction) + 40 * cos(speed / 20) + starty;
    }
    speed += 0.5;

    return pos;
}

/**
 * Moves projectile in a boomerang pattern
 * 
 * @param startx (not used)
 * @param starty (not used)
 * @param posx Current X-coord
 * @param posy Current Y-coord
 * @param direction An angle in radians
 * @param thetaAim (not used)
 * @param speed Amount to move
 * @returns Resulting position
 */
Position moveBoomerang(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;

    pos.x += cos(direction) * 2.5 * speed;
    pos.y += sin(direction) * 2.5 * speed;

    speed -= 1 / 500.0;

    return pos;
}