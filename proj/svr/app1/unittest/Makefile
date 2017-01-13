include ../../../mk/Makefile.root.include
include ../../../mk/Makefile.libs.include

PROJ_CXXFLAGS 	+= -g -std=c++0x	#cxx  compile flags
UT_TARGET_BIN 		:=main

PROJ_INC_PATHES 		+= $(GTEST_INCLUDE_PATH) \
						..
PROJ_LIB_PATHES 		+=  
PROJ_LIB_FULL_NAMES 	+= $(GTEST_LIB_FULL_NAME)

PROJ_STATIC_LIBS 	+= pthread

UT_DEST_EXCLUDE_OBJS	:= ../main.o
UT_DEST_OBJS 			:= $(filter-out $(UT_DEST_EXCLUDE_OBJS), $(patsubst %.cpp,%.o, $(wildcard ../*.cpp)))

CXX_OBJS  	+=  $(UT_DEST_OBJS)

all: $(TARGET_BIN)

$(UT_TARGET_BIN): $(OBJS)
	$(DO_CPP_TARGET)

clean:
	$(DO_CLEAN)
