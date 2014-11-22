#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <iostream>
#include <vector>
#include "TextureManager.h"

/*
    Abstract base class
*/

class GameState
{
    public:
        virtual void update() = 0;
        virtual void render() = 0;

        //like load/constructor method
        virtual bool onEnter() = 0;

        //like clean method
        virtual bool onExit() = 0;

        //Getter for state ID returns static const ID
        //ID is used to ensure states don't get repeated
        virtual std::string getStateID() const = 0;
        bool currentState;

    protected:
        std::vector<std::string> m_textureIDList;

};


#endif // GAMESTATE_H
