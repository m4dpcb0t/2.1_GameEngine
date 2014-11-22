#include "TextureManager.h"


TextureManager* TextureManager::t_instance = NULL;

TextureManager* TextureManager::Instance()
{
    if(!t_instance)
    {
        t_instance = new TextureManager();
    }
    return t_instance;
}


TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
    printf("TEXTUREMANAGER CLEANING...\n");
    cleanTextures();
    printf("TEXTUREMANAGER CLEANED...\n");

}

bool TextureManager::loadMedia(const char* fileName, const char* ID)
{
    loadedTexture = new Texture();

    if(!loadedTexture ->loadTextureFromFile(fileName))
    {
        printf("Unable to load Texture from file.\n");
        return false;
    }
    else{
        m_textureMap[ID] = loadedTexture;
    }

    return true;

}

void TextureManager::draw(float xPos, float yPos,
                          float xRect, float yRect,
                          float wRect, float hRect,
                          const char* textureID)
{
    srcRect.x = xRect;
    srcRect.y = yRect;
    srcRect.w = wRect;
    srcRect.h = hRect;


    Texture* currentTexture;

    currentTexture = m_textureMap[textureID];

    if(currentTexture == NULL)
        printf("Failed to load image\n");

    currentTexture ->render(xPos, yPos, &srcRect);

}

void TextureManager::drawFrame(float xPos, float yPos,
                               float xRect, float yRect,
                               float wRect, float hRect,
                               int currentRow, int currentFrame,
                               const char* textureID)
{
    srcRect.x = wRect * currentFrame;
    srcRect.y = hRect * (currentRow -1);
    srcRect.w = wRect;
    srcRect.h = hRect;


    Texture* currentTexture;

    currentTexture = m_textureMap[textureID];

    destRect = new Floating_Rectangle();

    destRect = &srcRect;

    if(currentTexture == NULL)
        printf("Failed to load image\n");

    currentTexture ->render(xPos, yPos, destRect);

}

void TextureManager::cleanTextures()
{
    //Free loaded image
    delete loadedTexture;
    loadedTexture = NULL;
    destRect = NULL;
}

void TextureManager::clearFromTextureMap(std::string ID)
{
    m_textureMap.erase(ID);
}
