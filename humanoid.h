/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#ifndef _HUMANOID_
#define _HUMANOID_

#include <vector>
#include "Entity.h"
#include "Projectile.h"

// Time enemy will move in one direction before changing
#define ROBOT_MOVE_TIME 500
#define HUMAN_MOVE_TIME 150

// Distance enemy will move toward player
#define ENEMY_MIN_DIST 250

// Distance enemy will move away from player
#define ENEMY_MAX_DIST 450

// Shooting style identifiers (not all implemented at this time)
enum ShootStyle 
{
    SS_SINGLESHOT,
    SS_DOUBLESHOT,
    SS_TRIPLESHOT,
    SS_4WAY,
    SS_4WAYTILT,
    SS_8WAY,
    SS_SPIRAL,
    SS_3INAROW,
    SS_TOTAL
};

/**
 * Represents a humanoid-type entity (Human, Robot, Player)
 */
class Humanoid : public Entity
{
public:
    Humanoid(void);
    Humanoid(const Humanoid &humanoid);
    Humanoid(int health, EntityType entityType, 
                double x, double y, double speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID);

    void move(Movement &dir);
    std::vector<Projectile*> shoot(double targetx, double targety, bool soulBullet);
    ShootStyle getShootStyle();
    void setShootStyle(ShootStyle ss);
protected:
    int shootCooldown; // the current time left before being able to shoot again
    int shootTimer; // the time between each shot
    ShootStyle shootStyle; // what direction and how many projectiles to fire
};
#endif