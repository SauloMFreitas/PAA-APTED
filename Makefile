CXX = g++
CXXFLAGS = -I includes/ -std=c++17 -Wall
SRCS = $(wildcard source/*.cpp) main.cpp generator/Tree_generator.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

# Verifica o sistema operacional
ifeq ($(OS),Windows_NT)
	CLEAN_CMD = if exist source\*.o (del /f /q source\*.o) && if exist main.o (del /f /q main.o) && if exist $(EXEC) (del /f /q $(EXEC))
else
	CLEAN_CMD = rm -f source/*.o main.o $(EXEC)
endif

all: clean $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)
