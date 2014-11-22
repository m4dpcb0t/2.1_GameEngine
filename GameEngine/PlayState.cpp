#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GL_Player.h"
#include "InputHandler.h"
#include "Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{

	if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_P))
    {
		Game::Instance() ->getStateMachine() ->pushState(new PauseState);
    }

    if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_G))
    {
        Game::Instance() ->getStateMachine() ->pushState(new GameOverState);
    }


    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->update();
    }
}

void PlayState::render()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] ->draw();
    }
}

bool PlayState::onEnter()
{
    GameObject* player = new GL_Player();

    if(!player ->load(new LoaderParams(50.0f, 250.0f, 32.0f, 64.0f, 
						1,"player.png", "player")))
        return false;

    m_gameObjects.push_back(player);
    m_textureIDList.push_back("player");

    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::onExit()
{
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] = NULL;
        m_gameObjects.erase(m_gameObjects.begin() + i);
        std::cout << "PLAYER GAMEOBJECTS: " << m_gameObjects.size() << ": after DELETE"<< std::endl;
    --i;
    }
    m_gameObjects.clear();

    for(unsigned int i = 0; i < m_textureIDList.size(); i++)
    {
        TextureManager::Instance() ->clearFromTextureMap(m_textureIDList[i]);
        std::cout << "DELETING TEXTURES PLAYER" << std::endl;

    }

    std::cout << "exiting PlayState\n";
    return true;

}
