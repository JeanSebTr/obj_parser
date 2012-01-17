/* 
 * File:   Convert.cpp
 * Author: jeansebtr
 * 
 * Created on 14 février 2011, 21:44
 */

#include "Convert.h"
#include <sstream>
#include <stdio.h>

std::string Convert::itos(int i)
{
    std::ostringstream str;
    str << i;
    return str.str();
}

std::string Convert::dtos(double d)
{
    std::ostringstream str;
    str << d;
    return str.str();
}

std::string Convert::ptos(const void* p)
{
    char buf[10];
    sprintf(buf, "%p", p);
    return buf;
}
