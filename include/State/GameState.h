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

    protected:

    private:
        std::vector<int> _players; // contains the player ids
        int _currentPlayerTurn; // the id of the current player's turn
};

#endif // GAMESTATE_H
