# global variables: CXX and CXXFLAGS are predefined.
SOURCEDIR = source
CLIPPDIR = external/clipp/include/
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -I $(CLIPPDIR)

.PHONY: kompresor debug

all: kompresor

debug: CXXFLAGS += -DDEBUG -g
debug: kompresor

kompresor:
	$(CXX) $(CXXFLAGS) $(SOURCEDIR)/main.cpp -o $@

clean:
	rm kompresor
