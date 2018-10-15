#include "HexagonShape.h"
#include <SDL.h>
#include "GameState.h"


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

    SDL_SetRenderDrawColor(renderer, LineColor.red, LineColor.green, LineColor.blue, LineColor.alpha);

    SDL_RenderDrawLine(renderer, x - 2 * lineLength, y - lineLength * GameState::IsometricScaling, x - 2 * lineLength, y + lineLength* GameState::IsometricScaling);
    SDL_RenderDrawLine(renderer, x - 2 * lineLength, y - lineLength* GameState::IsometricScaling, x, y - 2* lineLength* GameState::IsometricScaling);
    SDL_RenderDrawLine(renderer, x + 2 * lineLength, y - lineLength* GameState::IsometricScaling, x, y - 2* lineLength* GameState::IsometricScaling);

    // Only need to render the top 3 lines if it's a repeatable hexagon
    if (!repeatable){
        SDL_RenderDrawLine(renderer, x + 2 * lineLength, y - lineLength* GameState::IsometricScaling, x + 2 * lineLength, y + lineLength* GameState::IsometricScaling);
        SDL_RenderDrawLine(renderer, x - 2 * lineLength, y + lineLength* GameState::IsometricScaling, x, y + 2* lineLength* GameState::IsometricScaling);
        SDL_RenderDrawLine(renderer, x + 2 * lineLength, y + lineLength* GameState::IsometricScaling, x, y + 2* lineLength* GameState::IsometricScaling);
    }



}
