#include "toolbar_component.hpp"

static bool isFlip = false;
static bool activatePin;

static float buttonRatio_W;
static float buttonRatio_H;
static float sideRatio_W;
static float sideRatio_H;
static float verticalRatio_W;
static float verticalRatio_H;

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

// Summary: 현재 윈도우 사이즈에 맞게 요소 구성 
void settingToolbar(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar) {

    // Initialize tolbar components
    toolbar->background = (SDL_FRect*)malloc(sizeof(SDL_FRect));

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){
        toolbar->buttonArr[i] = (SDL_FRect*)malloc(sizeof(SDL_FRect));
    }

    for (int i = 0; i < NUM_SIDE_BUTTON; i++){
        toolbar->sideArr[i] = (SDL_FRect*)malloc(sizeof(SDL_FRect));
    }

    for (int i = 0; i < NUM_VERTICAL_BUTTON; i++){
        toolbar->verticalArr[i] = (SDL_FRect*)malloc(sizeof(SDL_FRect));
    }

    // Window and background
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    *(toolbar -> background) = (SDL_FRect){0, 0, windowWidth, windowHeight}; 

        // Window Changed ratio
    int windowRatio = windowWidth / SCREEN_WIDTH;

    // 10:2 (5)
    // 5:1

    // Buttons
    float buttonWidth, buttonHeight;
    SDL_GetTextureSize(loadButtonTexture(renderer, PIN, NORMAL), &buttonWidth, &buttonHeight);

        // Button Ratio 
    buttonRatio_W = windowWidth / buttonWidth; 
    buttonRatio_H = windowHeight / buttonHeight;
    
    buttonWidth = windowWidth / buttonRatio_W;
    buttonHeight = windowHeight / buttonRatio_H;

        // Buttons tray
    float trayWidth = buttonWidth * NUM_MAIN_BUTTON;
    float trayHeight = buttonHeight;
    float tray_X = (windowWidth / 2) - (trayWidth / 2);
    float tray_Y = 0;

    float button_X;

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){
        button_X = tray_X + (i * buttonWidth);
        *(toolbar->buttonArr[i]) = (SDL_FRect){button_X, tray_Y, buttonWidth, buttonHeight};
    }

    // Side
    float sideWidth, sideHeight;
    SDL_GetTextureSize(loadSideTexture(renderer, LEFT), &sideWidth, &sideHeight);

        // Side Ratio 
    sideRatio_W = windowWidth / sideWidth; 
    sideRatio_H = windowHeight / sideHeight;
    
    sideWidth = windowWidth / sideRatio_W;
    sideHeight = windowHeight / sideRatio_H;

    float left_X = tray_X - sideWidth;
    float left_Y = 0;
    float right_X = tray_X + trayWidth;
    float right_Y = 0;

    *(toolbar->sideArr[LEFT]) = (SDL_FRect){left_X, left_Y, sideWidth, sideHeight};
    *(toolbar->sideArr[RIGHT]) = (SDL_FRect){right_X, right_Y, sideWidth, sideHeight};

    // Vertical
    float verticalWidth, verticalHeight;
    SDL_GetTextureSize(loadVerticalTexture(renderer, FLIP), &verticalWidth, &verticalHeight);

        // Vertical Ratio 
    verticalRatio_W = windowWidth / verticalWidth; 
    verticalRatio_H = windowHeight / verticalHeight;
    
    verticalWidth = windowWidth / verticalRatio_W;
    verticalHeight = windowHeight / verticalRatio_H;

    float flip_X = (windowWidth / 2) - (verticalWidth / 2);
    float flip_Y = trayHeight;
    float spread_X = flip_X;
    float spread_Y = 0;

    *(toolbar->verticalArr[FLIP]) = (SDL_FRect){flip_X, flip_Y, verticalWidth, verticalHeight};
    *(toolbar->verticalArr[SPREAD]) = (SDL_FRect){spread_X, spread_Y, verticalWidth, verticalHeight};

    drawWindow(renderer, toolbar, true, true);
}

