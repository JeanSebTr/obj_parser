#include "debug.h"
#include <stdio.h>


void dbg(std::string msg)
{
    std::cout << msg << std::endl;
}

/*void dbg(char* msg)
{
    printf("%s", msg);
}*/

void dbg_info()
{
    char * cwd;
    getcwd(cwd, 255);
    std::cout << cwd << std::endl;
}
