#ifndef OBJ2_HPP
#define OBJ2_HPP

#include <stdlib.h>

static int refCounter2 = 0;

class obj2
{
public:
    /** ctor */
    obj2();

    /** dtor */
    ~obj2();

protected:
    /** used to hold the number of the object */
    int objNum;
};
#endif
