CXX 	  := g++
CXXFLAGS  := -std=c++17 -Wall -Wno-format-security -pedantic-errors
LDFLAGS   := -L/usr/lib -lstdc++
SRC 	  := dbm.cpp
TARGET    := dbm

all: clean dbm

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/$@ $< $(LDFLAGS)

clean:
	@rm -f bin/*

run:
	./bin/$(TARGET)