include ../../mk/Makefile.root.include
include ../../mk/Makefile.libs.include

PROJ_CXXFLAGS 	+= -g -std=c++0x	#cxx  compile flags
TARGET_BIN 		:=main

PROJ_INC_PATHES 		+= $(GTEST_INCLUDE_PATH)
PROJ_LIB_PATHES 		+= 
PROJ_LIB_FULL_NAMES 	+= $(GTEST_LIB_FULL_NAME)

PROJ_STATIC_LIBS 	+= pthread


all: $(TARGET_BIN)

$(TARGET_BIN): $(OBJS)
	@echo $(OS_ARCH)
	@echo $(GTEST_INCLUDE_PATH)
	$(DO_CPP_TARGET)

clean:
	$(DO_CLEAN)
