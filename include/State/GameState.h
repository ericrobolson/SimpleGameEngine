#ifndef GAMESTATE_H
#define GAMESTATE_H

#include<vector>

class GameState
{
    public:
        static GameState& Instance(){
            static GameState *instance = new GameState();
            return *instance;
        };

        virtual ~GameState();

        bool Paused;
        static const int LevelWidth = 1000;
        static const int LevelHeight = 1000;
        static const int GfxScaling = 4; // Internal resolution is 1x, gfx resolution is 4x. Should be even. E.g. for a display screen of 1920x1080, the internal representation would be a grid of 960x540

    protected:

    private:
        GameState();

        std::vector<int> _players; // contains the player ids
        int _currentPlayerTurn; // the id of the current player's turn
};

#endif // GAMESTATE_H
