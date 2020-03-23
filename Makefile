# This make file is writte for use with GNU Make
# @author: Joerg Erdmenger
# The tools

RM = rm -rf
MKDIR = mkdir
EXE =
POST_LINK.cc = #
# all platforms except win
COMPILE_ONLY = -c 
OUTPUT_FILE = -o 
DEBUG = -g

PLATFORM:=$(shell uname)

ifeq ($(PLATFORM),AIX)
  CC = xlC_r
  LINK_SHARED.cc = makeC++SharedLib_r -p0  -bI:/lib/pse.exp -bmaxdata:0x80000000 -bexpall -b initfini:initLib:closeLib 
#  POST_LINK.cc = ar -cvr
#  LIB_POST = .1
  TEST_LIBS+= -ldl
  SO = .a
endif

ifeq ($(PLATFORM),Linux)
  CC = g++
  CFLAGS+= -fPIC
  LINK_SHARED.cc = g++ -shared -fPIC -Xlinker -rpath -Xlinker ../lib/i686-pc-linux-gnu -Xlinker -rpath-link -Xlinker ../lib/i686-pc-linux-gnu
# -init initLib -fini closeLib
  TEST_LIBS+= -ldl
#  CFLAGS += -ldl
  SO = .so
endif

ifeq ($(PLATFORM),Darwin)
  CC = gcc
  LINK_SHARED.cc = g++ -shared  -Xlinker -rpath -Xlinker -rpath-link
# -rpath-link -Xlinker ../lib/i686-pc-linux-gnu
# -init initLib -fini closeLib
  TEST_LIBS+= -ldl
#  CFLAGS += -ldl
  SO = .so
endif


ifeq ($(PLATFORM),OSF1)
  CC = cxx
  LINK_SHARED.cc = ld -shared -init initLib -fini closeLib -lc
  SO = .so
endif

ifeq ($(PLATFORM),SunOS)
  CC = CC
  LINK_SHARED.cc = CC -G
# -features=rtti
# -mt -KPIC -w
#  -z muldefs
#-z initfirst initLib
  TEST_LIBS+= -ldl
  SO = .so
endif

ifeq ($(PLATFORM),HP-UX)
  CC = aCC
  LINK_SHARED.cc = aCC -b -Wl,+s -Wl,+b/usr/lib:/usr/ccs/lib -Wl,+n
  TEST_LFLAGS = -Wl,+s -Wl,+b/usr/lib:/usr/ccs/lib -Wl,+n -I/usr/local/ACE/ACE_wrappers
  TEST_LIBS = -L/usr/local/ACE/ACE_wrappers/ace -lACE -lpthread -lxti -lrt
# only on 64 bit (PA 2.x / HP-UX 11):
  LINK_SHARED.cc +=  -Wl,'+fini closeLib' -Wl,'+init initLib'
  CFLAGS += +Z
  SO = .so
endif

ifeq ($(PLATFORM),CYGWIN_NT-5.0)
  CC = cl
  LINK_SHARED.cc = link /dll 
  CFLAGS =	/DWIN32 /G4 /Gs /Oit /MTd /nologo /W3 /WX /Gm /GX /Od /ZI
  LFLAGS =	/NOLOGO /BATCH /INCREMENTAL:NO
  COMPILE_ONLY = /c
  OUTPUT_FILE = /o 
  DEBUG = /DEBUG
endif

CFLAGS += $(DEBUG)
OBJ =  $(PLATFORM)/shared.o $(PLATFORM)/obj1.o $(PLATFORM)/obj2.o
# Rules:

default: lib exec
all: default prepare
lib: shared$(SO)

shared$(SO) : ${OBJ}
		$(LINK_SHARED.cc) $(DEBUG) $(OUTPUT_FILE) $(PLATFORM)/lib$(@) ${OBJ};

exec: testlib.c
	$(CC) $(CFLAGS) $(OUTPUT_FILE) $(PLATFORM)/testlib$(EXE) $< ${TEST_LIBS};


test:
	./$(PLATFORM)/testlib$(EXE) -lib $(PLATFORM)/libshared$(SO);



$(PLATFORM)/%.o: %.c
	$(CC) $(COMPILE_ONLY) $(CFLAGS) $(OUTPUT_FILE) $(@) $<;

$(PLATFORM)/%.o: %.cpp
	$(CC) $(COMPILE_ONLY) $(CFLAGS) $(OUTPUT_FILE) $(@) $<;
#	$(CC) $(CFLAGS) $(COMPILE_ONLY) $<;

$(PLATFORM)/obj1.o: obj1.cpp
	$(CC) $(COMPILE_ONLY) $(CFLAGS) $(OUTPUT_FILE) $(@) $<;

prepare:
	$(MKDIR) $(PLATFORM);

clean:
	$(RM) $(PLATFORM) so_locations testlib.o shared;

