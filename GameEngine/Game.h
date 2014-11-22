#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <stdio.h>
#include <string>

#include "InputHandler.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Floating_Rectangle.h"
#include "TextureManager.h"
#include "GL_Player.h"
#include "GameStateMachine.h"

//Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

//Viewports
enum ViewPortMode
{
    VIEWPORT_MODE_FULL,
    VIEWPORT_MODE_HALF_CENTRE,
    VIEWPORT_MODE_HALF_TOP,
    VIEWPORT_MODE_QUAD,
    VIEWPORT_MODE_RADAR
};

class Game {

public:
	~Game();
	static Game* Instance();

	//Starts up SDL, create window, and intialized OpenGL
	bool init();

	//Initalizes matrices and clear color
	bool initGL();
    /*
    Pre Condition:
        - A valid OpenGL context
    Post Condition:
        - Initalizes matices and clear color
        - Reports to console if there was an OpenGL error
        - Returns false if there was an error in initalization
    Side Effects:
        -Projection matrix is set to an orthgraphic matrix
        -Modelview matrix is set to modelview
        -Clear color is set to black
    */

    bool loadMedia();
    /*
    Pre Condition:
        - None
    Post Condition:
        - Loads media in to texture object
    Side Effects:
        -Projection matrix is set to an orthgraphic matrix
        -Modelview matrix is set to modelview
        -Clear color is set to black
    */

	void handleEvents(void);
	/*
	Pre Condition:
        -None
    Post Condition:
        -Toggles the color mode when the user press q
        -Cycles through different projection scales when the user presse e
    Side Effects:
        -If the user press e, the matrix mode is set to projection
	*/

	void render(void);
	/*
    Pre Condition
        -A valid OpenGL context
        -Active modelview matrix
    Post Condition
        -Renders the screen
    Side Effects
        -Clears the color buffer
        -Swaps the front/back buffer
        -Sets matrix mode to modelview
        -Translates modelviw matrix to the center of the default screen
        -Changes the current redering color
	*/
	void clean(void);
	void update(void);
	/*
    Pre Condition:
        -None
    Post Condition:
        -Does per frame logic
    Side Effects
        -None
	*/



	bool running() {return m_bRunning;}

	void exit(void){m_bRunning = false;}

	SDL_Window* getWindow() const { return g_pWindow;}

    GameStateMachine* getStateMachine() {return m_pGameStateMachine;}

private:

	//Pointer to window function to create window
	SDL_Window* g_pWindow;

	//OpenGL context
	SDL_GLContext g_Context;

	bool g_RenderQuad;
	bool m_bRunning;
	float x, y;

	//The projection scale controls how large of a coordinate area we want to render
    GLfloat g_ProjectionScale;

	//Must be accesed using instance
	Game();
	static Game* g_instance;

	//Game states
    GameStateMachine* m_pGameStateMachine;

};
#endif 