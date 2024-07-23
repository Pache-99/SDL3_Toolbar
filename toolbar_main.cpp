#include "toolbar_main.hpp"

// PROJECT TODO: EXIT 메인 버튼 키를 눌렀을 때 메인 함수에 0을 반환해야함. (종료 기능 찾기)
// PROJECT TODO: window와 renderer를 가져와야 함. 
// MY TODO: 툴바 구성요소들의 비례식을 찾아야 함. 
// MY TODO: 화면 크기 조절 시 툴바 위치 고정되도록 해야 됨. 

int runToolbar(SDL_Window *window, SDL_Renderer *renderer){

    // SDL_SetWindowFullscreen(window, true);
    
    Toolbar *toolbar = (Toolbar*)malloc(sizeof(Toolbar));

    bool button = true;
    settingToolbar(window, renderer, toolbar);

    SDL_RenderPresent(renderer);

    bool quit = false;

    float mouse_X, mouse_Y;
    SDL_FPoint mousePos;

    SDL_Event e;

    while (!quit){
        SDL_WaitEvent(&e);

        // Quit event
        if (e.type == SDL_EVENT_QUIT){
            quit = true;
            break;
        }
        else if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE){
            quit = true;
            break;
        }
        
        else if (e.type == SDL_EVENT_WINDOW_RESIZED){
            resettingToolbar(window, renderer, toolbar);
            SDL_RenderPresent(renderer);
        }

        SDL_GetMouseState(&mouse_X, &mouse_Y);
        mousePos = (SDL_FPoint){mouse_X, mouse_Y};

        // Mouse event
        switch(e.type){

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                clickSide(window, renderer, toolbar, mousePos, DOWN);

                clickButton(window, renderer, toolbar, mousePos, true);
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                clickSide(window, renderer, toolbar, mousePos, UP);

                if (clickButton(window, renderer, toolbar, mousePos, false) == EXIT){
                    quit = true;
                }
                break;

            case SDL_EVENT_MOUSE_MOTION:
                clickSide(window, renderer, toolbar, mousePos, MOTION);

                hoverButton(window, renderer, toolbar, mousePos);
                break;
        }
    }

    free(toolbar);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

int main(int argc, char* argv[]){

    (void) argc;
    (void) argv;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = makeWindow();
    SDL_Renderer *renderer = makeRenderer(window);

    runToolbar(window, renderer);

    return 0;
}