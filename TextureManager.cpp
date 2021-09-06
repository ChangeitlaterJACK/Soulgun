/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
*/

#include "TextureManager.h"

/**
 * Loads all pre-defined textures
 *
 * @param renderer An external renderer needed to create textures
 */
TextureManager::TextureManager(SDL_Renderer *xRenderer)
{
    renderer = xRenderer;

    int i = 0;
    paths[i++] = "assets/images/openmoji-player.png";
    paths[i++] = "assets/images/openmoji-robot.png";
    paths[i++] = "assets/images/openmoji-human.png";
    paths[i++] = "assets/images/placeholder-bullet.png";
    paths[i++] = "assets/images/placeholder-terrain.png";
    paths[i++] = "assets/images/placeholder-wall.png";
    paths[i++] = "assets/images/placeholder-pit.png";
    paths[i++] = "assets/images/game_over.png";

    for (int id = 0; id < TX_TOTAL; ++id)
    {
        textures[id] = NULL;
        dimensions[id].x = 0;
        dimensions[id].y = 0;
        load(static_cast<TextureID>(id));
    }
}

/**
 * Unloads all loaded textures
 */
TextureManager::~TextureManager(void)
{
    for (int id = 0; id < TX_TOTAL; ++id)
    {
        unload(static_cast<TextureID>(id));
    }
}

/**
 * Retrieves a texture that has been loaded
 *
 * @param id The texture ID to retrieve
 * @returns A pointer to the texture
 */
SDL_Texture *TextureManager::getTexture(TextureID id)
{
    return textures[id];
}

/**
 * Retrieves the dimensions of a texture that has been loaded
 *
 * @param id The texture ID to retrieve dimensions for
 * @returns An SDL point struct (x = width, y = height)
 */
SDL_Point TextureManager::getDimensions(TextureID id)
{
    return dimensions[id];
}

/**
 * Loads a image into memory and creates a texture from it
 *
 * @param id The texture ID to load
 * @returns A pointer to the texture that was created, or NULL if failed
 */
SDL_Texture *TextureManager::load(TextureID id)
{
    // Reload if already loaded
    if (textures[id] != NULL)
        unload(id);

    const char *path = paths[id].c_str();
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);

    if (!texture)
        printf("Error creating texture from %s: %s", path, SDL_GetError());

    // Get dimensions
    int w = 0;
    int h = 0;
    SDL_Point size;

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    size.x = w;
    size.y = h;
    dimensions[id] = size;

    textures[id] = texture;
    return texture;
}

/**
 * Unloads a texture that has been loaded
 *
 * @param id The texture ID to load
 */
void TextureManager::unload(TextureID id)
{
    if (textures[id] != NULL) {
        SDL_DestroyTexture(textures[id]);
        textures[id] = NULL;
        dimensions[id].x = 0;
        dimensions[id].y = 0;
    }
}
