#include "GL_GameObject.h"
#include "TextureManager.h"

GL_GameObject::GL_GameObject() : GameObject()
{
    //ctor
}

GL_GameObject::~GL_GameObject()
{
    //dtor
}

bool GL_GameObject::load(const LoaderParams* pParams)
{ 
    m_position = Vector2D(pParams ->getX(), pParams ->getY());
    m_velocity = Vector2D(0, 0);
    m_acceleration = Vector2D(0 , 0);
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_fileName = pParams ->getFileName();
    m_fileID = pParams ->getFileID();
    m_currentFrame = pParams ->getNumFrames();
    m_animSpeed = 0;
    m_callbackID = 0;
    m_currentRow = pParams ->getCurrentRow();

    TextureManager::Instance() ->loadMedia(m_fileName ,m_fileID);

    return true;
}

void GL_GameObject::draw()
{

    TextureManager::Instance() ->drawFrame( m_position.getX(), m_position.getY(), 0,
                                           0, m_width, m_height,
                                           m_currentRow, m_currentFrame, m_fileID);
}

void GL_GameObject::update()
{

    //Basic movement
    m_velocity += m_acceleration;
    m_position += m_velocity;

}

void GL_GameObject::clean()
{}
