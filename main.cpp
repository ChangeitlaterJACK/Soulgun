#ifdef LAB
#include "../SDL/include/SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif //LAB

#include <iostream>
#include "Map.h"
#include "Humanoid.h"
#include "TextureManager.h"
#include "DisplayManager.h"
#include "HUD.h"

#define REFRESH_RATE 15

using namespace std;

bool eventFinder(SDL_Event &event, Movement &movement);

int main (int argc, char **argv) {
	Movement movement;

	//Event handler
	SDL_Event event;

	// Initialize SDL objects
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_Window *window = SDL_CreateWindow("Soulgun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	// Create all of the objects for the game engine
	TextureManager *txMan = new TextureManager(renderer);
	Map *map = new Map(txMan);
	DisplayManager dispMan(renderer, txMan, map);
	vector<Projectile*> playerShots;
	Humanoid *player = dispMan.spawnHumanoid(map, ET_PLAYER);
	HUD *hud = new HUD(renderer, player, txMan);

	// Start the game loop
	int nextRefresh = SDL_GetTicks();
	while (event.type != SDL_QUIT)
	{
		// Check for input
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				break;
		}

		SDL_RenderClear(renderer);

		// Interpret event
		if (eventFinder(event, movement))
		{
			playerShots = player->shoot(0,0,true);
			for (int i = 0; i < playerShots.size(); ++i)
				dispMan.addProjectile(playerShots[i]);
		}

		if (map->isPlayerColliding(player->testMove(movement)))
		{
			player->move(movement);
		}

		// Wait for refresh delay
		int now = SDL_GetTicks();
		if (now < nextRefresh)
			SDL_Delay(nextRefresh - now);
		nextRefresh = now + REFRESH_RATE;
		
		SDL_RenderClear(renderer);
		
		// Respawn and recalculate entity positions
		dispMan.spawnEnemies(map);
		dispMan.moveEnemies(map);
		dispMan.fireEnemies();
		dispMan.moveProjectiles();

		// TO-DO Fix game over screen
        // Game Over screen
        if(player->damage(0)){
            SDL_DestroyRenderer(renderer);
            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_Texture *gtext = IMG_LoadTexture(renderer, "assets/images/game_over.png");

            SDL_RenderCopy(renderer, gtext, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            break;
        }

		// Redraw entities on screen
		dispMan.refresh();
		//hud->refresh();
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();

	return 0;
}

/**
 * Interprets keyboard events
 * 
 * @param event A keyboard event
 * @param movement Movement struct that will be populated based on keyboard input
 * @returns True if user presses the shoot key
 */
bool eventFinder(SDL_Event &event, Movement &movement){
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	movement.left = (keystate[SDL_SCANCODE_LEFT] != 0);
	movement.up = (keystate[SDL_SCANCODE_UP] != 0);
	movement.right = (keystate[SDL_SCANCODE_RIGHT] != 0);
	movement.down = (keystate[SDL_SCANCODE_DOWN] != 0);
	return (keystate[SDL_SCANCODE_SPACE] != 0);
}

