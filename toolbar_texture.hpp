#ifndef TOOLBAR_TEXTURE_HPP
#define TOOLBAR_TEXTURE_HPP

#include "toolbar_define.hpp"

#define IMAGE_PATH_BACKGROUND "../resource/basic-bg2.jpg"

// "resource/main" images
#define IMAGE_PATH_MAIN_ROOT "../resource/main/"

#define IMAGE_PATH_MAIN_PIN "1_pin"
#define IMAGE_PATH_MAIN_LOGIN "2_login"
#define IMAGE_PATH_MAIN_MULTI "3_multi"
#define IMAGE_PATH_MAIN_MINI "4_mini"
#define IMAGE_PATH_MAIN_MAX "5_max"
#define IMAGE_PATH_MAIN_EXIT "6_exit"

#define IMAGE_PATH_MAIN_NORMAL "_default.png"
#define IMAGE_PATH_MAIN_HOVER "_hover.png"
#define IMAGE_PATH_MAIN_CLICK "_click.png"

// "resource/side" images
#define IMAGE_PATH_SIDE_ROOT "../resource/side/"

#define IMAGE_PATH_SIDE_LEFT "bg-left-v2.png"
#define IMAGE_PATH_SIDE_RIGHT "bg-right-v2.png"

#define IMAGE_PATH_SIDE_FLIP "bg-bottom-up-v2.png"
#define IMAGE_PATH_SIDE_SPREAD "bg-bottom-down-v2.png"

SDL_Texture* loadBackTexture(SDL_Renderer *renderer);
SDL_Texture* loadButtonTexture(SDL_Renderer *renderer, ButtonProperty button, ButtonStatus status);
SDL_Texture* loadSideTexture(SDL_Renderer *renderer, SideProperty side);
SDL_Texture* loadVerticalTexture(SDL_Renderer *renderer, VerticalProperty vertical);

#endif // TOOLBAR_TEXTURE_HPP