#include "HexagonShape.h"
#include <SDL.h>

HexagonShape::HexagonShape()
{
    x = 0;
    y = 0;
    hexRadius = 4;
}

HexagonShape::~HexagonShape()
{
    //dtor
}

void HexagonShape::Render(SDL_Renderer* renderer){
    int lineLength = hexRadius / 4;

    SDL_RenderDrawLine(renderer, x - 2 * lineLength, y - lineLength, x - 2 * lineLength, y + lineLength);
    SDL_RenderDrawLine(renderer, x - 2 * lineLength, y - lineLength, x, y - 2* lineLength);
    SDL_RenderDrawLine(renderer, x + 2 * lineLength, y - lineLength, x, y - 2* lineLength);

    // Only need to render the top 3 lines if it's a repeatable hexagon
    if (!repeatable){
        SDL_RenderDrawLine(renderer, x + 2 * lineLength, y - lineLength, x + 2 * lineLength, y + lineLength);
        SDL_RenderDrawLine(renderer, x - 2 * lineLength, y + lineLength, x, y + 2* lineLength);
        SDL_RenderDrawLine(renderer, x + 2 * lineLength, y + lineLength, x, y + 2* lineLength);
    }

}
