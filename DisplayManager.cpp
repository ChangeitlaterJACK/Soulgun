#include "DisplayManager.h"

/**
 * Initializes the display manager
 * 
 * @param xRenderer External renderer
 * @param xTexture External texture manager
 */
DisplayManager::DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture) {
    renderer = xRenderer;
    txMan = xTexture;
}

/**
 * Deconstructs all entities
 */
DisplayManager::~DisplayManager(void) {
    for (int i = 0; i != entities.size(); ++i) {
        delete entities[i];
    }
    entities.clear();
}

/**
 * Adds an entity to the manager
 * 
 * @param entity Pointer to an entity
 */
void DisplayManager::addEntity(Entity *entity) {
    entities.push_back(entity);
}

/**
 * Removes an entity from the manager
 * 
 * @param entity Pointer to an entity that is being managed
 */
void DisplayManager::removeEntity(Entity *entity) {
    for (int i = 0; i < entities.size(); ++i) {
        if (entities[i] == entity) {
            delete entity;
            entities.erase(entities.begin() + i);
        }
    }
}

/**
 * Draws textures on the window where they are currently located
 */
void DisplayManager::refresh(void) {
    // Put textures on screen
    SDL_Rect position;
    SDL_Point size;
    SDL_Texture *texture;
    Entity *e;

    // Map should draw the portion of its texture onscreen that it needs to
    texture = txMan->getTexture(TX_TERRAIN);
    size = txMan->getDimensions(TX_TERRAIN);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (int i = 0; i < entities.size(); ++i) {
        e = entities[i];

        texture = txMan->getTexture(static_cast<TextureID>(e->getImage()));
        size = txMan->getDimensions(static_cast<TextureID>(e->getImage()));
        position.h = size.y;
        position.w = size.x;

        // position.x  = e->x - map->offset_x;
        // position.y  = e->y - map->offset_y;
        Position pos = e->getPosition();
        position.x  = pos.x;
        position.y  = pos.y;

        SDL_RenderCopy(renderer, texture, NULL, &position);
    }
}