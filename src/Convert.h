/* 
 * File:   Convert.h
 * Author: jeansebtr
 *
 * Created on 14 février 2011, 21:44
 */


#include <string>


#ifndef _CONVERT_H
#define	_CONVERT_H

class Convert {
public:
    static std::string itos(int i);
    static std::string dtos(double d);
    static std::string ptos(const void* p);
private:
    Convert();

};

#endif	/* _CONVERT_H */

