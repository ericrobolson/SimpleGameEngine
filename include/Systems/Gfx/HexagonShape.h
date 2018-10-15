#ifndef HEXAGONSHAPE_H
#define HEXAGONSHAPE_H
#include <SDL.h>
#include "Color.h"

class HexagonShape
{
    public:
        HexagonShape();
        virtual ~HexagonShape();

        int x;
        int y;
        int hexRadius;

        bool repeatable;

        Color LineColor;

        void Render(SDL_Renderer* render);
    private:
    protected:

    private:
};

#endif // HEXAGONSHAPE_H
