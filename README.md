# Soulgun
A cross-platform "bullet hell" game where your gun can possess your enemies.  The player will dodge bullets from neverending barrage of robotic and humanoid enemies.  If the player gets in over their head they can target a humanoid enemy to switch places and move out of harm's way.
_Jackedsoft 2021_

## Contributors
* **J**ared Collums
* **A**leksander Kaletin
* **C**hristopher Tevren
* **K**irani Anderson

## Technologies
* C++
* [SDL 2.0](https://www.libsdl.org/]) - "a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D"

## Attributions
Entity sprites based on graphics designed by OpenMoji – the open-source emoji and icon project. License: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/#)


## Overview of how entities and projectiles work
Humanoids can be either humans or robots. A humans soul can be stolen by the player, giving the player the stats of the human. Human and robots stats include health, movement speed, a shooting cooldown, and bullet patterns. 
The spawning of humanoids is managed by the display manager, which generates humanoids with random stats near the player. The spawn rate increases over time. Movement is also handled by the display manager. Robots move vertically and horizontally, while humans move diagonally.
Entity bullet patterns are defined by two variables, the shoot style, and a function that defines the projectiles movement. The shoot style of an entity is what defines the number and orientation of bullets when they are fired. The projectile movement function defines how the bullet will move after it has been spawned. These two variables are randomized separately, creating a fair amount of unique combinations.



## Development Roadmap
Development will happen in one week sprints, with each sprint introducing the features specified below.  Specific milestone deadlines may be shifted as needed.  After the last of these sprints we hope to have a coherent game whose mechanics and assets can be easily built upon.

### Week 1 - Prototype
- Basic Game Engine
	- Main Loop
		* Construct the main game loop to handle rending of graphics and handle user input
	- Onscreen Entities
		* Objects to represent the player, enemies, and their respective locations
	- Map with Partial Display
		* A map system to display only a portion of the map depending on player location

### Week 2
- Player Movement
	* Enable user to move around map with user input
- Enemy Spawning System
	* System for continuously spawning a limited number of enemies in proximity to the player entity
- Projectiles & Collision
	* Player and enemies shoot projectiles
	* Players and enemies disappear from map when projectiles collide with them

### Week 3
- Humanoid Enemy Type 
	* Enable an enemy to be “possessed” by the soulgun
- Soulgun Functionality
	* Alternate firing mode that causes player entity to switch with humanoid enemy
	* Soulgun projectile only collides with humanoid enemies

### Week 4 - Minimum Viable Product
- Enemy Movement AI
	* Enemies face and toward player and move around or away if player gets too close
	* Enemies position themselves in a relavtively even distribution
- Scoring
	* Points and/or timer

### Week 5
- Quality Assurance
	* Test for bugs
- Cosmetic Enhancements
	* Better sprite graphics 
	* Rudimentary Sound effects
	* Better map graphics
