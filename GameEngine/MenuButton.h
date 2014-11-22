#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "GL_GameObject.h"

class MenuButton : public GL_GameObject
{
    public:
        MenuButton(void (*callback)() );
        virtual ~MenuButton();

        virtual void draw();
        virtual void update();
        virtual void clean();
        virtual bool load(const LoaderParams* pParams);

        //void setCallback(void(*callback) ()) { m_callback = callback;}
        //int getCallbackID() { return m_callbackID; }

    private:
         //Function Pointer
        void (*m_callback)();

        bool m_bReleased;
        enum button_state
        {
            MOUSE_OUT = 0,
            MOUSE_OVER = 1,
            CLICKED = 2
        };
};

#endif // MENUBUTTON_H
