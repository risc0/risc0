CC=clang++
CFLAGS=-std=c++11 -O0 -I.
CFLAGS+=-isystem/opt/local/include #MacPorts
CFLAGS+=-isystem/opt/homebrew/include #Homebrew
LDFLAGS+=-L/opt/local/lib
LDFLAGS+=-L/opt/homebrew/lib
DEPS_HPP = circom.hpp calcwit.hpp fr.hpp

all: stark_verify

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

%.o: %.cpp $(DEPS_HPP) $(SOURCES)
	$(CC) -Wno-address-of-packed-member -c $< $(CFLAGS)

stark_verify: $(OBJECTS)
	$(CC) -o stark_verify $(OBJECTS) $(LDFLAGS) -lgmp

.PHONY: clean

clean:
	rm -f stark_verify $(OBJECTS)

