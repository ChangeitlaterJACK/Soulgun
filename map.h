/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "entity.h"
#include "TextureManager.h"

const int TILE_HEIGHT = 100;
const int TILE_WIDTH = 100;
const int MAX_TILES = 30;

// Identifiers for tile types
enum tileID 
{ 
	TID_TERRAIN,
	TID_WALL,
	TID_PIT,
};

/**
 * Represents a single map tile
 */
class mapTile 
{
public:
	mapTile(void);
	mapTile(int x, int y, tileID id, SDL_Texture * texture );
	void setTileData(int x, int y, int h, int w, tileID id);
	tileID getType(void);
	SDL_Rect* getTile(void);
	SDL_Texture* getTileTexture(void);
private:
	tileID tID;
	SDL_Rect tileData;
	SDL_Texture* tileTexture;
};

/**
 * Represents the map 
 *
 * Handles drawing a collection of map tiles to the screen
 */
class MapManager 
{
public:	
	MapManager(TextureManager * txMan);
	~MapManager(void);
	
	void levelLoader(int level);
	void texturePreloader(TextureManager * txMan); 
	SDL_Texture* textureUnloader(int tile_type);
	bool mapCollision(Position player);

	tileID textureToTile(int tile_type);
	TextureID tileToTexture(int texture_type);
	void mapDrawer(SDL_Renderer * renderer); 
private:
	std::vector<SDL_Texture*> mapTextures;
	std::vector<std::vector<mapTile*> > gameMap;
};
