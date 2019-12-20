#include <stdlib.h>
#include <stdio.h>

#include "obj1.hpp"

obj1::obj1() 
{
        refCounter++;
        objNum = refCounter;
        printf("obj1> creating %d/%d\n",objNum,refCounter);
        pObj2 = new obj2();
        pObj3 = new obj2();
}
    
obj1::~obj1() 
{
    printf("obj1> deleting %d/%d\n",objNum,refCounter);
    delete pObj2;
    refCounter--;
}

void 
obj1::work( char * calledBy )
{
    printf("obj1 (%d/%d)> I am calledBy '%s'.\n",objNum,refCounter,calledBy);
}
