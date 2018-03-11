# global variables: CXX and CXXFLAGS are predefined.
SOURCEDIR = source
CLIPPDIR = -I external/clipp/include/
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17

.PHONY: kompresor debug archivization_tools.o zip.o

all: kompresor

debug: CXXFLAGS += -DDEBUG -g
debug: kompresor

kompresor: archivization_tools.o
	$(CXX) $(CXXFLAGS) $(CLIPPDIR) $(SOURCEDIR)/main.cpp -o $@ zip.o archivization_tools.o

archivization_tools.o: zip.o
	$(CXX) $(CXXFLAGS) -c $(SOURCEDIR)/archivization_tools.cpp

zip.o:
	$(CXX) $(CXXFLAGS) -c $(SOURCEDIR)/zip.cpp

clean:
	rm kompresor
