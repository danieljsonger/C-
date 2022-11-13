EXENAME = main

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra

all : $(EXENAME)

$(EXENAME): main.cpp binarytree.o
	$(CXX) $(CXXFLAGS) main.cpp binarytree.o -o $(EXENAME)

binarytree.o: binarytree.h binarytree.cpp
	$(CXX) $(CXXFLAGS) -c binarytree.cpp

.PHONY: clean
clean:
	rm -f *.o $(EXENAME)
