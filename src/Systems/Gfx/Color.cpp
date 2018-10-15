#include "Color.h"
#include <SDL.h>

Color::Color()
{
    alpha = SDL_ALPHA_OPAQUE;
    red = 0;
    green = 0;
    blue = 0;
}

Color::~Color()
{
    //dtor
}
