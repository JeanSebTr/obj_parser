/* 
 * File:   Game.h
 * Author: jeansebtr
 *
 * Created on 9 février 2011, 17:37
 */


#include <GL/glfw.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
	#ifdef _WIN32
	  #include <windows.h>
	#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "logic/Object.h"
#include "graphics/VisualObj.h"

#ifndef _GAME_H
#define	_GAME_H

class Game {
public:
    static void Init(char* file);
    static void GLFWCALL soundThread(void *arg);
    static void GLFWCALL logicThread(void *arg);
    static void drawThread();
    static void GLFWCALL networkThread(void *arg);

private:
    Game();
    Game(const Game &orig);
    virtual ~Game();

    static GLFWthread tSound;
    static GLFWmutex mSound;

    static GLFWthread tNetwork;
    static GLFWmutex mNetwork;

    static GLFWthread tLogic;
    static GLFWmutex mLogic;

    static GLFWmutex mDraw;
};

#endif	/* _GAME_H */

