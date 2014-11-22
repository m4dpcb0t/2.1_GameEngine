#ifndef GL_PLAYER_H
#define GL_PLAYER_H

#include "GL_GameObject.h"

class GL_Player : public GL_GameObject
{
    public:
        GL_Player();
        virtual ~GL_Player();
        virtual void draw();
        virtual void update();
        virtual void clean();
        virtual bool load(const LoaderParams* pParams);

    private:
        void handleInput();
		float* getVertex(){
			float *vertex;
			vertex[0] = this ->getPositon().getX();
			vertex[1] = this ->getPositon().getY();
			vertex[2] = vertex[0] + (this ->getWidth());
			vertex[3] = vertex[1] - (this ->getHeight());
			 
			return vertex;
		}
};

#endif // GL_PLAYER_H
