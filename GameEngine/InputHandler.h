#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Game.h"
#include "Vector2D.h"

using namespace std;

enum mouse_buttons
{
    M_LEFT    = 0,
    M_MIDDLE  = 1,
    M_RIGHT   = 2
};

enum dpad_buttons
{
    UP      = 1,
    DOWN    = 4,
    LEFT    = 2,
    RIGHT   = 8
};

class InputHandler
{
    public:

        //Singleton inputHandler
        static InputHandler* Instance();

        //Finds how many joysticks SDL has access to and the intializes them
        void intializeJoysticks();
        bool joysticksInitialized(){ return m_bJoysticksInitialized;}

        //poll for events and updates inputH
        void update();
        //cleans any devices that have been intialized
        void clean();

        //Grabs the values from the array of pairs
        int xvalues(int joy, int stick);
        int yvalues(int joy, int stick);

        const Uint8* currentKeyState;
        bool isKeyDown(SDL_Scancode key);
        bool isKeyUp(){return true;}

        //grab the current button state for the correct button
        //from the correct joystick
        //joy is joystickID and buttonNumber is button index
        bool getButtonState(int joy, int buttonNumber)
        {
            return m_buttonStates[joy] [buttonNumber];
        }

        //get mouse button states
        bool getMouserButtonState(int buttonNumber)
        {
            return m_mouseButtonStates[buttonNumber];
        }

        //resets mouse button states
        void reset()
        {
            m_mouseButtonStates[M_LEFT] = false;
            m_mouseButtonStates[M_RIGHT] = false;
            m_mouseButtonStates[M_MIDDLE] = false;
        }

        //get mouse position
        Vector2D* getMousePosition()
        {
            return m_mousePostion;
        }

        bool getDpadUp()
        {
            return dUp;
        }

        bool getDpadDown()
        {
            return dDown;
        }

        bool getDpadLeft()
        {
            return dLeft;
        }

        bool getDpadRight()
        {
            return dRight;
        }

        Uint8 getControllerPort()
        {
            return dpadStatus;
        }

        Uint8 dpadStatus;

		        ~InputHandler();

    private:
        InputHandler();

        static InputHandler* i_instance;

        //To control sensitivity of controller
        const int m_joystickDeadZone;

        std::vector<SDL_Joystick*> m_joysticks;

        //couples a pair of variables
        //To handle multiple controllers with multiple axes we will
        //create a vector of pairs of Vector2D* , one for each stick
        std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;
        bool m_bJoysticksInitialized;

        //array of buttonStates
        std::vector<std::vector<bool> > m_buttonStates;

        //array of dpadStates
        std::vector<std::vector<bool> > m_dpadStates;

        //array of mousebuttonStates
        std::vector<bool> m_mouseButtonStates;

        //map< Uint8, bool > HatStatus;
        bool dUp;
        bool dDown;
        bool dLeft;
        bool dRight;
        //m_keystate = SDL_GetKeyboardState(0);

        //Mouse position
        Vector2D* m_mousePostion;

        // handle keyboard events
        void onKeyDown();
        void onKeyUp();

        // handle mouse events
        void onMouseMove(SDL_Event& event);
        void onMouseButtonDown(SDL_Event& event);
        void onMouseButtonUp(SDL_Event& event);

        // handle joysticks events
        void onJoystickAxisMove(SDL_Event& event);
        void onJoystickButtonDown(SDL_Event& event);
        void onJoystickButtonUp(SDL_Event& event);
        void onJoystickDpad(SDL_Event& event);

        //SDL_Event event;
        //const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

};

#endif // INPUTHANDLER_H
