/* 
 * File:   Object.h
 * Author: jeansebtr
 *
 * Created on 9 février 2011, 22:55
 */

#include "coord.h"
#include "../graphics/VisualObj.h"

#ifndef _OBJECT_H
#define	_OBJECT_H

class Object
{
public:
    Object();
    Object(const Object& orig);
    virtual ~Object();

    uiCoord3 *coord;

    void Update(int rate);
    void AlterSpeed(uiVect3 accel);
private:
    VisualObj *graphics;
    uiVect3 speed;
    Angle3 rSpeed;
    uiVect3 accel;

};

#endif	/* _OBJECT_H */

