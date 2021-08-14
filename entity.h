/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#ifndef _ENTITY_
#define _ENTITY_

// Note: ENTITY_DEBUG is defined in movement.h

#include "movement.h"
#include "TextureManager.h"

// Entity type identifiers
enum EntityType
{
    ET_PLAYER,
    ET_ROBOT,
    ET_HUMAN,
    ET_PROJECTILE
};

class Entity //ABS
{
public:
    Entity(void);
    Entity(const Entity &entity);
    Entity(int health, EntityType entityType,
            double x, double y, double speed, moveEntityFunc entityMove,
            moveProjectileFunc projectileMove,
            TextureID textureID);
    Entity& operator=(const Entity &entity);
    ~Entity();

    int getHealth(void);
    Position getPosition(void);
    TextureID getImage(void);
    EntityType getType(void);

    void setHitbox(EntityType ID);
    void setHitboxPos(Position entity);
    SDL_Rect * getHitbox(void);
    bool entityCollision(SDL_Rect * a);

    moveProjectileFunc getProjMoveFunc();
    void setProjMoveFunc(moveProjectileFunc func);
    virtual void move(Movement &dir) = 0;
    virtual Position testMove(Movement &dir);
    bool damage(int amount);
    void setLocation(Position &newPos);

    // Todo: Protected getters and setters

    // For movement defined in display manager
    Movement moveDirection; // Last direction moved
    int moveStartTime;      // When humanoid started moving in this direction
    int moveAway;           // If true move away from player
protected:
    int maxHealth;  // Maximum hit points
    int health;     // hit points
    SDL_Rect hitbox; // Must update hitbox position before each use
    EntityType entityType; // Human, robot, player, etc

    double posx; // curent x coordinate
    double posy; // current y coordinate
    double speed; // movement speed, how much does it move between frames

    moveEntityFunc entityMove; // not fully implemented, used only with moveDirection
    moveProjectileFunc projectileMove; // define how the entity's projectiles will move after they've been shot
    TextureID textureID; // the image to load to the screen
};
#endif
