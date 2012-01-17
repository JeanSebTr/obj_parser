/* 
 * File:   Game.cpp
 * Author: jeansebtr
 * 
 * Created on 9 février 2011, 17:37
 */

#include <stdlib.h>
#include <iostream>

#include "Game.h"
#include "graphics/ModelLoader.h"
#include "debug.h"
#include "Convert.h"
#include "objlib.h"

#include <unistd.h>

Game::Game() {
}

Game::Game(const Game& orig) {
}

Game::~Game() {
}
double angleZ = 0;
double angleX = 0;

/*
static void Game::drawThread()
{
    
}

static void GLFWCALL Game::logicThread(void * arg)
{

}

static void GLFWCALL Game::soundThread(void * arg)
{

}

static void GLFWCALL Game::networkThread(void * arg)
{
    
}
*/
void Game::Init(char* file)
{
   // dbg_info();

    int running = GL_TRUE;
    // Initialize GLFW
    if( !glfwInit() )
    {
        dbg("Crash :(");
        exit( EXIT_FAILURE );
    }
    // Open an OpenGL window
    if( !glfwOpenWindow( 600,600, 0,0,0,0,0,0, GLFW_WINDOW ) )
    {
        dbg("Crash :(");
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

/* frame buffer clears should be to black */
glClearColor(0.0, 0.0, 0.0, 0.0);
/* pedantic, full window size is default viewport */
glViewport(0, 0, 600, 600);
std::cout << "Loading model " << file << std::endl;
int id = ModelLoader::Load(file);
    std::cout << "Model loaded with ID " << Convert::itos(id) << std::endl;
    ModelLoader::Render(id);
    //MeshObj* obj = new MeshObj("./cygnus/Cygnus.obj");
    running = GL_TRUE;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(70,1,1,1000);
    // Main loop
    glEnable(GL_DEPTH_TEST);
    double last_time = glfwGetTime();
    double current_time, ellapsed_time, lastsec = last_time;
    int fps = 0;
    float axis[2];
    while( running )
    {
        // OpenGL rendering goes here...
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity( );

gluLookAt(200,200,200,0,0,0,0,0,1);
glRotated(angleZ,0,0,1);
glRotated(angleX,1,0,0);

current_time = glfwGetTime();
ellapsed_time = current_time - last_time;
last_time = current_time;
glfwGetJoystickPos( GLFW_JOYSTICK_1, axis, 2 );
angleZ += axis[0] * 50 * ellapsed_time;
angleX += axis[1] * 50 * ellapsed_time;
if(angleZ > 360)
    angleZ -= 360;
if(angleZ < 0)
    angleZ += 360;
if(angleX > 360)
    angleX -= 360;
if(angleX < 0)
    angleX += 360;
if(current_time > lastsec + 1)
{
    dbg("Frame rate : "+Convert::itos(fps)+" fps");
    fps = 0;
    lastsec = current_time;
}
else
    fps++;
//obj->draw_model(false, false);
ModelLoader::Render(id);
glFlush();
        
        // Swap front and back rendering buffers
        glfwSwapBuffers();
        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
        glfwGetWindowParam( GLFW_OPENED );
    }
    
    
    glfwTerminate();
    exit( EXIT_SUCCESS );
}
