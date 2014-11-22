#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include "Floating_Rectangle.h"
#include <stdio.h>
#include <string>

class Texture
{
    public:
        Texture();
        /*
        Pre Condition
        -None
        Post Condition
        -Intializes member variables
        Side Effecs
        -None
        */

        virtual ~Texture();
          /*
        Pre Condition
        -None
        Post Condition
        -Frees textures
        Side Effecs
        -None
        */

        bool loadTextureFromPixels32(GLuint* pixels, GLfloat width, GLfloat height);
          /*
        Pre Condition
        -A valid OpenGl Context
        Post Condition
        -Creates a texture fro m the given pixels
        -Reports error to console if texture could not be created
        Side Effecs
        -Binds a NULL texture
        */

        bool loadTextureFromFile(std::string str);
          /*
        Pre Condition
        -A valid OpenGl Context
        Post Condition
        -Creates a texture fro m the given file
        -Reports error to console if texture could not be created
        Side Effecs
        -Binds a NULL texture
        */

        void freeTexture();
          /*
        Pre Condition
        -A valid OpenGl context
        Post Condition
        -Deletes texture if it exists
        -Sets texture ID to 0
        Side Effecs
        -None
        */

        void render(GLfloat x, GLfloat y, Floating_Rectangle* clip = NULL);
          /*
        Pre Condition
        -A valid OpenGL context
        -Active modelview matrix
        Post Condition
        -Translates to given position and reders textured quad
        -If given texture clip is NULL, the full texture is rendered
        Side Effecs
        -Binds member texture ID
        */

        GLuint getTextureID() const { return m_TextureID; }
          /*
        Pre Condition
        -None
        Post Condition
        -Returns texture name/ID
        Side Effecs
        -None
        */

        GLfloat getTextureWidth() const { return m_TextureWidth;}
          /*
        Pre Condition
        -None
        Post Condition
        -Returns texture width
        Side Effecs
        -None
        */

        GLfloat getTextureHeight() const { return m_TextureHeight;}
          /*
        Pre Condition
        -None
        Post Condition
        -Returns texture height
        Side Effecs
        -None
        */

    private:
        //Texture name
        GLuint m_TextureID;

        //Texture Dimensions
        GLfloat m_TextureWidth;
        GLfloat m_TextureHeight;

};

#endif // TEXTURE_H
