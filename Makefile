# global variables: CXX and CXXFLAGS are predefined.
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SOURCEDIR = source

.PHONY: kompresor debug

all: kompresor

debug: CXXFLAGS += -DDEBUG -g
debug: kompresor

kompresor:
	$(CXX) $(CXXFLAGS) $(SOURCEDIR)/main.cpp -o $@

clean:
	rm kompresor