void resettingToolbar(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar){

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float buttonWidth, buttonHeight;
    float button_X;

    buttonWidth = windowWidth / buttonRatio_W;
    buttonHeight = windowHeight / buttonRatio_H;

    button_X = (toolbar->buttonArr[0]->x) / buttonRatio_W; // TEST

        // Buttons tray
    float trayWidth = buttonWidth * NUM_MAIN_BUTTON;
    float trayHeight = buttonHeight;
    float tray_X = toolbar->buttonArr[0]->x;
    // float tray_X = button_X; // problem
    float tray_Y = 0;

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){
        button_X = tray_X + (i * buttonWidth);
        *(toolbar->buttonArr[i]) = (SDL_FRect){button_X, tray_Y, buttonWidth, buttonHeight};
    }

    // Side
    float sideWidth, sideHeight;

    sideWidth = windowWidth / sideRatio_W;
    sideHeight = windowHeight / sideRatio_H;

    float left_X = tray_X - sideWidth;
    float left_Y = 0;
    float right_X = tray_X + trayWidth;
    float right_Y = 0;

    *(toolbar->sideArr[LEFT]) = (SDL_FRect){left_X, left_Y, sideWidth, sideHeight};
    *(toolbar->sideArr[RIGHT]) = (SDL_FRect){right_X, right_Y, sideWidth, sideHeight};

    // Vertical
    float verticalWidth, verticalHeight;

    verticalWidth = windowWidth / verticalRatio_W;
    verticalHeight = windowHeight / verticalRatio_H;

    float flip_X = tray_X + (toolbar->buttonArr[0]->w * (NUM_MAIN_BUTTON / 2) - (verticalWidth / 2));
    float flip_Y = trayHeight;
    float spread_X = flip_X;
    float spread_Y = 0;

    *(toolbar->verticalArr[FLIP]) = (SDL_FRect){flip_X, flip_Y, verticalWidth, verticalHeight};
    *(toolbar->verticalArr[SPREAD]) = (SDL_FRect){spread_X, spread_Y, verticalWidth, verticalHeight};

    bool side;
    bool button;

    side = isFlip == true ? false : true;
    button = side; 

    drawWindow(renderer, toolbar, side, button);
}

// Summary: 화면 렌더링
// * (bool)side: 양쪽 사이드바 재렌더링 여부
// * (bool)button: 메인 버튼 재렌더링 여부 
int drawWindow(SDL_Renderer *renderer, Toolbar *toolbar, bool side, bool button){

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, loadBackTexture(renderer), NULL, toolbar->background);

    if (side){
        SDL_RenderTexture(renderer, loadVerticalTexture(renderer, FLIP), NULL, toolbar->verticalArr[FLIP]);

        for (int i = 0; i < NUM_SIDE_BUTTON; i++){
            SDL_RenderTexture(renderer, loadSideTexture(renderer, static_cast<SideProperty>(i)), NULL, toolbar->sideArr[i]);
        }   
    }
    else{
        SDL_RenderTexture(renderer, loadVerticalTexture(renderer, SPREAD), NULL, toolbar->verticalArr[SPREAD]);
    }

    if (button){

        for (int i = 0; i < NUM_MAIN_BUTTON; i++){

            SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), NORMAL), NULL, toolbar->buttonArr[i]);
        }
    }

    return 0;
}

// Summary: 메인 버튼 click down & click up
int clickButton(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos, bool down){

    SDL_RenderClear(renderer);
    drawWindow(renderer, toolbar, true, true);

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){

        if (!isFlip && SDL_PointInRectFloat(&mousePos, toolbar->buttonArr[i])){

            if (down){

                if (i != PIN && activatePin){
                    continue;
                }

                SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), CLICK), NULL, toolbar->buttonArr[i]);
                SDL_RenderPresent(renderer);
                break;
            }
            else {

                SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), HOVER), NULL, toolbar->buttonArr[i]);

                if (i == PIN){
                    activatePin = activatePin == false ? true : false;  
                }

                if (activatePin){
                    break;
                }

                if (i == EXIT){
                    return EXIT;
                }

                classifyButton(i, window);
                SDL_RenderPresent(renderer);
                break;
            }
        }
    }

    if (down){
        return 0;
    }

    for (int i = 0; i < NUM_VERTICAL_BUTTON; i++){

        if (!isFlip && SDL_PointInRectFloat(&mousePos, toolbar->verticalArr[FLIP])){
            drawWindow(renderer, toolbar, false, false);
            isFlipToggle(true);

            SDL_RenderPresent(renderer);
        }
        else if (isFlip && SDL_PointInRectFloat(&mousePos, toolbar->verticalArr[SPREAD])){
            drawWindow(renderer, toolbar, true, true);
            isFlipToggle(false);

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}

// Summary: 버튼 호버링
int hoverButton(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos){

    if (isFlip){
        return 0;
    }

    SDL_RenderClear(renderer);
    drawWindow(renderer, toolbar, true, false);

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){

        if (SDL_PointInRectFloat(&mousePos, toolbar->buttonArr[i])){

            if (i != PIN && activatePin){
                SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), NORMAL), NULL, toolbar->buttonArr[i]);
                continue;
            }

            SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), HOVER), NULL, toolbar->buttonArr[i]);
        }
        else {

            if (i == PIN && activatePin){
                SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), CLICK), NULL, toolbar->buttonArr[i]);
                continue;
            }

            SDL_RenderTexture(renderer, loadButtonTexture(renderer, static_cast<ButtonProperty>(i), NORMAL), NULL, toolbar->buttonArr[i]);
        }
    }
    SDL_RenderPresent(renderer);

    return 0;
}

