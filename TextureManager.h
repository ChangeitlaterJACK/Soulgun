/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#ifndef _TEXTUREMANAGER_
#define _TEXTUREMANAGER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

// Identifiers for textures
enum TextureID
{
    TX_PLAYER,
    TX_ROBOT,
    TX_HUMAN,
    TX_BULLET,
    TX_TERRAIN,
	TX_WALL,
	TX_PIT,
    TX_GAMEOVER,
    TX_TOTAL
};

/**
 * Manages textures in memory
 *
 * A pre-defined set of textures can be loaded, unloaded,
 * and retrieved with its dimension meta data
 */
class TextureManager
{
public:
    TextureManager(SDL_Renderer *xRenderer);
    ~TextureManager(void);

    SDL_Texture *getTexture(TextureID id);
    SDL_Point getDimensions(TextureID id);

private:
    std::string paths[TX_TOTAL];

    SDL_Texture *textures[TX_TOTAL];
    SDL_Point dimensions[TX_TOTAL];
    SDL_Renderer *renderer;

    SDL_Texture *load(TextureID id);
    void unload(TextureID id);
};
#endif