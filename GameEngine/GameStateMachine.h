#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include "GameState.h"

class GameStateMachine
{
    public:
        void pushState(GameState* pState);
        void changeState(GameState* pState);
        void popState();

        void update();
        void render();
        void clean();
    protected:
    private:
        std::vector<GameState*> m_gameStates;
};

#endif // GAMESTATEMACHINE_H
