#ifndef SHARED_H
#define SHARED_H 1

#if defined (_WIN32) /* Only Win32 needs special treatment. */
#    define Export_Flag __declspec(dllexport)
#    define Import_Flag __declspec (dllimport)
#    include <windows.h>
#else
#  define Export_Flag
#  define Import_Flag
#endif /* no _win32 */

#if defined (__GNUG__)
#    define LIB_INIT __attribute__ ((__constructor__))
#    define LIB_FINI __attribute__ ((__destructor__))
#else
#    define LIB_INIT
#    define LIB_FINI
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    Export_Flag int open( char *in, char **out );
    Export_Flag int work( char *data );
    Export_Flag int close( void );

    /** for now this is specific for AIX */
    Export_Flag void LIB_INIT initLib ();
    /** for now this is specific for AIX */
    Export_Flag void LIB_FINI closeLib ();

#if defined (__sun)
#pragma init (initLib)
#pragma fini (closeLib)
#endif

    void _init (void);
    void _fini (void);

#ifdef __cplusplus
}
#endif

#endif
