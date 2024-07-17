#ifndef TOOLBAR_DEFINE_H
#define TOOLBAR_DEFINE_H

#include <stdlib.h>
#include <SDL3/SDL.h> 
#include <SDL3_image/SDL_image.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define NUM_MAIN_BUTTON 6
#define NUM_SIDE_BUTTON 2
#define NUM_VERTICAL_BUTTON 2

#define STAT_MAIN_BUTTON 3

// Main buttons
enum ButtonProperty {
    PIN,
    LOGIN,
    MULTI,
    MINI,
    MAX,
    EXIT
};

enum ButtonStatus {
    NORMAL,
    HOVER,
    CLICK
};

// Side buttons
enum SideProperty {
    LEFT,
    RIGHT
};

enum SideStatus {
    STOP,
    MOVE
};

// Vertical Buttons
enum VerticalProperty {
    FLIP,
    SPREAD
};



typedef struct{
    SDL_FRect *backRect;
    SDL_FRect *buttonRect[NUM_MAIN_BUTTON];
    SDL_FRect *sideRect[NUM_SIDE_BUTTON];
    SDL_FRect *verticalRect[NUM_VERTICAL_BUTTON];
} Toolbar;

#endif