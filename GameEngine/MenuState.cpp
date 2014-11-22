#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "Game.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->update();
    }
}

void MenuState::render()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->draw();
    }
}

bool MenuState::onEnter()
{
    GameObject* button1 = new MenuButton(s_menuToPlay);
    GameObject* button2 = new MenuButton(s_exitFromMenu);

    if(!button1 ->load(new LoaderParams(100, 100, 400, 100, 0,
        "button.png", "playButton")))
        return false;

    if(!button2 ->load(new LoaderParams(100, 300, 400, 100, 0,
        "exit.png", "exitButton")))
        return false;


    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    m_textureIDList.push_back("playButton");
    m_textureIDList.push_back("exitButton");

    std::cout << "GAMEOBJECTS: " << m_gameObjects.size() << ": before DELETE"<< std::endl;


    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] = NULL;
        m_gameObjects.erase(m_gameObjects.begin() + i);
        std::cout << "MENUSTATE GAMEOBJECTS: " << m_gameObjects.size() << " after DELETE"<< std::endl;

    --i;
    }
    m_gameObjects.clear();

    //clear the texture manager
    for(unsigned int i = 0; i < m_textureIDList.size(); i++)
    {
        TextureManager::Instance() ->clearFromTextureMap(m_textureIDList[i]);
        std::cout << "MENUSTATE DELETING TEXTURES" << std::endl;
    }


    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay()
{
    std::cout << "Play button clicked\n";
    Game::Instance() ->getStateMachine() ->changeState(new PlayState());
    //currentState = false;
}

void MenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked\n";
    Game::Instance() ->exit();
}

