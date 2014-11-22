#include "GameOverState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
    for(unsigned int i = 0 ; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->update();
        //std::cout << "Pause updating" << endl;
    }
}

void GameOverState::render()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->draw();
    }
}

bool GameOverState::onEnter()
{
    GameObject* button1 = new MenuButton(s_gameOverToMain);
    GameObject* button2 = new MenuButton(s_restartPlay);

    if(!button1 ->load(new LoaderParams(200, 100, 200, 80, 0,
        "main.png", "mainMenuButton")))
        return false;

    if(!button2 ->load(new LoaderParams(200, 300, 200, 80, 0,
        "restart.png", "restartButton")))
        return false;

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    m_textureIDList.push_back("mainMenuButton");
    m_textureIDList.push_back("restartButton");

    std::cout << "entering GameOverState\n";

    std::cout << "GAMEOBJECTS: " << m_gameObjects.size() << ": before DELETE"<< std::endl;


    return true;
}

bool GameOverState::onExit()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] = NULL;
        //m_gameObjects[i] ->clean();
        m_gameObjects.erase(m_gameObjects.begin() + i);
        std::cout << "GAMEOVER GAMEOBJECTS: " << m_gameObjects.size() << ": after DELETE"<< std::endl;

        --i;
    }

    m_gameObjects.clear();
    //clear the texture manager
    for(unsigned int i = 0; i < m_textureIDList.size(); i++)
    {
        TextureManager::Instance() ->clearFromTextureMap(m_textureIDList[i]);
        std::cout << "GAMEOVER DELETING TEXTURES" << std::endl;

    }
    InputHandler::Instance() ->reset();

    std::cout << "exiting game over state" << endl;

    return true;
}

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new
    MenuState());
}

void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new
    PlayState());
}
