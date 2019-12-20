#ifndef OBJ1_HPP
#define OBJ1_HPP

#include <stdlib.h>
#include "obj2.hpp"

static int   refCounter = 0;

class obj1
{
public:
    /** default ctor */
    obj1();
    
    /** dtor */
    ~obj1();

    /** do something */
    void work( char * calledBy );

protected:
    int          objNum;
    obj2        *pObj2;
    obj2        *pObj3;
};
#endif
