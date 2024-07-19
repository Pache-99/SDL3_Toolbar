#include "toolbar_main.h"

void runToolbar(){

    SDL_Window *window = makeWindow();
    SDL_Renderer *renderer = makeRenderer(window);

    // int width, height;
    // SDL_GetCurrentRenderOutputSize(renderer, &width, &height);
    // SDL_SetWindowSize(window, width, height);
    // SDL_SetWindowFullscreen(window, true);
    
    Toolbar *toolbar = (Toolbar*)malloc(sizeof(Toolbar));

    bool flip = false;
    settingToolbar(window, renderer, toolbar, flip);

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
        }
        else if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE){
            quit = true;
        }
        
        else if (e.type == SDL_EVENT_WINDOW_RESIZED){
            settingToolbar(window, renderer, toolbar, flip);
            SDL_RenderPresent(renderer);
        }

        SDL_GetMouseState(&mouse_X, &mouse_Y);
        mousePos = (SDL_FPoint){mouse_X, mouse_Y};

        // Mouse event
        switch(e.type){

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                clickButton(window, renderer, toolbar, mousePos, true);
                SDL_RenderPresent(renderer);
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                clickButton(window, renderer, toolbar, mousePos, false);
                SDL_RenderPresent(renderer);
                break;

            case SDL_EVENT_MOUSE_MOTION:
                hoverButton(window, renderer, toolbar, mousePos);
                // SDL_RenderPresent(renderer);
                break;
        }
    }
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