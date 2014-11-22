#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "LoaderParams.h"

//Abstract base class
class GameObject
{
    public:
        //virtual uses the definition from the type of the object itself
        //Forces any derived class to declare and implement them
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;

        //Takes paramaters from LoaderParams class
        virtual bool load(const LoaderParams* pParams) = 0;

    protected:

        GameObject() {}
        virtual ~GameObject() {}
};

#endif // GAMEOBJECT_H
