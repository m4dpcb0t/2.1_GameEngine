#include "GameStateMachine.h"

//Push the passed-in pState parameter into
//the m_gameStates array and then call its
//onEnter function
void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back() ->onEnter();
}

//Check if any states is available to remove
//Call onExit function of the current state
//remove state

void GameStateMachine::popState()
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back() ->onExit())
        {
            m_gameStates.back() = NULL;
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}
//Check if any states are in array
//Check if their ID is the same as the current one
//Do nothing if ID is the same
//If state do not match remove current state
//Add our new pState and call onEnter()

void GameStateMachine::changeState(GameState* pState)
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back() ->getStateID() == pState ->getStateID())
            {
                std::cout << "Your are trying to change to the same state moron" << std::endl;
                return;
            }

        if(m_gameStates.back() ->onExit())
        {
            for(unsigned int i = 0; i < m_gameStates.size(); i++)
            {
                std::cout << m_gameStates.size() << ": before DELETE"<< std::endl;
                std::cout << m_gameStates[i] << ": GAMESTATE" << std::endl;
                m_gameStates[i] = NULL;
                std::cout << m_gameStates[i] << ": NULL" << std::endl;
                m_gameStates.erase(m_gameStates.begin() + i);
                std::cout << m_gameStates.size() << ": after DELETE"<< std::endl;

                i--;
            }
        }
    }

    //push back our new state
    m_gameStates.push_back(pState);
//    std::cout << "Adding new state" << endl;

    //initalize it
    m_gameStates.back() ->onEnter();
  //  std::cout << "Entering new state" << endl;
}

void GameStateMachine::update()
{
    if(!m_gameStates.empty())
        m_gameStates.back() ->update();
}

void GameStateMachine::render()
{
    if(!m_gameStates.empty())
        m_gameStates.back() ->render();
}

void GameStateMachine::clean()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();

        delete m_gameStates.back();

        m_gameStates.clear();
    }

}

