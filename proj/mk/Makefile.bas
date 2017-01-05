
SRC_ROOT=/home/tra1/gems2.0 # get current obsolute directory
INSTALL_ROOT=$(SRC_ROOT)/install

BUILD_DATE=$(shell date "+%Y-%m-%d %H:%M:%S")
# version from git 
SVR_MAJOR_VERSION=1.0   #
SVR_VERSION=$(SVR_MAJOR_VERSION).0



##----------------------------------------------------------
A=@
#CC    = gcc
#CXX   = g++
#AR    = ar
RM    = rm -rf
ECHO  = echo
MV    = mv
MAKE  = make
CD    = cd
CP    = cp -R
MKDIR = mkdir -p

##-----------OS/COMPILE SPECIAL FLAGS------------
COSFLAGS = -finline-functions -Wall -pipe -Wshadow -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wsign-compare   -fPIC
AROSFLAGS=
OFLAG    = -O0

##----------------------------------------------------------
COMPILE_FLAG = -g $(COSFLAGS) $(OFLAG) -DDEBUG_F -DMONITOR_F -DBUILD_DATE="\"$(BUILD_DATE)\"" -DSVR_VERSION="\"$(SVR_VERSION)\"" -DSVR_MAJOR_VERSION="\"$(SVR_MAJOR_VERSION)\""
CFLAGS   = -Wmissing-prototypes $(COMPILE_FLAG)
CXXFLAGS = $(COMPILE_FLAG)
DLLFLAGS = -shared
ARFLAGS  = $(AROSFLAGS) -ruc

##----------------------------------------------------------
INCPATH  = -I./ -I$(SRC_ROOT)/easy/base/ -I$(SRC_ROOT)/easy/lib/ -I$(SRC_ROOT)/easy/util/ -I$(SRC_ROOT)/persudo/ -I$(SRC_ROOT)/persudo/sha/ -I$(SRC_ROOT)/persudo/a2r_b/ -I$(SRC_ROOT)/public/memdb/
LIBS     = -lm -lc -lpthread -ldl
USRLIBS  =
USRINCPATH =

##----------------------------------------------------------
.SUFFIXES: .c .cpp .C .o

.cpp.o:
	$(A)$(ECHO) "Compiling [cpp] file:[$@] ..."
	$(A)$(CXX) $(CXXFLAGS) $(INCPATH) $(USRINCPATH) -c $<

.C.o:
	$(A)$(ECHO) "Compiling [cpp] file:[$@] ..."
	$(A)$(CXX) $(CXXFLAGS) $(INCPATH) $(USRINCPATH) -c $<

.c.o:
	$(A)$(ECHO) "Compiling [ c ] file:[$@] ..."
	$(A)$(CC)  $(CFLAGS)   $(INCPATH) $(USRINCPATH) -c $<
