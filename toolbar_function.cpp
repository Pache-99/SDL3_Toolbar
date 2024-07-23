#include "toolbar_function.hpp"

void classifyButton(int button, SDL_Window *window){

    switch(button){
        case PIN:

            break;
        case LOGIN:

            break;
        case MULTI:

            break;
        case MINI:
            func_Minimize(window);
            break;
        case FULLSCREEN:
            func_Maximize(window);
            break;
    }
}

void func_Pin(bool activate){

    
}

void func_Login(){

    // TODO: 로그인창에 대한 정보가 필요함. 

}

void func_Multimonitor(){

    // int numDisplays = SDL_GetNumVideoDisplays(); // 없는 함수

    // if (numDisplays == 0){
    //     SDL_SetError("Can't find monitor");
    // }
    
    // TODO: 새로 생성된 윈도우들이 기존 윈도우와 같게, 독립적으로 작동하도록? 아니면 툴바 없이?
}

void func_Minimize(SDL_Window *window){

    SDL_MinimizeWindow(window);
}

void func_Maximize(SDL_Window *window){

    // 0 is fullscreen mode
    int isFullscreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;

    if (isFullscreen != 0) {
        SDL_Log("SET WINDOW NORMAL SIZE");
        SDL_SetWindowFullscreen(window, false);
    }
    else{
        SDL_Log("SET WINDOW FULLSIZE");
        SDL_SetWindowFullscreen(window, true);
    }

}

