#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <stdio.h>
#include <map>

#include "Texture.h"
#include "Floating_Rectangle.h"

class TextureManager
{
    public:
        static TextureManager* Instance();
        virtual ~TextureManager();

        bool loadMedia(const char*, const char*);
        void draw(float, float, float, float, float, float, const char*);
        void drawFrame(float, float, float, float, float, float, int, int, const char*);
        void cleanTextures();
        void clearFromTextureMap(std::string);

    protected:
    private:
        TextureManager();
        static TextureManager* t_instance;
        Texture* loadedTexture;
        Floating_Rectangle *destRect;
        Floating_Rectangle srcRect;

        std::map<std::string, Texture*> m_textureMap;
};

#endif // TEXTUREMANAGER_H
