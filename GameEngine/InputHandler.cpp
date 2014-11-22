#include "InputHandler.h"

InputHandler* InputHandler::i_instance = NULL;

//Instance can call the constructor only
InputHandler* InputHandler::Instance()
{
    if(!i_instance)
        i_instance = new InputHandler;
    return i_instance;
}

InputHandler::InputHandler() : m_joystickDeadZone(10000), currentKeyState(0),
							   m_bJoysticksInitialized(false), m_mousePostion(new Vector2D(0, 0))
{
    //ctor

    for(int i = 0; i < 3; i++)
        m_mouseButtonStates.push_back(false);
	currentKeyState = SDL_GetKeyboardState(NULL);
	dUp = false;
	dDown = false;
	dLeft = false;
	dRight = false;
}

InputHandler::~InputHandler()
{
    //dtor
}

void InputHandler::intializeJoysticks()
{
    //Check if subsystem has been initialized//

    //If not intialized intialize it
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    //Opening each available joystick//

    //pushed into our array for closing later
    if(SDL_NumJoysticks() > 0)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);

            if(SDL_JoystickOpen(i))
            {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new
                Vector2D(0, 0), new Vector2D(0, 0))); //add our pair

                std::vector<bool> tempButtons;
                //get the number of buttons for each of our joystick
                //push each button to array and set to false as nothing is pressed
                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                    tempButtons.push_back(false);
                //push the array to m_buttonStates to be used with
                //getButtonState()
                m_buttonStates.push_back(tempButtons);
            }
        }

        //Tell SDL to start listening for joystick events
        //By enabling SDL_JoystickEventState
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialized = true;

        std::cout << "Initialised " << m_joysticks.size()
        << "joysticks" << endl;
    }
    else
        m_bJoysticksInitialized = false;
}

//Gets called for each frame in the main game loop
void InputHandler::update()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        //Check the axis the event came from
        int whichOne = event.jaxis.which;
        switch (event.type)
        {
        case SDL_QUIT:
            Game::Instance() ->clean();
        break;
        //Check for an SDL_JOY... if exist
        case SDL_JOYAXISMOTION:
            onJoystickAxisMove(event);
        break;

        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
        break;

        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
        break;

        case SDL_JOYHATMOTION:
            onJoystickDpad(event);
        break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
        break;

        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
        break;

        case SDL_MOUSEMOTION:
            onMouseMove(event);
        break;

        case SDL_MOUSEWHEEL:
            cout << event.wheel.y << endl;
        break;

        default:
            break;
        }
    }
}

//Loops through all SDL_Joystick pointers and calls SDL_JoystickClose
void InputHandler::clean()
{
    if(m_bJoysticksInitialized)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
            SDL_JoystickClose(m_joysticks[i]);
    }
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(currentKeyState != 0)
    {
		Uint32 buttonPress = SDL_GetTicks();

        if(currentKeyState[key] == 1)
        {
            return true;
        }
		else
			currentKeyState = SDL_GetKeyboardState(NULL);
    
    }
    return false;
}

//joy parameter is the identifier(ID) of the joystick
//stick parameter is 1 for left and 2 is for the right
int InputHandler::xvalues(int joy, int stick)
{
    if(m_joystickValues.size() > 0)
    {
        if(stick == 1)
            return static_cast<int> (m_joystickValues[joy].first ->getX());
        else if(stick == 2)
            return static_cast<int> (m_joystickValues[joy].second ->getX());
    }
    return 0;
}

