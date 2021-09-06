/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
*/

#include "Projectile.h"

using namespace std;

// Default constructor
Projectile::Projectile():
    Entity(),
    power(2),
    soulBullet(false),
    startx(0),
    starty(0),
    direction(0)
{
#ifdef ENTITYDEBUG
        cout << "Created default projectile. " << endl;
#endif
}

// Copy constructor
Projectile::Projectile(const Projectile &projectile):
    Entity(projectile),
    power(projectile.power),
    soulBullet(projectile.soulBullet),
    startx(projectile.startx),
    starty(projectile.starty),
    direction(projectile.direction)
{
#ifdef ENTITYDEBUG
        cout << "Created projectile from copy. " << endl;
#endif
}

/**
 * Constructor
 * 
 * @param lifetime Indicates how long before projectile disappears (value will decrement when game loop refreshes)
 * @param power The number of health points the projectile will do upon contact.
 * @param startx X-coord where projectile started
 * @param starty Y-coord where projected started
 * @param direction Radians for the direction the bullet is aimed toward
 * @param soulBullet True if the bullet used will take a human entity's soul
 * @param projectileMove Function to handle movement
 * @param textureID Texture identifier for this projectile
 */
Projectile::Projectile(int lifetime, int power, double startx, double starty, double direction, 
                        bool soulBullet, moveProjectileFunc projectileMove, TextureID textureID):
    Entity(lifetime, ET_PROJECTILE, startx, starty, 1, movePlayer, projectileMove, textureID), //control all bullet speeds from here
    power(power),
    soulBullet(soulBullet),
    startx(startx),
    starty(starty),
    direction(direction)
{
#ifdef ENTITYDEBUG
        cout << "Created projectile with custom stats. " << endl;
#endif
}

/**
 * Moves projectile in cardinal directions
 * 
 * @param dir The Direction to move
 * @returns True if projecitle has expended its lifespan
 */
void Projectile::move(Movement &dir)
{
    double thetaAim = convertMovementToRads(dir);
    Position pos = projectileMove(startx, starty, posx, posy, direction, thetaAim, speed);
	setHitboxPos(pos);
    
    posx = pos.x;
    posy = pos.y;
    health -= 1;
}

/**
 * Determines what position a projectile would be at after moving in cardinal directions (does not update location)
 * 
 * @param dir Direction to move
 * @returns Resulting position
 */
Position Projectile::testMove(Movement &dir)
{
    // Note: This could be changed to accept a Position instead
    double thetaAim = convertMovementToRads(dir);
    Position pos = projectileMove(startx, starty, posx, posy, direction, thetaAim, speed);
    return pos;
}

/**
 * Moves projectile at an angle
 * 
 * @param thetaAim The angle in radians to move
 * @returns True if projecitle has expended its lifespan
 */
bool Projectile::move(double thetaAim)
{
    // Move projectile using its movement function
    Position pos = projectileMove(startx, starty, posx, posy, direction, thetaAim, speed);
    posx = pos.x;
    posy = pos.y;
    health -= 1;

    // Update hitbox location and return indicator if projectile should disappear
	setHitboxPos(pos);
    return (health <= 0);
}

/**
 * Determines what position a projectile would be at after moving at an angle (does not update location)
 * 
 * @param dir Direction to move
 * @returns Resulting position
 */
Position Projectile::testMove(double thetaAim)
{
    Position pos = projectileMove(startx, starty, posx, posy, direction, thetaAim, speed);
    return pos;
}

/** 
 * Adds radians to alter the current direction.
 * Designed to be used for ease of multi bullet creation along with the copy constructor.
 * Could potentially be used for rebounding off walls, but this is not currently expected and won't work with all movement functions.
 * 
 * @param amount Amount of radians to add
 */
void Projectile::changeDirection(double amount)
{
#ifdef ENTITYDEBUG
    cout << "Projectile direction changed from " << direction;
#endif
    direction += amount;
    while (direction > M_PI)
        direction -= 2 * M_PI;
    while (direction <= -M_PI)
        direction += 2 * M_PI;
#ifdef ENTITYDEBUG
    cout << " to " << direction << ". " << endl;
#endif
}

/**
 * Getter for power value
 * 
 * @returns Power value
 */
int Projectile::getPower()
{
    return power;
}

/**
 * Getter for current direction
 * 
 * @returns Current direction
 */
double Projectile::getDirection()
{
    return direction;
}

/**
 * Indicates whether projectile is a soul bullet
 * 
 * @returns True if projectile is a soul bullet
 */
bool Projectile::isSoulBullet()
{
    return soulBullet;
}
