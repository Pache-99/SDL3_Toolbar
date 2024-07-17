#include "toolbar_makePath.h"
#include "toolbar_component.h"

char* buttonTexturePath(enum ButtonProperty button, enum ButtonStatus status){

    char* frontChar, backChar;

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
        case MAX:
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

        return charLink;
}

char* sideTexturePath(enum SideProperty side){
    // TODO: LEFT, RIGHT 받아오기
}

char* verticalTexturePath(enum VerticalProperty vertical){
    // TODO: FLIP, SPREAD 받아오기 
}