#ifndef TOOLBAR_COMPONENT_H
#define TOOLBAR_COMPONENT_H

#include "toolbar_texture.h"
#include "toolbar_function.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h> 
#include <SDL3_image/SDL_image.h>

SDL_Window* makeWindow();
SDL_Renderer* makeRenderer(SDL_Window *window);
SDL_Texture* repaintTexture(SDL_Renderer *renderer);

void settingToolbar(SDL_Window* window, SDL_Renderer* renderer, Toolbar *toolbar, bool button);
int drawWindow(SDL_Renderer *renderer, Toolbar *toolbar, bool side, bool button);

int clickButton(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos, bool down);
int hoverButton(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos);

void isFlipToggle(bool flip);

#endif //TOOLBAR_COMPONENT_H