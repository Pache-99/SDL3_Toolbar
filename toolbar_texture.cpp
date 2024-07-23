#include "toolbar_texture.hpp"

SDL_Texture* loadBackTexture(SDL_Renderer *renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, IMAGE_PATH_BACKGROUND);

    return texture;
}

SDL_Texture* loadButtonTexture(SDL_Renderer *renderer, ButtonProperty button, ButtonStatus status){

    char* frontChar;
    char* backChar;

    switch(button){
        case PIN:
            frontChar = IMAGE_PATH_MAIN_PIN;
            break;
        case LOGIN:
            frontChar = IMAGE_PATH_MAIN_LOGIN;
            break;
        case MULTI:
            frontChar = IMAGE_PATH_MAIN_MULTI;
            break;
        case MINI:
            frontChar = IMAGE_PATH_MAIN_MINI;
            break;
        case FULLSCREEN:
            frontChar = IMAGE_PATH_MAIN_MAX;
            break;
        case EXIT:
            frontChar = IMAGE_PATH_MAIN_EXIT;
            break;
    }

    switch(status){
        case NORMAL:
            backChar = IMAGE_PATH_MAIN_NORMAL;
            break;
        case HOVER:
            backChar = IMAGE_PATH_MAIN_HOVER;
            break;
        case CLICK:
            backChar = IMAGE_PATH_MAIN_CLICK;
            break;
    }

    char* charLink = 
        (char*)malloc(strlen(IMAGE_PATH_MAIN_ROOT) + strlen(frontChar) + strlen(backChar) + 1);

    strcpy(charLink, IMAGE_PATH_MAIN_ROOT);
    strcat(charLink, frontChar);
    strcat(charLink, backChar);

    SDL_Texture* texture = IMG_LoadTexture(renderer, charLink);

    if (texture == NULL){
        SDL_Log("Can't load the texture!", SDL_GetError());
    }

    return texture;
}

SDL_Texture* loadSideTexture(SDL_Renderer *renderer, SideProperty side){
    
    char* frontChar = IMAGE_PATH_SIDE_ROOT ;
    char* backChar;

    switch(side){
        case LEFT:
            backChar = IMAGE_PATH_SIDE_LEFT;
            break;
        case RIGHT:
            backChar = IMAGE_PATH_SIDE_RIGHT;
            break;
    }

    char* charLink = 
        (char*)malloc(strlen(frontChar) + strlen(backChar) + 1);

    strcpy(charLink, frontChar);
    strcat(charLink, backChar);

    SDL_Texture *texture = IMG_LoadTexture(renderer, charLink);

    if (texture == NULL){
        SDL_Log("Can't load the texture!", SDL_GetError());
    }

    return texture;
}

SDL_Texture* loadVerticalTexture(SDL_Renderer *renderer, VerticalProperty vertical){
    
    char* frontChar = IMAGE_PATH_SIDE_ROOT;
    char* backChar;

    switch(vertical){
        case FLIP:
            backChar = IMAGE_PATH_SIDE_FLIP;
            break;
        case SPREAD:
            backChar = IMAGE_PATH_SIDE_SPREAD;
            break;
    }

    char* charLink = 
        (char*)malloc(strlen(frontChar) + strlen(backChar) + 1);

        
    strcpy(charLink, frontChar);
    strcat(charLink, backChar);

    SDL_Texture *texture = IMG_LoadTexture(renderer, charLink);

    if (texture == NULL){
        SDL_Log("Can't load the texture!", SDL_GetError());
    }

    return texture;
}


