
#include <stdio.h>
#include "obj2.hpp"

obj2::obj2()
{
    refCounter2++;
    objNum = refCounter2;
    printf("obj2> creating %d/%d\n",objNum,refCounter2);
}

obj2::~obj2()
{
    printf("obj2> deleting %d/%d\n",objNum,refCounter2);
    refCounter2--;
}
