#include "Texture.h"
#include <IL\il.h>
#include <IL\ilu.h>

Texture::Texture()
{
    //ctor
    m_TextureID = 0;
    m_TextureWidth = 0;
    m_TextureHeight = 0;
}

Texture::~Texture()
{
    //dtor
    freeTexture();
    printf("TEXTURES CLEANED\n");
}

bool Texture::loadTextureFromPixels32(GLuint* pixels, GLfloat width, GLfloat height)
{
    //Free texture if it exists
    freeTexture();

    //Get tuxture dimensions
    m_TextureWidth = width;
    m_TextureHeight = height;

    //Generate texture ID put it in m_TextureID
    glGenTextures(1, &m_TextureID);

    //Bind texture ID
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    //Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    /*
    With glTexImage2D(), we assign pixels to our texture ID to generate the texture.

    What the function arguments mean from left to right:

    GL_TEXTURE_2D - texture target or the type of texture we're assigning the pixels to
    0 - the mipmap level. Don't worry about this for now
    GL_RGBA - the pixel format of how the texture is stored. OpenGL takes this as a suggestion, not an order
    width - texture width
    height - texture height
    0 - texture border width
    GL_RGBA - the format of the pixel data you're assigning
    GL_UNSIGNED_BYTE - the data type for the pixel data you're assigning
    pixels - the pointer address of the pixel data you're assigning


    After this call to glTexImage2D(), our pixel data should now be sitting comfortably in the GPU.

    */
    //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //Unbind textures
    glBindTexture(GL_TEXTURE_2D, NULL);

    //Check for errors
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
//        printf("Error loading texture from %p pixels!", pixels, gluErrorString(error));
        return false;
    }

    return true;
}

bool Texture::loadTextureFromFile(std::string str)
{
    //Texture loading sucess
    bool loadedTexture = false;

    //Generate and set current image ID
	ILuint imgID = 0;
    ilGenImages(1, &imgID);
    ilBindImage(imgID);

    //Load image
    ILboolean success = ilLoadImage(str.c_str());

    //Image loaded
    if(success == IL_TRUE)
    {
        //Convert imgae to RGBA
        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        if(success == IL_TRUE)
        {
            //Create texture from pixels
            loadedTexture = loadTextureFromPixels32((GLuint*)ilGetData(),
                (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
        }

        //Delete from devil memory
        ilDeleteImages(1, &imgID);
    }

    //Check for error
    if(!loadedTexture)
        printf("Unable to load texture");

    return loadedTexture;
}

void Texture::render(GLfloat x, GLfloat y, Floating_Rectangle* clip)
{
    //If the texture exists
    if(m_TextureID != 0)
    {
        //Remove any previous transformations
        glPopMatrix();
        //glLoadIdentity();
        glPushMatrix();


        //Texture coordinates
        GLfloat texTop = 0.0f;
        GLfloat texBottom = 1.0f;
        GLfloat texLeft = 0.0f;
        GLfloat texRight = 1.0f;

        //Vertex coordinates
        GLfloat quadHeight = m_TextureHeight;
        GLfloat quadWidth = m_TextureWidth;

        //Handle Clipping
        if(clip != NULL)
        {
            //Texture Coordinates
            texLeft = clip->x / m_TextureWidth;
            texRight = (clip->x + clip->w) / m_TextureWidth;
            texTop = clip->y / m_TextureHeight;
            texBottom = (clip->y + clip->h) / m_TextureHeight;

            //Vertex coordinates
            quadWidth = clip->w;
            quadHeight = clip->h;
        }

        //Move to rendering point
        glTranslatef(x, y, 0.0f);

        //Set texture ID
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        //Render textured Quad
         glBegin( GL_QUADS );
            glTexCoord2f( texLeft, texTop); glVertex2f( 0.f, 0.f );
            glTexCoord2f( texRight, texTop); glVertex2f( quadWidth, 0.f );
            glTexCoord2f( texRight, texBottom); glVertex2f( quadWidth, quadHeight);
            glTexCoord2f( texLeft, texBottom); glVertex2f( 0.f, quadHeight );
        glEnd();

    }
}

void Texture::freeTexture()
{
    //Delete Texture
    if(m_TextureID != 0)
    {
        glDeleteTextures(1, &m_TextureID);
        m_TextureID = 0;
    }

    m_TextureWidth = 0;
    m_TextureHeight = 0;
}
