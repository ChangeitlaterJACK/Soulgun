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
#include "Entity.h"
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
class MapTile 
{
public:
	MapTile(void);
	MapTile(int x, int y, tileID id, SDL_Texture * texture );
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
class Map 
{
public:	
	Map(TextureManager * txMan);
	~Map(void);
	
	void load(int level);
	void retrieveTextures(TextureManager * txMan); 
	SDL_Texture* getTileTexture(int tile_type);
	bool isPlayerColliding(Position player);

	tileID textureToTile(int tile_type);
	TextureID tileToTexture(int texture_type);
	void refresh(SDL_Renderer * renderer); 
private:
	std::vector<SDL_Texture*> mapTextures;
	std::vector<std::vector<MapTile*> > gameMap;
};
