#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(void (*callback)() ) :
GL_GameObject(), m_callback(callback), m_bReleased(true)
{
    //ctor
   // m_currentFrame = MOUSE_OUT;
}

MenuButton::~MenuButton()
{
    //dtor
}

bool MenuButton::load(const LoaderParams* pParams)
{
    GL_GameObject::load(pParams);
   // m_callbackID = pParams ->getCallbackID();
    m_currentFrame = MOUSE_OUT; //start at frame 0

    return true;
}

void MenuButton::update()
{
    Vector2D* pMousePos = InputHandler::Instance() ->getMousePosition();

    if(pMousePos ->getX() < (m_position.getX() + m_width)
    && pMousePos ->getX() > m_position.getX()
    && pMousePos ->getY() < (m_position.getY() + m_height)
    && pMousePos ->getY() > m_position.getY())
    {
        m_currentFrame = MOUSE_OVER;

        if(InputHandler::Instance() ->getMouserButtonState(M_LEFT)
        && m_bReleased)
        {
            m_currentFrame = CLICKED;

            if(m_callback != 0)
                m_callback(); //call our callback function
            m_bReleased = false;
        }
        else if(!InputHandler::Instance() ->getMouserButtonState(M_LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
        m_currentFrame = MOUSE_OUT;

}

void MenuButton::draw()
{
    GL_GameObject::draw();
}

void MenuButton::clean()
{
    GL_GameObject::clean();
}

 