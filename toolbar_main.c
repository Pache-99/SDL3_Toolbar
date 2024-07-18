#include "toolbar_main.h"

void runToolbar(){

    SDL_Window *window = makeWindow();
    SDL_Renderer *renderer = makeRenderer(window);
    SDL_Texture *texture = loadBackTexture(renderer);

    // int width, height;
    // SDL_GetCurrentRenderOutputSize(renderer, &width, &height);
    // SDL_SetWindowSize(window, width, height);
    // SDL_SetWindowFullscreen(window, true);

    Toolbar *toolbar = (Toolbar*)malloc(sizeof(Toolbar));
    setToolbar(window, renderer, texture, toolbar, false); // Temp: false

    SDL_RenderTexture(renderer, texture, NULL, toolbar->background);
    SDL_RenderPresent(renderer);

    // float a, b;
    // SDL_GetTextureSize(texture, &a, &b);
}

void runWindow(){

    bool quit = false;

    while (!quit){

        SDL_Event e;
        SDL_WaitEvent(&e);

        // Quit event
        if (e.type == SDL_EVENT_QUIT){
            quit = true;
        }
        else if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE){
            quit = true;
        }

        // Mouse event
        switch(e.type){

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                // TODO: 어떤 버튼 클릭인지 체크  
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                // TODO: 어떤 버튼을 누른 상태에서 => 해당 rect를 나가지 않고 마우스를 땠는지 체크
                // TODO: 위 조건을 만족 시 기능 실행
                break;

            case SDL_EVENT_MOUSE_MOTION:
                

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
    runWindow();
    
    return 0;
}