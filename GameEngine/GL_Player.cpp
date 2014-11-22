#include "GL_Player.h"
#include "InputHandler.h"

GL_Player::GL_Player() : GL_GameObject()
{
    //ctor
}

GL_Player::~GL_Player()
{
    //dtor
}

bool GL_Player::load(const LoaderParams* pParams)
{
    GL_GameObject::load(pParams);

    return true;
}

void GL_Player::draw()
{
    GL_GameObject::draw();
}

void GL_Player::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

    m_velocity.setX(0);
    m_velocity.setY(0);
    m_acceleration.setX(0);
    m_acceleration.setY(0);

    handleInput();

    GL_GameObject::update();

    printf("%f", m_position.getX());
}

void GL_Player::handleInput()
{
    //***********GAMEPAD CONTROLS*****************//
    if(InputHandler::Instance() ->joysticksInitialized())
    {
        //LEFT JOYSTICK
        if(InputHandler::Instance() ->xvalues(0, 1) > 0 ||
        InputHandler::Instance() ->xvalues(0, 1) < 0)
        {
            m_velocity.setX(1 * InputHandler::Instance() ->xvalues(0, 1));
        }

        if(InputHandler::Instance() ->yvalues(0, 1) > 0 ||
        InputHandler::Instance() ->yvalues(0, 1) < 0)
        {
            m_velocity.setY(1 * InputHandler::Instance() ->yvalues(0, 1));
        }

        //RIGHT JOYSTICK
        //Check if stick has been moved if so set velocity to
        if(InputHandler::Instance() ->xvalues(0, 2) > 0 ||
        InputHandler::Instance() ->xvalues(0, 2) < 0)
        {
            m_velocity.setX(1 * InputHandler::Instance() ->xvalues(0, 2));
            cout << 1 * InputHandler::Instance() ->xvalues(0, 2) << endl;
        }

        if(InputHandler::Instance() ->yvalues(0, 2) > 0 ||
        InputHandler::Instance() ->yvalues(0, 2) < 0)
        {
            m_velocity.setY(1 * InputHandler::Instance() ->yvalues(0, 2));
        }

        /*
            A = 0   L = 4       GUIDE = 8
            B = 1   R = 5       CLSTICK = 9
            X = 2   SELECT = 6  CRSTICK = 10
            Y = 3   START = 7
        */
        if(InputHandler::Instance() ->getButtonState(0, 0)){
            m_velocity.setY(2);
            }

        if(InputHandler::Instance() ->getDpadUp() && InputHandler::Instance() ->dpadStatus == 0)
        {
            m_velocity.setY(-1);
            cout << "UP" << endl;
        }

        if(InputHandler::Instance() ->getDpadDown() && InputHandler::Instance() ->dpadStatus == 0)
        {
            m_velocity.setY(1);
            cout << "DOWN" << endl;
        }

        if(InputHandler::Instance() ->getDpadLeft() && InputHandler::Instance() ->dpadStatus == 0)
        {
            m_velocity.setX(-1);
            cout << "LEFT" << endl;
        }

        if(InputHandler::Instance() ->getDpadRight() && InputHandler::Instance() ->dpadStatus == 0)
        {
            m_velocity.setX(1);
            cout << "RIGHT" << endl;
        }

        /*
        if(InputHandler::Instance() ->HatStatus[SDL_HAT_RIGHT])
        {
            m_velocity.setX(-1);
            cout << "RIGHT" << endl;
        }
        */
    }

     //***********KEYBOARD COONTROLS*****************//


    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_velocity.setX(1);
        m_currentRow = 4;
    }

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_velocity.setX(-1);
        m_currentRow = 2;

    }
    else
    {
        //player ->m_currentRow = 1;
    }

     //***********MOUSE COONTROLS*****************//

        /*
            MOUSE_BUTTON_LEFT   =   0
            MOUSE_BUTTON_MIDDLE =   1
            MOUSE_BUTTON_RIGHT  =   2
        */
        if(InputHandler::Instance() ->getMouserButtonState(0))
            cout << "MLEFT" << endl;

        if(InputHandler::Instance() ->getMouserButtonState(2))
            cout << "MRIGTH" << endl;

        if(InputHandler::Instance() ->getMouserButtonState(1))
            cout << "MMIDDLE" << endl;

     //   Vector2D* vec = InputHandler::Instance() ->getMousePosition();
     //   m_velocity = (*vec - m_position) /100;

}

void GL_Player::clean()
{
    GL_GameObject::clean();
}
