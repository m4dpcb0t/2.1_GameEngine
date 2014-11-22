#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "GameObject.h"

class MenuState : public GameState
{
    public:

        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const { return s_menuID;}

    private:

      //  virtual void setCallbacks(const std::vector<Callback>& callbacks);

        //call back the functions for menu items
        static void s_menuToPlay();
        static void s_exitFromMenu();

        static const std::string s_menuID;

        std::vector<GameObject*> m_gameObjects;

};

#endif // MENUSTATE_H
