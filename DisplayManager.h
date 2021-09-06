/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#pragma once
#include "Map.h"
#include "TextureManager.h"
#include "Humanoid.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Distance enemies will spawn away from the player
#define SPAWN_DIST 350

#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH 1024
/**
 * Manages entities and where textures are drawn on-screen
 */
class DisplayManager
{
public:
    DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture, Map *map);
    ~DisplayManager(void);

    Position applyCameraOffset(Position absPos);

    void spawnEnemies(Map *map);
    Humanoid *spawnHumanoid(Map *map, EntityType type);
    void moveEnemies(Map *map);
    bool isNearEnemy(int x, int y, int proximity);
    void fireEnemies(void);
    void moveProjectiles(void);

    void addEntity(Humanoid *entity);
    void removeEntity(Humanoid *entity);
    void addProjectile(Projectile *proj);
    void removeProjectile(Projectile *proj);
    void refreshEntities(void);
    void refreshMap(void); 

    void flashBox(int startx, int starty, int Width, int Height);
    void flashScreen(void);
    bool swapSpots(Humanoid *toSwap);

private:
    std::vector<Humanoid *> entities;
    std::vector<Projectile *> projectiles;
    SDL_Renderer *renderer;
		Map *renderMap;
    TextureManager *txMan;

    int newSpawnCooldown;
    int maxSpawnCooldown;
    bool firstSpawn;
    Humanoid *player;
};
