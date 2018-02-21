# global variables: CXX and CXXFLAGS are predefined.
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SOURCEDIR = source

.PHONY: kompresor

all: kompresor

kompresor:
	$(CXX) $(CXXFLAGS) $(SOURCEDIR)/main.cpp -o $@

clean:
	rm kompresor
