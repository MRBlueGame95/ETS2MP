CXX=g++
#-m32
CXXFLAGS=-c -static
LDFLAGS=-ldl -lpthread -static
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../../../../lib/RakNet.a

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
#	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	ar rcs $@ $(OBJECTS) 

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -Rf $(OBJECTS) $(EXECUTABLE)
