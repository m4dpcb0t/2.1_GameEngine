#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "GameObject.h"

class PauseState : public GameState
{
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const {return s_pauseID;}

      //  virtual void setCallbacks(const std::vector<Callback>& callbacks);

    private:

        static void s_pauseToMain();
        static void s_resumeToPlay();

        static const std::string s_pauseID;
        std::vector<GameObject* > m_gameObjects;
};

#endif // PAUSESTATE_H
