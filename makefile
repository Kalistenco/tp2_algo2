CXXFLAGS = -Wall -g
CXX = g++

all : tp2

tp2 : main.o

main.o: main.cpp util.h
	$(CXX) $(CXXLAGS) -o main.o -c main.cpp 

clean :
	rm*.o