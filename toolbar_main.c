#include "toolbar_main.h"

int runToolbar(){

    SDL_Window *window = makeWindow();
    SDL_Renderer *renderer = makeRenderer(window);

    // SDL_SetWindowFullscreen(window, true);
    
    Toolbar *toolbar = (Toolbar*)malloc(sizeof(Toolbar));

    bool button = true;
    settingToolbar(window, renderer, toolbar, button);

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
            settingToolbar(window, renderer, toolbar, button);
            SDL_RenderPresent(renderer);
        }

        SDL_GetMouseState(&mouse_X, &mouse_Y);
        mousePos = (SDL_FPoint){mouse_X, mouse_Y};

        // Mouse event
        switch(e.type){

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                clickButton(window, renderer, toolbar, mousePos, true);
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (clickButton(window, renderer, toolbar, mousePos, false) == EXIT)
                quit = true;
                break;

            case SDL_EVENT_MOUSE_MOTION:
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

    runToolbar();

    return 0;
}