#ifndef GAMESTATE_H
#define GAMESTATE_H

#include<vector>

class GameState
{
    public:
        GameState();
        virtual ~GameState();

        const static int MaxXTiles = 120;
        const static int MaxYTiles = 120;
        const static int HextileSize = 64; // should be divisible by 4
        static constexpr float IsometricScaling = .577; // tan(30*), what's used to calculate the vertical scale of objects

    protected:

    private:
        std::vector<int> _players; // contains the player ids
        int _currentPlayerTurn; // the id of the current player's turn
};

#endif // GAMESTATE_H
