/* 
 * File:   debug.h
 * Author: jeansebtr
 *
 * Created on 14 février 2011, 00:52
 */

#include <iostream>
#include <string>
#include <dirent.h>
#include <stdlib.h>

#ifndef _DEBUG_H
#define	_DEBUG_H

void dbg(std::string msg);
//void dbg(char* msg);

void dbg_info();

#endif	/* _DEBUG_H */

