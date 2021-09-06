/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#include "Entity.h"

using namespace std;

/**
 * Default constructor
 */
Entity::Entity(void):
    moveStartTime(0),
    moveAway(false),
    maxHealth(10),
    health(maxHealth),
    entityType(ET_ROBOT),
    posx(0),
    posy(0),
    speed(1),
    entityMove(moveLeft),
    projectileMove(moveLeft),
    textureID(TX_ROBOT)

{
	setHitbox(ET_ROBOT);
#ifdef ENTITYDEBUG
    cout << "Created default entity." << endl;
#endif
}

// Copy constructor
Entity::Entity(const Entity &entity):
    maxHealth(entity.maxHealth),
    health(entity.maxHealth),
    entityType(ET_PLAYER),
    posx(entity.posx),
    posy(entity.posy),
    speed(entity.speed),
    entityMove(entity.entityMove),
    projectileMove(entity.projectileMove),
    textureID(entity.textureID)
{
	setHitbox(entityType);
#ifdef ENTITYDEBUG
    cout << "Created entity from copy." << endl;
#endif
}

/**
 * Constructor
 * 
 * @param health Amount of hit points
 * @param entityType ET constant: human, robot, player
 * @param x Current X-coord
 * @param y Current Y-coord
 * @param entityMove Function that describes the entity's movemeny
 * @param projectMove Function that desribes the movement of entity's projectiles
 * @param textureID Texture identifier
 */
Entity::Entity(int health, EntityType entityType,
                double x, double y, double speed, moveEntityFunc entityMove,
                moveProjectileFunc projectileMove,
                TextureID textureID) :
    maxHealth(health),
    health(health),
    entityType(entityType),
    posx(x),
    posy(y),
    speed(speed),
    entityMove(entityMove),
    projectileMove(projectileMove),
    textureID(textureID)
{
	setHitbox(entityType);
#ifdef ENTITYDEBUG
    cout << "Created entity with custom stats." << endl;
    cout << "Type is: " << (entityType == ET_PLAYER ? "player" : "npc") << endl;
    cout << "Position: " << posx << ", " << posy << endl;
    cout << "speed: " << speed << endl;
#endif
}

/**
 * Get x, y coordinates
 * 
 * @returns struct with x, y members
 */
Position Entity::getPosition(void)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    return pos;
}

/**
 * Getter for health
 * 
 * @returns Current health
 */
int Entity::getHealth(void)
{
    return health;
}

/**
 * Getter for texture identifier
 * 
 * @returns Current texture identifier
 */
TextureID Entity::getImage(void)
{
    return textureID;
}

/**
 * Getter for entity type identifier
 * 
 * @returns Entity type identifier
 */
EntityType Entity::getType(void)
{
    return entityType;
}

/**
 * Getter for the Move Projectile function
 * 
 * @returns Move projectile function
 */
moveProjectileFunc Entity::getProjMoveFunc()
{
    return projectileMove;
}

/**
 * Setter for the Move Projectile function
 * 
 * @param func A moveProjectileFunc function
 */
void Entity::setProjMoveFunc(moveProjectileFunc func)
{
    projectileMove = func;
}

/**
 * Adjusts hitbox based on entity type
 * 
 * @param ID entity type identifier
 */
void Entity::setHitbox(EntityType ID)
{
    if (ID == ET_PROJECTILE)
    {
        hitbox.h = 5;
        hitbox.w = 5;
    }
    else
    {
        hitbox.h = 25;
        hitbox.w = 25;
    }
}

/**
 * Adjusts hitbox location
 * 
 * @param entity Entity's current position
 */
void Entity::setHitboxPos(Position entity)
{
    hitbox.x = entity.x;
    hitbox.y = entity.y;
}

/**
 * Getter for the hitbox
 * 
 * @returns The hitbox struct
 */
SDL_Rect * Entity::getHitbox()
{
	return &hitbox;
}

/**
 * Determines whether an entity collides with a defined box
 * 
 * @param a Pointer to an SDL rectangle definition
 * @returns True if collision detected
 */
bool Entity::entityCollision(SDL_Rect * a){
	return SDL_HasIntersection(a, &this->hitbox);
}

/**
 * Determines where an entity would be located after moving (without actually moving them)
 * 
 * @param dir Movement struct for movement directions
 * @returns Resulting position
 */
Position Entity::testMove(Movement &dir)
{
    return entityMove(posx, posy, dir, speed);
}

/**
 * Inflict damage on the entity
 * 
 * @param amount Amount of damage to inflict (makes health go down)
 * @returns True if entity has no remaining hit points (death)
 */
bool Entity::damage(int amount)
{
    health -= amount;
#ifdef ENTITYDEBUG
        cout << "Entity took " << amount << " damage. " << endl;
#endif
    if (health <= 0)
    {
#ifdef ENTITYDEBUG
        cout << "Entity died." << endl;
#endif
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Sets entity location (x, y coord)
 * 
 * @param newPos New x,y position
 */
void Entity::setLocation(Position &newPos){
    posx = newPos.x;
    posy = newPos.y;
}
