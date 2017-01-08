include ../../mk/Makefile.root.include
include ../../mk/Makefile.libs.include


PROJ_INC_PATHES 		+= 	$(GTEST_INCLUDE_PATH) \
							$(GMOCK_INCLUDE_PATH)
PROJ_LIB_PATHES 		+= 
PROJ_LIB_FULL_NAMES 	+= 	$(GTEST_LIB_FULL_NAME) \
							$(GMOCK_LIB_FULL_NAME)

TARGET_BIN=main

all: $(TARGET_BIN)

$(TARGET_BIN): $(OBJS)
	$(DO_CPP_TARGET)
clean:
	$(DO_CLEAN)
