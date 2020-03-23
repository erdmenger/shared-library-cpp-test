# shared-library-cpp-test
Is a project to learn about behaviour of shared library entry and exit function implemented in C++ with different operating systems and compiler combinations.

## Building

### UNIX:
In order to build on a Unix flavour OS issue the following two
commands. The makefile successfully build on older versions of AIX,
HP-UX, Linux, Solaris, Tru64 .
```
% make prepare
% make
% make test
```

The first call will only create a directory for this plattform
where all the objects and executables will be copied to.

### Windows:
using MS VC++6:
tested on Windows NT 4.0 and Windows 2000

Open the MS Visual C++ Workspace file 'win32\shared_lib.dsw'.
Set the project 'testlib' as active project and hit F7 to compile.
You should find the library 'shared.dll' and the testprogram
'testlib.exe' in 'win32\testlib\Debug'


## Running the test

Call the testprogram like this:
```
% testlib -lib <full qualified path to lib> [-nounload]
```

On Windows you may leave the '-lib <something>' parameter out
because the lib and the program are within the same folder
and the libname 'shared.dll' is compiled into the test program
as default. So it will load the lib from the folder where
it resides.
