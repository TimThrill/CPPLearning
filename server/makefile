CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lpthread
CUR_SOURCES=main.cc EpollTask.cc SelectTask.cc
EXT_DIR=../common/
EXT_SOURCES=$(EXT_DIR)ThreadManager.cc $(EXT_DIR)ThreadException.cc
OBJECTS=$(CUR_SOURCES:.cc=.o) $(EXT_SOURCES:.cc=.o)
EXECUTABLE=server

all: $(CURSOURCES) $(EXT_SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	    $(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.cc.o:
	    $(CC) $(CFLAGS) $< -o $@
