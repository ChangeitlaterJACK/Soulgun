/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
*/

#include "Map.h"

/**
 * Map Tile members
 */

// Default constructor
MapTile::MapTile(void)
{
	tileData.x = 0;
	tileData.y = 0;
	
	tileData.h = TILE_HEIGHT;
	tileData.w = TILE_WIDTH;

	// Tile type enum ID
	tID = TID_PIT;
}

/**
 * Constrcutor
 * 
 * @param x X-coord
 * @param y Y-coord
 * @param id Tile identifier
 * @param texture Pointer to texture
 */
MapTile::MapTile(int x, int y, tileID id, SDL_Texture * texture)
{
	tileData.x = x;
	tileData.y = y;

	tileData.h = TILE_HEIGHT;
	tileData.w = TILE_WIDTH;

	tID = id;
	tileTexture = texture;
}

/**
 * Setter for all tile attributes
 * 
 * @param x X-coord
 * @param y Y-coord
 * @param h Height in pixels
 * @param w Width in pixels
 * @param id Tile identifier
 */
void MapTile::setTileData(int x, int y, int h, int w, tileID id)
{
	tileData.x = x;
	tileData.y = y;

	tileData.h = h;
	tileData.w = w;

	tID = id;
}

/**
 * Getter for tile identifier
 */
tileID MapTile::getType(void)
{
	return tID;
}

/**
 * Getter for tile attributes
 */
SDL_Rect* MapTile::getTile(void)
{
	return &tileData;
}

/**
 * Getter for texture pointer
 */
SDL_Texture* MapTile::getTileTexture(void)
{
	return tileTexture;
}

/**
 * Map Manager members
 */

/**
 * Destructor
 */
Map::~Map(void) 
{
	for(int i = 0; i < MAX_TILES; ++i)
	{
		gameMap[i].clear();
	}
	gameMap.clear();
}

/**
 * Constructor that preloads textures and map
 * 
 * @param txMan Pointer to texture manager
 */
Map::Map(TextureManager * txMan) 
{	
	mapTextures.resize(3);

	// Preloads texture set
	for(int i = 0; i < 3; ++i)
	{
		mapTextures[i] = txMan->getTexture(tileToTexture(i));
	}

	loadLevel(1);
}

/**
 * Loads a map file and tiles into memory
 * 
 * @param level Indicates which map to load
 */
void Map::loadLevel(int level)
{	
	std::ifstream mapFile;
	int tile_type;

	// Load map file
	switch (level)
	{
		case 1:
			mapFile.open("assets/maps/levelone.txt");
			break;
 	}
	gameMap.resize(MAX_TILES);

	// Load map tile objects
	if(mapFile.is_open()) 
	{
		for(int i = 0; i < MAX_TILES; ++i)
		{
			gameMap[i].resize(MAX_TILES);
			for(int j = 0; j < MAX_TILES; ++j)
			{
				mapFile >> tile_type;
				gameMap[i][j] = new MapTile(j * TILE_WIDTH, i * TILE_HEIGHT, textureToTile(tile_type), getTileTexture(tile_type));
			}
		}
	}
	else
	{
		std::cout << "Map file failed to load" << std::endl;
	}

	mapFile.close(); 
}
/**
 * Retrieves a map texture
 * 
 * @param tile_type Tile identifier
 */
SDL_Texture* Map::getTileTexture(int tile_type)
{
	return mapTextures[tile_type];
}

/**
 * Map collision detector
 * 
 * @param player Pointer to the player object
 * @returns False if player is colliding with map edge, wall, or pit
 */
bool Map::isPlayerColliding(Position player)
{
	// TO-DO: Calculate camera offset for both tiles and player

	if (player.x <= 0 || player.y <= 0 || player.x + 20 >= MAX_TILES * TILE_WIDTH || player.y + 25 >= MAX_TILES * TILE_HEIGHT) 
		return false;

	if (gameMap[player.y / TILE_WIDTH][player.x / TILE_HEIGHT]->getType() == TID_WALL ||
		gameMap[(player.y + 25) / TILE_WIDTH][(player.x + 20) / TILE_HEIGHT]->getType() == TID_WALL ||
		gameMap[(player.y + 25) / TILE_WIDTH][(player.x) / TILE_HEIGHT]->getType() == TID_WALL ||
		gameMap[(player.y) / TILE_WIDTH][(player.x + 20) / TILE_HEIGHT]->getType() == TID_WALL)
	{
		return false;
	}

	if (gameMap[player.y / TILE_WIDTH][player.x / TILE_HEIGHT]->getType() == TID_PIT ||
		gameMap[(player.y + 25) / TILE_WIDTH][(player.x + 20) / TILE_HEIGHT]->getType() == TID_PIT ||
		gameMap[(player.y + 25) / TILE_WIDTH][(player.x) / TILE_HEIGHT]->getType() == TID_PIT ||
		gameMap[(player.y) / TILE_WIDTH][(player.x + 20) / TILE_HEIGHT]->getType() == TID_PIT)
	{
		return false;
	}
	else
	{
		return true;
	}

}

/**
 * Converts a texture ID to a tile ID
 * 
 * @param tile_type Texture ID
 * @returns Tile identifier
 */
tileID Map::textureToTile(int tile_type) 
{
	// TO-DO: Remove function, store tile id in object itself
	tileID tid;
	switch (tile_type) 
	{
		case 0:
			tid = TID_TERRAIN;
		break;
		case 1:
			tid = TID_WALL;
		break;
		case 2:
			tid = TID_PIT;
		break;
	}
	return tid;
}

/**
 * Converts a tile ID to a texture ID
 * 
 * @param texture_type Tile ID
 * @returns Texture identifier
 */
TextureID Map::tileToTexture(int texture_type) 
{
	// TO-DO: Remove function, store texture id in object itself
	TextureID tid;
	switch (texture_type) {
		case 0:
			tid = TX_TERRAIN;
		break;
		case 1:
			tid = TX_WALL;
		break;
		case 2:
			tid = TX_PIT;
		break;
	}
	return tid;
}

/**
 * Draws tiles onto the map
 * 
 * @param renderer External renderer
 */
void Map::refresh(SDL_Renderer * renderer) 
{
	// TO-DO: Only render tiles that are visible
	// Calculate camera offset position before SDL_RenderCopy

	// Loops iterate over map 2D vector
	for(int i = 0; i < MAX_TILES; ++i)
	{
		for(int j = 0; j < MAX_TILES; ++j)
		{
			SDL_RenderCopy(renderer, gameMap[i][j]->getTileTexture(), NULL, gameMap[i][j]->getTile());
		}
	}
}
