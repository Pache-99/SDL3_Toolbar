#include "toolbar_component.h"

void 


Toolbar* createToolbar(SDL_Window* window) {

    Toolbar* toolbar = (Toolbar*)malloc(sizeof(Toolbar));

    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    toolbar->backRect = (SDL_FRect*){0, 0, (float)width, (float)height}; 

    // TODO:
    // 1) window 크기를 구한다. 
    // 2) 각 텍스처의 해상도 크기를 구한다. 

    // SDL_RectFitinRect => rect가 다른 rect 안에 들어가면 비례 계산 

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){



    }

    for (int i = 0; i <  NUM_SIDE_BUTTON; i++){

    }

    for (int i = 0; i < NUM_VERTICAL_BUTTON; i++){

    }

    return toolbar;
}

void resizeWindow() {

}


void reprintWindow() {

}