int clickSide(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos, SideStatus sideStatus){

    if (activatePin){
        return 0;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    *(toolbar->background) = (SDL_FRect){0, 0, windowWidth, windowHeight};

    static bool click = false;
    static bool left = false;
    static bool right = false;

    for (int i = 0; i < NUM_SIDE_BUTTON; i++){

        if (sideStatus == DOWN && SDL_PointInRectFloat(&mousePos, toolbar->sideArr[LEFT])){
            click = true;
            left = true;
            right = false;
        }
        else if(sideStatus == DOWN && SDL_PointInRectFloat(&mousePos, toolbar->sideArr[RIGHT])){
            click = true;
            left = false;
            right = true;
        }
    
        if (sideStatus == UP){
            click = false;
            left = false;
            right = false;
        }

        if (click == true && sideStatus == MOTION){

            if (left){

                if (toolbar->sideArr[LEFT]->x >= 0 && 
                    (toolbar->sideArr[RIGHT]->x + toolbar->sideArr[RIGHT]->w) <= windowWidth){

                    toolbar->sideArr[LEFT]->x = mousePos.x;
                }
                else if (toolbar->sideArr[LEFT]->x < 0){
                    toolbar->sideArr[LEFT]->x = 0;
                }
                else if ((toolbar->sideArr[RIGHT]->x + toolbar->sideArr[RIGHT]->w) > windowWidth){
                    toolbar->sideArr[LEFT]->x  = windowWidth - 
                        ((toolbar->sideArr[RIGHT]->w * NUM_SIDE_BUTTON) + (toolbar->buttonArr[0]->w * NUM_MAIN_BUTTON));
                }

                for (int i = 0; i < NUM_MAIN_BUTTON; i++){
                    toolbar->buttonArr[i]->x = 
                        toolbar->sideArr[LEFT]->x + toolbar->sideArr[LEFT]->w + (toolbar->buttonArr[0]->w * i);
                }

                for (int i = 0; i < NUM_VERTICAL_BUTTON; i++){
                    toolbar->verticalArr[i]->x = 
                        (toolbar->buttonArr[0]->x + toolbar->buttonArr[0]->w * (NUM_MAIN_BUTTON / 2)) - (toolbar->verticalArr[0]->w / 2); 
                }

                toolbar->sideArr[RIGHT]->x = 
                    toolbar->buttonArr[NUM_MAIN_BUTTON - 1]->x + toolbar->buttonArr[0]->w;
            }
            else if (right){

                if ((toolbar->sideArr[RIGHT]->x + toolbar->sideArr[RIGHT]->w) <= windowWidth &&
                    toolbar->sideArr[LEFT]->x >= 0){
                    toolbar->sideArr[RIGHT]->x = mousePos.x;
                }
                else if ((toolbar->sideArr[RIGHT]->x + toolbar->sideArr[RIGHT]->w) > windowWidth){
                    toolbar->sideArr[RIGHT]->x  = windowWidth - toolbar->sideArr[RIGHT]->w;
                }
                else if (toolbar->sideArr[LEFT]->x < 0){
                    toolbar->sideArr[RIGHT]->x = 
                        ((toolbar->sideArr[RIGHT]->w * NUM_SIDE_BUTTON) + (toolbar->buttonArr[0]->w * NUM_MAIN_BUTTON)) - 
                            toolbar->sideArr[RIGHT]->w;
                }

                for (int i = 0; i < NUM_MAIN_BUTTON; i++){
                    
                    toolbar->buttonArr[i]->x = 
                        (toolbar->sideArr[RIGHT]->x - (toolbar->buttonArr[0]->w * NUM_MAIN_BUTTON)) + 
                            (toolbar->buttonArr[0]->w * i);
                }

                for (int i = 0; i < NUM_VERTICAL_BUTTON; i++){

                    toolbar->verticalArr[i]->x = 
                        (toolbar->buttonArr[0]->x + toolbar->buttonArr[0]->w * (NUM_MAIN_BUTTON / 2)) - (toolbar->verticalArr[0]->w / 2); 
                }

                toolbar->sideArr[LEFT]->x = toolbar->buttonArr[0]->x - toolbar->sideArr[LEFT]->w;
            }
        }
    }

    return 0;
}

void isFlipToggle(bool flip){

    isFlip = flip;
}