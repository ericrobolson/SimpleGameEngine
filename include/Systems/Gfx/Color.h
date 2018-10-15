#ifndef COLOR_H
#define COLOR_H
#include <SDL.h>
class Color
{
    public:
        Color();
        virtual ~Color();

        Uint8 alpha;
        Uint8 red;
        Uint8 green;
        Uint8 blue;

    protected:

    private:
};

#endif // COLOR_H
