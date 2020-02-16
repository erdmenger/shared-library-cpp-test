
#include "shared.h"
#include <stdlib.h>
#include <stdio.h>

#include "obj1.hpp"

static obj1 theObj1 = obj1();

/* ----------------------------------------------------------- */
int open( char *in, char **out ) {
    char *pOut = 0;

    printf( "-> open():");
    printf(" in = '%s'.\n",in);
    pOut = (char *)malloc( 20 * sizeof( char ) );
    sprintf(pOut, "String form lib");
    *out = pOut;
    return 0;
}
/* ----------------------------------------------------------- */
int work( char *data ) {
    printf("-> work(): data: %s\n",data);
//    theObj1.work( "int work( char *data )" );
    return 0;
}
/* ----------------------------------------------------------- */
int close( void ) {
    printf("-> close()\n");
    return 0;
}
/* ----------------------------------------------------------- */
void initLib (void) {
    printf("* initLib() *\n");
    return;
}
/* ----------------------------------------------------------- */
void closeLib (void)
{
    printf("* closeLib() *\n");
    return;
}

 /* at least on Linux these functions are in the C runtime lib */
#ifndef __linux

/* ----------------------------------------------------------- */
void _init (void) {
    printf("* _init() *\n");
    return;
}
/* ----------------------------------------------------------- */
void _fini (void)
{
    printf("* _fini() *\n");
    return;
}
#endif

/* ----------------------------------------------------------- */

#if defined (_WIN32)
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			printf(" DllMain called state >DLL_PROCESS_ATTACHED<\n");
		case DLL_THREAD_ATTACH:
			printf(" DllMain called state >DLL_THREAD_ATTACHED<\n");
		case DLL_THREAD_DETACH:
			printf(" DllMain called state >DLL_THREAD_DETTACHED<\n");
		case DLL_PROCESS_DETACH:
			printf(" DllMain called state >DLL_PROCESS_DETTACHED<\n");
			break;
    }
    return TRUE;
}
#endif
