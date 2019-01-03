#ifndef BASICMAZE_H
#define BASICMAZE_H


class BasicMaze
{
    public:
        static const int MaxGridSize = 32;

        BasicMaze();
        virtual ~BasicMaze();

        void Reset();
        void Generate();

        bool Occupied(int x, int y);

    protected:

    private:
        void SetMaze(bool value);
        void CarvePath(int x, int y, int length);
        bool _grid[MaxGridSize][MaxGridSize];
};

#endif // BASICMAZE_H
