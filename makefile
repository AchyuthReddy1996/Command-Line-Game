# Makefile

# the C++ compiler
CXX     = g++
#CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3 -std=c++14

all: main 

main: main.cpp Player.o Enemy.o Room.o 
	$(CXX) $(CXXFLAGS) main.cpp Player.o Enemy.o Room.o -o main

Room.o: Room.cpp 
	$(CXX) $(CXXFLAGS) -c Room.cpp -o Room.o

Enemy.o: Enemy.cpp 
	$(CXX) $(CXXFLAGS) -c Enemy.cpp -o Enemy.o

Player.o: Player.cpp Room.h Enemy.h
	$(CXX) $(CXXFLAGS) -c Player.cpp -o Player.o



deepclean:
	rm -f *~ *.o main *.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump

