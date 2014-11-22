#include "Game.h"

#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "PlayState.h"
#include <IL\il.h>
#include <IL\ilu.h>		

using namespace std;
Game* Game::g_instance = NULL;

//Viewport mode
int gViewportMode = VIEWPORT_MODE_FULL;

//Camera Position
GLfloat gCameraX = 0.0f;
GLfloat gCameraY = 0.0f;
GLfloat gCameraZ = 0.0f;

//Counter
int g_counter = 0;
float x = 0.0f;

//GameObjects
GL_Player* player;

//Temp
float xpos;

//Instance can call the constructor only
Game* Game::Instance()
{
	if(!g_instance)
		g_instance = new Game;
	return g_instance;
}

Game::Game(){

	    GLfloat g_ProjectionScale = 1.f;
}
Game::~Game(){}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initalize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}else{

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Set Double Buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//Create window
		g_pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if(g_pWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create context
			g_Context = SDL_GL_CreateContext(g_pWindow);
			if(g_Context == NULL)
			{
				printf("OpenGl context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Use Vsync
				if(SDL_GL_SetSwapInterval(1) < 0)
					printf("Warning: Unable to set Vsync! SDL Error: %s\n", SDL_GetError());

				//Initialize OpenGL
				if(!initGL())
				{
					printf("Unable to initialize OpenGL\n");
					success = false;
				}
			}
		}
	}

	m_bRunning = true;


    //GAMESTATE
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine ->changeState(new MenuState());


	return success;
}

bool Game::initGL(void)
{
    //Set the viewport
    glViewport(0.0f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initalize Projection Matrix
	//Projection Matrix controls how perspective work in OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initalize Modelview Matrix
	//Modelview Matrix controls how your rendered objects are viewed and placed
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Save the default modelview matrix
	glPushMatrix();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );


     //Enable texturing
     glEnable(GL_TEXTURE_2D);

	//Check for error
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Errror initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}


	//Intialize DevIL
	ilInit();
	ilClearColor(255, 255, 255, 0);

	ILenum iLError = ilGetError();
	if(iLError != IL_NO_ERROR)
    {
        printf("Error intializing DevIL! \n", iluErrorString( iLError ));
        return false;
    }

	return true;
}

void Game::handleEvents(void)
{
	InputHandler::Instance() ->update();

    //Quit Game
    if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        m_bRunning = false;
     //   keypressed = true;
    }

	if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_W))
	{
        gCameraY += 0.5f;
        y += 1.5f;
    //    keypressed = true;
    }
	if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_S))
	{
        gCameraY -= 0.5f;
        y -= 1.5f;
    //    keypressed = true;
    }
	if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_D))
    {
        gCameraX += 0.5f;
        x += 1.5f;
    //    keypressed = true;
    }
	if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_A))
    {
        gCameraX -= 0.5f;
        x -= 1.5f;
    //    keypressed = true;
    }

   
    if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_O))
    {
        gCameraZ -= 0.1f;
        x -= 1.5f;
     //   keypressed = true;
    }

    if(InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_V))
    {
        //Cycle through the viewport modes
        gViewportMode++;
    //    keypressed = true;
        if(gViewportMode > VIEWPORT_MODE_RADAR)
        {
            //Set back to full
            gViewportMode = VIEWPORT_MODE_FULL;
        }
    }


    //Take the saved matrix off the stack and reset it
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glLoadIdentity();


    glTranslatef(gCameraX, gCameraY, gCameraZ);

    //Save default matix again with camera translation
    glPushMatrix();
}

void Game::update(void){
    
	m_pGameStateMachine ->update();

}

void Game::render(void)
{
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Pop default matrix mode onto current matrix
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    //Save default matrix
    glPushMatrix();

    m_pGameStateMachine ->render();
}

void Game::clean(void)
{
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = NULL;
    printf("CLEANING GAME...\n");
    m_pGameStateMachine ->clean();

    m_pGameStateMachine = 0;
    delete m_pGameStateMachine;

    InputHandler::Instance() ->~InputHandler();
    TextureManager::Instance() ->~TextureManager();


    printf("GAME CLEANED\nNOW EXITING");
	//Quit SDL subsytems
	SDL_Quit();
}
