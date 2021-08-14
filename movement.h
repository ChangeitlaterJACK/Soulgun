/**
 * Soulgun
 * Copyright (C) 2021 Change It Later JACK
 * Distributed under the MIT software license
 */

#ifndef _MOVEMENT_
#define _MOVEMENT_
#define _USE_MATH_DEFINES

// Comment this out if not debugging
// #define ENTITYDEBUG

#ifdef ENTITYDEBUG
#include <iostream>
#endif
#include <cmath>

#define NUM_OF_PROJ_MOVE_FUNCS 5

// Defines a position on a 2-D plane
struct Position
{
    double x;
    double y;
};

// Defines movement for cardinal directions
struct Movement
{
    bool left = false;
    bool down = false;
    bool up = false;
    bool right = false;
};

// Converting from cardinal directions to angles and vice-versa
// 0 radians is up, positive y is up, positive x is right
double convertCoordsToRads(int startx, int starty, int endx, int endy);
Movement convertCoordsToMovement(int startx, int starty, int endx, int endy);
Movement convertRadsToMovement(double rads);
double convertMovementToRads(Movement &dir);

// Definitions for functons passed for moving entities
typedef Position (*moveEntityFunc)(double posx, double posy, Movement dir, double speed);
typedef Position (*moveProjectileFunc)(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);

// Specific instances entity movement functions
Position moveLeft(double posx, double posy, Movement dir, double speed);
Position movePlayer(double posx, double posy, Movement dir, double speed);

// Projectile movement functions
Position moveLeft(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveDirection(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveSpiral(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveCorkscrew(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveSine(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveBoomerang(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
#endif