CXX = g++
CXXFLAGS = -I includes/
SRCS = $(wildcard ZHSH/*.cpp) main.cpp generator/Tree_generator.cpp MemoryAccessTracker.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

# Verifica o sistema operacional
ifeq ($(OS),Windows_NT)
	CLEAN_CMD = if exist ZHSH\*.o (del /f /q ZHSH\*.o) && if exist main.o (del /f /q main.o) && if exist generator\Tree_generator.o (del /f /q generator\Tree_generator.o) && if exist MemoryAccessTracker.o (del /f /q MemoryAccessTracker.o) && if exist $(EXEC) (del /f /q $(EXEC))
else
	CLEAN_CMD = rm -f ZHSH/*.o main.o generator/Tree_generator.o MemoryAccessTracker.o $(EXEC)
endif

all: clean $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)

run: all
	./$(EXEC)
