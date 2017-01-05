include ./mk/Makefile.include


TARGET_BIN=main


MY_FLAGS= -g -Werror

#TODO: CXX_SRC=$(wild *.cpp)
#TODO: C_SRC=$(wild *.cpp)
#OBJS = $(CXX_OBJS) $(C_OBJS)
OBJS = a.o


CXXFLAGS += $(MY_FLAGS) 

all: $(TARGET_BIN)

$(TARGET_BIN): $(OBJS)
	$(ECHO) "OK"
	$(CXX) -o $(TARGET_BIN) $^


clean:
	$(RM) -frv $(TARGET_BIN) *.o
