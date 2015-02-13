CC	= g++
CFLAGS	= -std=c++11 -fPIC -lpthread -w 
LDFLAGS	= -pthread
PROG	= run


# command

RM	=rm
CP	=cp
CD	=cd
MV	=mv

	
SOURCES	= ./src/random_source.cpp ./src/linearmatching.cpp ./src/node.cpp ./src/tinythread.cpp ./src/main.cpp ./src/random_util.cpp ./src/pat.cpp ./src/ds.cpp ./src/suffixtrie.cpp ./src/kmers_initparam.cpp ./src/alphabet.cpp ./src/kmers_delimitor.cpp ./src/kmers_reads.cpp ./src/qual.cpp ./src/filesplittor.cpp ./src/reorderdrive.cpp ./src/threadwrapper.cpp ./src/search_globals.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run
all: $(SOURCES) $(EXECUTABLE)
clean:
	$(RM) $(OBJECTS)
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC)  -c $(CFLAGS) $< -o $@

