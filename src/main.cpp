/* 
 * File:   main.cpp
 * Author: jeansebtr
 *
 * Created on 8 février 2011, 17:20
 */

#include <stdlib.h>


#include <iostream>
#include <GL/glfw.h>

#include "Game.h"
#include "debug.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{

    dbg("Starting APP !");

    Game::Init(argv[1]);

    exit(EXIT_SUCCESS);
}

