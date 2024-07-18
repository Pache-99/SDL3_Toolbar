#include "toolbar_component.h"

SDL_Window* makeWindow(){

    SDL_Window *window = SDL_CreateWindow("SDL3_Toolbar",
                        SCREEN_WIDTH, SCREEN_HEIGHT,
                        SDL_WINDOW_RESIZABLE);
    return window;
}

SDL_Renderer* makeRenderer(SDL_Window *window){

    if(window == NULL){
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    return renderer;
}

SDL_Texture* repaintTexture(SDL_Renderer *renderer){
    
    if(renderer == NULL){
        return NULL;
    }

}

// 현재 윈도우 사이즈에 맞게 화면 구성요소를 자동 갱신 & 출력
void setToolbar(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Toolbar *toolbar, bool flip) {

    //  Temp toolbar components
    SDL_FRect background;
    SDL_FRect buttonArr[NUM_MAIN_BUTTON];
    SDL_FRect sideArr[NUM_SIDE_BUTTON];
    SDL_FRect verticalArr[NUM_VERTICAL_BUTTON];

    // Window and background
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    background = (SDL_FRect){0, 0, windowWidth, windowHeight};
    // *(toolbar -> background) = background;
    SDL_RenderTexture(renderer, texture, NULL, &background);

    // Buttons
    float buttonWidth, buttonHeight;
    SDL_GetTextureSize(loadButtonTexture(renderer, PIN, NORMAL), &buttonWidth, &buttonHeight);

        // Buttons tray
    float trayWidth = buttonWidth * NUM_MAIN_BUTTON;
    float trayHeight = buttonHeight;
    float tray_X = (windowWidth / 2) - (trayWidth / 2);
    float tray_Y = 0;

    float button_X;

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){
        button_X = tray_X + (i * buttonWidth);
        buttonArr[i] = (SDL_FRect){button_X, tray_Y, buttonWidth, buttonHeight};

        if (!flip){
        SDL_RenderTexture(renderer, loadButtonTexture(renderer, i, NORMAL), NULL, &buttonArr[i]);
        }
    }

    // Side
    float sideWidth, sideHeight;
    SDL_GetTextureSize(loadSideTexture(renderer, LEFT), &sideWidth, &sideHeight);

    float left_X = tray_X - sideWidth;
    float left_Y = 0;
    float right_X = tray_X + trayWidth;
    float right_Y = 0;

    sideArr[LEFT] = (SDL_FRect){left_X, left_Y, sideWidth, sideHeight};
    sideArr[RIGHT] = (SDL_FRect){right_X, right_Y, sideWidth, sideHeight};

    // *(toolbar->sideArr[LEFT]) = sideArr[LEFT];
    // *(toolbar->sideArr[RIGHT]) = sideArr[RIGHT];

    for (int i = 0; i < NUM_SIDE_BUTTON; i++){

        if (!flip){
            SDL_RenderTexture(renderer, loadSideTexture(renderer, i), NULL, &sideArr[i]);
        }
    }

    // Vertical
    float verticalWidth, verticalHeight;
    SDL_GetTextureSize(loadVerticalTexture(renderer, FLIP), &verticalWidth, &verticalHeight);

    float flip_X = (windowWidth / 2) - (verticalWidth / 2);
    float flip_Y = trayHeight;
    float spread_X = flip_X;
    float spread_Y = 0;

    verticalArr[FLIP] = (SDL_FRect){flip_X, flip_Y, verticalWidth, verticalHeight};
    verticalArr[SPREAD] = (SDL_FRect){spread_X, spread_Y, verticalWidth, verticalHeight};

    // *(toolbar->verticalArr[FLIP]) = verticalArr[FLIP];
    // *(toolbar->verticalArr[SPREAD]) = verticalArr[SPREAD];

    for (int i = 0; i < NUM_VERTICAL_BUTTON; i++){

        if (!flip && i == FLIP){
            SDL_RenderTexture(renderer, loadVerticalTexture(renderer, i), NULL, &verticalArr[i]);
        }
    }
}


void resizeWindow() {

}


void reprintWindow() {

}

