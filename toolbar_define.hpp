#ifndef TOOLBAR_DEFINE_HPP
#define TOOLBAR_DEFINE_HPP

#include <SDL3/SDL.h> 
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define NUM_MAIN_BUTTON 6
#define NUM_SIDE_BUTTON 2
#define NUM_VERTICAL_BUTTON 2

#define STAT_MAIN_BUTTON 3

// Exit flag
typedef enum exitFlag{
    ON, 
    OFF
}exitFlag;

// Main buttons
typedef enum ButtonProperty{
    PIN,
    LOGIN,
    MULTI,
    MINI,
    FULLSCREEN,
    EXIT
} ButtonProperty;

typedef enum ButtonStatus {
    NORMAL,
    HOVER,
    CLICK
} ButtonStatus;

// Side buttons
typedef enum SideProperty {
    LEFT,
    RIGHT
} SideProperty;

typedef enum SideStatus {
    STOP,
    MOVE
} SideStatus;

// Vertical Buttons
typedef enum VerticalProperty {
    FLIP,
    SPREAD
} VerticalProperty;

// Toolbar components
typedef struct{
    SDL_FRect *background;
    SDL_FRect *buttonArr[NUM_MAIN_BUTTON];
    SDL_FRect *sideArr[NUM_SIDE_BUTTON];
    SDL_FRect *verticalArr[NUM_VERTICAL_BUTTON];
} Toolbar;

#endif // TOOLBAR_DEFINE_HPP