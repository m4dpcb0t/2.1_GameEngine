#include "PauseState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
    for(unsigned int i = 0 ; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->update();
        //std::cout << "Pause updating" << endl;
    }
}

void PauseState::render()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->draw();
    }
}

bool PauseState::onEnter()
{
    GameObject* button1 = new MenuButton(s_resumeToPlay);
    GameObject* button2 = new MenuButton(s_pauseToMain);

    if(!button1 ->load(new LoaderParams(200, 100, 200, 80, 0,
        "resume.png", "resumeButton")))
        return false;

    if(!button2 ->load(new LoaderParams(200, 300, 200, 80, 0,
        "main.png", "mainMenuButton")))
        return false;

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    m_textureIDList.push_back("resumeButton");
    m_textureIDList.push_back("mainMenuButton");

    std::cout << "entering pause menu\n";

    std::cout << "GAMEOBJECTS: " << m_gameObjects.size() << ": before DELETE"<< std::endl;


    return true;
}

bool PauseState::onExit()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] = NULL;
        m_gameObjects.erase(m_gameObjects.begin() + i);
        std::cout << "PAUSE GAMEOBJECTS: " << m_gameObjects.size() << ": after DELETE"<< std::endl;

    --i;
    }

    m_gameObjects.clear();
    //clear the texture manager
    for(unsigned int i = 0; i < m_textureIDList.size(); i++)
    {
        TextureManager::Instance() ->clearFromTextureMap(m_textureIDList[i]);
        std::cout << "PAUSE DELETING TEXTURES" << std::endl;

    }

    InputHandler::Instance() ->reset();

    std::cout << "exiting pause state" << endl;

    return true;
}

void PauseState::s_pauseToMain()
{
    Game::Instance() ->getStateMachine() ->changeState(new MenuState());
}

void PauseState::s_resumeToPlay()
{
    Game::Instance() ->getStateMachine() ->popState();
}
