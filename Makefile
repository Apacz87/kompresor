# global variables: CXX and CXXFLAGS are predefined.
TARGET = kompresor
SOURCEDIR = source
CLIPPDIR = -I external/clipp/include/
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O0
RM = rm -f
SOURCEFILES = zip.cpp archivization_tools.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCEFILES))

.PHONY: $(TARGET) $(OBJECTS) debug clean

default: $(TARGET)
all: default

debug: CXXFLAGS += -DDEBUG -g
debug: $(TARGET)

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CLIPPDIR) $(SOURCEDIR)/main.cpp -o $@ $^

archivization_tools.o: zip.o
	$(CXX) $(CXXFLAGS) -c $(SOURCEDIR)/archivization_tools.cpp

zip.o:
	$(CXX) $(CXXFLAGS) -c $(SOURCEDIR)/zip.cpp

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET)
