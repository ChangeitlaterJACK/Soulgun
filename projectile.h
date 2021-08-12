/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "entity.h"
#include "movement.h"

/**
 * Represents a projectile entity type
 *
 * Handles movement and attributes specific to projectiles
 */
class Projectile: public Entity
{
public:
    Projectile();
    Projectile(const Projectile &projectile);
    Projectile(int lifetime, int power, double startx, double starty, double direction, bool soulBullet, moveProjectileFunc projectileMove, TextureID textureID);

    void move(Movement &dir);
    bool move(double thetaAim); 
    Position testMove(Movement &dir); 
    Position testMove(double thetaAim);
    void changeDirection(double amount); 

    int getPower(void);
    double getDirection(void);
    bool isSoulBullet(void);
protected:
    int power;
    bool soulBullet; 
    double startx;
    double starty;
    double direction;
};
#endif