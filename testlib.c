#include <stdlib.h>                                            /* for malloc */
#include <stdio.h>                                             /* for printf */
#include <string.h>                                              /* strcmp() */
#include <errno.h>

/* now for the dynamic loading */
#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>                     /* alarm() */
#  include <dlfcn.h> /* for solaris, dlopen, dlsym - */
#endif
#include <signal.h>                                                /* sigset */

#if defined __hpux
# include <ace/OS.h>
#  define dlopen( a, b)  ACE_OS::dlopen( a, b)
#  define dlsym( a, b)   ACE_OS::dlsym( a, b)
#  define dlerror()      ACE_OS::dlerror()
#endif

#ifndef _WIN32
void * libHandle = 0;
#else
HINSTANCE libHandle = 0;
#endif


static const char *function_names[] =
{
   "open",
   "work",
   "close"
};

/** The array of function pointers. */
#define FUNC_ARRSIZE 3
#define LIB_OPEN   0
#define LIB_WORK   1
#define LIB_CLOSE  2

#define OPEN_A(arr) (*((int(*)(char *, char ** ))arr[LIB_OPEN]))
#define WORK_A(arr) (*((int(*)(char *))arr[LIB_WORK]))
#define CLOSE_A(arr) (*((int(*)())arr[LIB_CLOSE]))


static void usage( )
{
    printf("usage:\n");
    printf("  testlib -lib <library to load>\n");
}
/*
 * Return pointers to each of the functions.  Exit if they can't be
 *  loaded.
 * @param arr is an array of function pointers.  Must be SBTFUNC_ARRSIZE long
 */
static void load_funcs(void ** arr, char * lib_name)
{
    /*void *libHandle = 0;*/
   int   i;

#ifdef _WIN32
   libHandle = LoadLibrary(lib_name);
#else
#  ifdef _AIX
     libHandle = dlopen(lib_name, RTLD_NOW);
#  else
     libHandle = dlopen(lib_name, RTLD_NOW);
#  endif
#endif
   if (!libHandle)
   {
       printf( " The errno after dlopen is: %d \n",errno);
#ifdef _WIN32
      printf( " %s\n", GetLastError() );
#else
      printf( " %s\n", dlerror());
#endif
      exit(1);
   }
   printf("%s is found and the function pointers: ",lib_name);
   for (i = 0; i < FUNC_ARRSIZE; i++)
   {
       arr[i] = 0;
#ifdef _WIN32
       arr[i] = GetProcAddress(libHandle, function_names[i]);
#elif defined __hpux
      arr[i] = dlsym( (mapped_shl_entry *) libHandle, function_names[i]);
#else
       arr[i] = dlsym( libHandle, function_names[i]);
#endif
       if (!arr[i])
       {
           printf( "Function '%s' could not be loaded from the shared library %s.\n", function_names[i], lib_name);
#ifdef _WIN32
           printf( "System Error: %d\n", GetLastError());
#else
           printf( "System Error: %s\n", dlerror());
#endif
           exit(1);
       } else {
           printf("'%s()' ",function_names[i]);
       }
   }
      printf("are loaded.\n");
}

int libUnLoad () 
{
	printf("unloading library\n");
#ifdef _WIN32    
    /* unload th DLL */
    FreeLibrary(libHandle);
    
    return GetLastError();
#else
    /* Unload shared library */
    if (dlclose(libHandle))
        return 20;
    else
		return 0;
#endif
}

/*****************************************************************************/
/* Program body.                                                             */
/*****************************************************************************/
int main(int argc, char ** argv)
{
    void       *func[FUNC_ARRSIZE];
    char        *value = 0;
    char       **returnVal = &value;
    int         nounload;

#ifdef _WIN32
     char          *lib_name = "shared.dll";
#else
#  ifdef _AIX
     char          *lib_name = "libshared.a";
#  else
     /* SUN, LINUX, HP-UP, Tru64, .. */
     char          *lib_name = "libshared.so";
#  endif
#endif

    nounload = 0;
   /*******************/
   /* Parse arguments */
   /*******************/
   for (argv++; *argv; argv++)
   {
       if (!strcmp(*argv, "-lib"))
       {
           if (!*++argv)
           {
               usage();
               return 1;
           }
           lib_name = *argv;
       } 
       else if (!strcmp(*argv, "-nounload"))
       {
	   nounload = 1;
       }
       else{
           usage();
           return 1;
       }

   }

   load_funcs( func, lib_name);
   OPEN_A(func)("String from test program",returnVal);
   printf( "open successful returned: '%s'.\n",value);

   WORK_A(func)("12345667890ABCD");
   CLOSE_A(func)();
   if( 0 == nounload )
   {
       libUnLoad();
   }
   return 0;
}