int InputHandler::yvalues(int joy, int stick)
{
    if(m_joystickValues.size() > 0)
    {
        if(stick == 1)
            return m_joystickValues[joy].first ->getY();
        else if(stick == 2)
            return m_joystickValues[joy].second ->getY();
    }
    return 0;
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
    //Check the axis the event came from
    int whichOne = event.jaxis.which;
    //Find out which controller the event came from
    //If 0 or 1 it is the left stick
    //If 3 or 4 it is the right stick
    // left stick move left or right
    if(event.jaxis.axis == 0)
    {
        if(event.jaxis.value > m_joystickDeadZone)
            m_joystickValues[whichOne].first ->setX(1);
        else if (event.jaxis.value < -m_joystickDeadZone)
            m_joystickValues[whichOne].first ->setX(-1);
        else
            m_joystickValues[whichOne].first ->setX(0);
    }
    //left stick move up or down
    if(event.jaxis.axis == 1)
    {
        if(event.jaxis.value > m_joystickDeadZone)
            m_joystickValues[whichOne].first ->setY(1);
        else if(event.jaxis.value < -m_joystickDeadZone)
            m_joystickValues[whichOne].first ->setY(-1);
        else
            m_joystickValues[whichOne].first ->setY(0);
    }
    //right stick move left or right
    if(event.jaxis.axis == 3)
    {
        if(event.jaxis.value > m_joystickDeadZone)
            m_joystickValues[whichOne].second ->setX(1);
        else if(event.jaxis.value < -m_joystickDeadZone)
            m_joystickValues[whichOne].second ->setX(-1);
        else
            m_joystickValues[whichOne].second ->setX(0);
    }
    //right stick move up or down
    if(event.jaxis.axis == 4)
    {
        if(event.jaxis.value > m_joystickDeadZone)
            m_joystickValues[whichOne].second ->setY(1);
        else if(event.jaxis.value < -m_joystickDeadZone)
            m_joystickValues[whichOne].second ->setY(-1);
        else
            m_joystickValues[whichOne].second ->setY(0);
    }
    //Left Trigger
    //-32768 : 32767
    if(event.jaxis.axis == 2)
    {
        std::cout << event.jaxis.value << endl;
    }

    //Right Trigger
    if(event.jaxis.axis == 5)
    {
        std::cout << event.jaxis.value << endl;
    }

}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = false;
}

void InputHandler::onJoystickDpad(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    dpadStatus = whichOne;
    /*
    HatStatus[SDL_HAT_UP] = (true == event.jhat.value & SDL_HAT_UP);
    HatStatus[SDL_HAT_DOWN] = (true == event.jhat.value & SDL_HAT_DOWN);
    HatStatus[SDL_HAT_LEFT] = (true == event.jhat.value & SDL_HAT_LEFT);
    HatStatus[SDL_HAT_RIGHT] = (true == event.jhat.value & SDL_HAT_RIGHT);
    */
    if(event.jhat.value == SDL_HAT_CENTERED){
        dUp = false;
        dDown = false;
        dLeft = false;
        dRight = false;
    }

    if(event.jhat.value == SDL_HAT_UP){
        dUp = true;
    }
    if(event.jhat.value == SDL_HAT_DOWN){
        dDown = true;
    }
    if(event.jhat.value == SDL_HAT_LEFT){
        dLeft = true;
    }
    if(event.jhat.value == SDL_HAT_RIGHT){
        dRight = true;
    }

}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
        m_mouseButtonStates[M_LEFT] = true;
    if(event.button.button == SDL_BUTTON_MIDDLE)
        m_mouseButtonStates[M_MIDDLE] = true;
    if(event.button.button == SDL_BUTTON_RIGHT)
        m_mouseButtonStates[M_RIGHT] = true;
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
        m_mouseButtonStates[M_LEFT] = false;
    if(event.button.button == SDL_BUTTON_MIDDLE)
        m_mouseButtonStates[M_MIDDLE] = false;
    if(event.button.button == SDL_BUTTON_RIGHT)
        m_mouseButtonStates[M_RIGHT] = false;
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePostion = new Vector2D(0.0f, 0.0f);
    m_mousePostion ->setX( static_cast <float>(event.motion.x));
    m_mousePostion ->setY( static_cast <float>(event.motion.y));
}

