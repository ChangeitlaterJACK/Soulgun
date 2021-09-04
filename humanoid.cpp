/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#include "Humanoid.h"

using namespace std;

// Default constructor
Humanoid::Humanoid() :
    Entity(),
    shootCooldown(0),
    shootTimer(100),
    shootStyle(SS_SINGLESHOT)
{
}

// Copy constructor
Humanoid::Humanoid(const Humanoid &humanoid):
    Entity(humanoid),
    shootCooldown(100),
    shootTimer(humanoid.shootCooldown),
    shootStyle(humanoid.shootStyle)
{
}

/**
 * Constructor
 * 
 * @param health Hit points before dying
 * @param entityType ET constant identifier
 * @param x X-coord
 * @param y Y-coord
 * @param speed Movement speed (in pixels)
 * @param entityMove Movement function
 * @param textureID Texture associated with this humanoid
 */
Humanoid::Humanoid(int health, EntityType entityType, 
                double x, double y, double speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID) :
    Entity(health, entityType, x, y, speed, entityMove, projectileMove, textureID),
    shootCooldown(100),
    shootTimer(shootCooldown),
    shootStyle(shootStyle)
{
    if (shootStyle == SS_SPIRAL)
    {
        // Fine-tuned cooldown for spiral shot (can be volatile)
        shootCooldown = 367;
    }
}

/**
 * Getter for shoot style
 * 
 * @returns A ShootStyle constant
 */
ShootStyle Humanoid::getShootStyle()
{
    return shootStyle;
}

/**
 * Setter for shoot style
 * 
 * @param ss A ShootStyle constant
 */
void Humanoid::setShootStyle(ShootStyle ss)
{
    shootStyle = ss;
}

/**
 * Move entity location
 * 
 * @param dir Movement struct for movement direction
 */
void Humanoid::move(Movement &dir)
{
#ifdef ENTITYDEBUG
    bool printSecondHalfOfDebug;
    if (dir.right || dir.left || dir.up || dir.down)  //only print if its going to move
    {
        cout << "Moved entity from (" << posx << ", " << posy;
        printSecondHalfOfDebug = true;
    }
#endif
    Position pos = entityMove(posx, posy, dir, speed);
	setHitboxPos(pos);

    posx = pos.x;
    posy = pos.y;

    if (dir.up || dir.down || dir.left || dir.right)
        moveDirection = dir;

    shootCooldown -=1;
#ifdef ENTITYDEBUG
    if (printSecondHalfOfDebug)
        cout << ") to (" << posx << ", " << posy << ") \n";
#endif
}

/**
 * Spawns a list of projectiles
 * Debug note: Can watch the proj pointer in vscode with gdb: (Projectile*[9]) *proj
 * 
 * @param targetx X-coord that projectile is aimed at
 * @param targety Y-coord that the projecitle is aimed at
 * @param soulBullet If true, this is a soul bullet (currently the only type of bullet the player fires)
 * @returns A list of created projectile objects
 */
vector<Projectile*> Humanoid::shoot(double targetx, double targety, bool soulBullet)
{
    // figure out what direction the entity is aiming
    double aimDirection;
    if (entityType != ET_PLAYER) 
        aimDirection = atan2((targety-posy), (targetx-posx));
    else
        aimDirection = convertMovementToRads(moveDirection);

    double aposx = posx;
    double aposy = posy;

    // adjust for function offsets
    if (projectileMove == moveSine)
    {
        aposx += 50;
        aposy -= 28;
    }
    if (projectileMove == moveCorkscrew)
    {
        aposx += 22;
        aposy += 38;
    }
    TextureID texture = (soulBullet ? TX_BULLET : TX_BULLET); // change when new texture is available
    int power = 1;
    vector<Projectile*> proj;

    // pick projectile lifetime based on movement function
    int lifetime = 700;
    if (projectileMove == moveSpiral 
        || projectileMove == moveCorkscrew
        || projectileMove == moveBoomerang)
        lifetime = 1200;

    // fire projectiles
    if (shootCooldown <= 0 || shootStyle == SS_SPIRAL || shootStyle == SS_3INAROW)
    {
        switch (shootStyle)
        {
            case SS_SINGLESHOT:
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                shootCooldown = shootTimer;
                break;
            case SS_DOUBLESHOT:
                aimDirection -= M_PI / 15;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 7.5;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                shootCooldown = shootTimer;
                break;
            case SS_TRIPLESHOT:
                aimDirection -= M_PI / 12;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 12;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                
                aimDirection += M_PI / 12;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                shootCooldown = shootTimer;
                break;
            case SS_4WAY:
                aimDirection = 0;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                shootCooldown = shootTimer;
                break;
            case SS_4WAYTILT:
                aimDirection = M_PI / 4;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                shootCooldown = shootTimer;
                break;
            case SS_8WAY:
                aimDirection = 0;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection = M_PI / 4;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                aimDirection += M_PI / 2;
                proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));

                shootCooldown = shootTimer;
                break;
            case SS_SPIRAL:
                // Exact spray pattern is currently non-deterministic for unknown reasons
                // Editing the constant values below could result in volatile behavior
                if (shootCooldown % 16 == 0)
                {
                    aimDirection = (shootCooldown / 16) * M_PI / 8.0;
                    proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                }
                if (shootCooldown <= 0)
                    shootCooldown = shootTimer;
                break;
            case SS_3INAROW:
                if (shootCooldown == 0 || shootCooldown == floor(shootTimer / 15) || shootCooldown == floor(shootTimer / 15) * 2)
                {
                    proj.push_back(new Projectile(lifetime, power, aposx, aposy, aimDirection, soulBullet, projectileMove, texture));
                }
                if (shootCooldown <= 0)
                    shootCooldown = shootTimer;
                break;
            default:
                break;
        }
    }
    return proj;
}