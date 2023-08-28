# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main GameTesterMain

main: main.cpp Game.o
	$(CXX) $(CXXFLAGS) main.cpp Game.o -o main

# The -c command produces the object file
Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp -o Game.o

GameTesterMain: GameTesterMain.cpp Game.o GameTester.o
	$(CXX) $(CXXFLAGS) GameTesterMain.cpp Game.o GameTester.o -o GameTesterMain

GameTester.o: GameTester.cpp GameTester.h
	$(CXX) $(CXXFLAGS) -c GameTester.cpp -o GameTester.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o GameTesterMain main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump

