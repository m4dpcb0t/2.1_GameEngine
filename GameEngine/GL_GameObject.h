#ifndef GL_GAMEOBJECT_H
#define GL_GAMEOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"

//This class contains reusable functions
class GL_GameObject : public GameObject
{
    public:

        GL_GameObject();
        virtual ~GL_GameObject();
        virtual void draw();
        virtual void update();
        virtual void clean();
        virtual bool load(const LoaderParams* pParams);

        float getWidth() const { return m_width; }
        float getHeight() const { return m_height; }

        void setWidth(float x) { m_width = x; }
        void setHeight(float y) { m_height = y; }

        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;
        int m_currentRow;


        Vector2D& getPositon() {return m_position;}


    protected:


        float m_width;
        float m_height;
        int m_currentFrame;
        int m_numFrames;
        int m_callbackID;
        int m_animSpeed;
        char* m_fileName;
        char* m_fileID;
    private:


};

#endif // GL_GAMEOBJECT_H
