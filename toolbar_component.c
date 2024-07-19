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

// Summary: 현재 윈도우 사이즈에 맞게 요소 구성 
void settingToolbar(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, bool button) {

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
    
    // TODO: window resize => 해상도 비례를 지키면서 줄일 수 있는 방법이 있나?
    // TODO: 현재는 window, button 간 ratio를 계산하지 않으므로 수정 필요. 

    // Window and background
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    *(toolbar -> background) = (SDL_FRect){0, 0, windowWidth, windowHeight}; 
    SDL_RenderTexture(renderer, loadBackTexture(renderer), NULL, toolbar->background);

    // Buttons
    float buttonWidth, buttonHeight;
    SDL_GetTextureSize(loadButtonTexture(renderer, PIN, NORMAL), &buttonWidth, &buttonHeight);
        // TODO: window와의 비례 추가 

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

    float left_X = tray_X - sideWidth;
    float left_Y = 0;
    float right_X = tray_X + trayWidth;
    float right_Y = 0;

    *(toolbar->sideArr[LEFT]) = (SDL_FRect){left_X, left_Y, sideWidth, sideHeight};
    *(toolbar->sideArr[RIGHT]) = (SDL_FRect){right_X, right_Y, sideWidth, sideHeight};

    // Vertical
    float verticalWidth, verticalHeight;
    SDL_GetTextureSize(loadVerticalTexture(renderer, FLIP), &verticalWidth, &verticalHeight);

    float flip_X = (windowWidth / 2) - (verticalWidth / 2);
    float flip_Y = trayHeight;
    float spread_X = flip_X;
    float spread_Y = 0;

    *(toolbar->verticalArr[FLIP]) = (SDL_FRect){flip_X, flip_Y, verticalWidth, verticalHeight};
    *(toolbar->verticalArr[SPREAD]) = (SDL_FRect){spread_X, spread_Y, verticalWidth, verticalHeight};

    bool side = button;

    drawWindow(renderer, toolbar, side, button);
}

// Summary: 화면 렌더링
// * (bool)side: 양쪽 사이드바 재렌더링 여부
// * (bool)button: 메인 버튼 재렌더링 여부 
int drawWindow(SDL_Renderer *renderer, Toolbar *toolbar, bool side, bool button){

    SDL_RenderTexture(renderer, loadBackTexture(renderer), NULL, toolbar->background);

    for (int i = 0; i < NUM_SIDE_BUTTON; i++){
        SDL_RenderTexture(renderer, loadSideTexture(renderer, i), NULL, toolbar->sideArr[i]);
    }

    if (side){
        SDL_RenderTexture(renderer, loadVerticalTexture(renderer, FLIP), NULL, toolbar->verticalArr[FLIP]);
    }
    else{
        SDL_RenderTexture(renderer, loadVerticalTexture(renderer, SPREAD), NULL, toolbar->verticalArr[SPREAD]);
    }

    if (button){

        for (int i = 0; i < NUM_MAIN_BUTTON; i++){
            SDL_RenderTexture(renderer, loadButtonTexture(renderer, i, NORMAL), NULL, toolbar->buttonArr[i]);
        }
    }

}

// Summary: 메인 버튼 down & up
int clickButton(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos, bool down){

    // TODO: Hover 이미지가 여러번 출력되는거 같음. 조금 진하게 보임 
    drawWindow(renderer, toolbar, true, true);

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){

        if (SDL_PointInRectFloat(&mousePos, toolbar->buttonArr[i])){
            switch(down){
                case true:
                    SDL_RenderTexture(renderer, loadButtonTexture(renderer, i, CLICK), NULL, toolbar->buttonArr[i]);
                    break;

                case false:
                    SDL_RenderTexture(renderer, loadButtonTexture(renderer, i, HOVER), NULL, toolbar->buttonArr[i]);

                    if (i == EXIT){
                        return EXIT;
                    }

                    classifyButton(i);
                    break;
            }

            SDL_RenderPresent(renderer);  
        }
    }

    return 0;
}

// Summary: 버튼 호버링
void hoverButton(SDL_Window *window, SDL_Renderer *renderer, Toolbar *toolbar, SDL_FPoint mousePos){

    SDL_RenderClear(renderer);
    drawWindow(renderer, toolbar, true, false);

    for (int i = 0; i < NUM_MAIN_BUTTON; i++){

        if (SDL_PointInRectFloat(&mousePos, toolbar->buttonArr[i])){
            SDL_RenderTexture(renderer, loadButtonTexture(renderer, i, HOVER), NULL, toolbar->buttonArr[i]);
        }
        else {

            SDL_RenderTexture(renderer, loadButtonTexture(renderer, i, NORMAL), NULL, toolbar->buttonArr[i]);
        }
    }
    SDL_RenderPresent(renderer);
}