.PHONY: all clean run

CC := g++
CFLAGS := -std=c++11 -Wno-deprecated-enum-enum-conversion -O2
CFLAGS += `wx-config --cxxflags`
CFLAGS += `pkg-config --cflags libmodbus`
LDFLAGS := `wx-config --libs`
LDFLAGS += `pkg-config --libs libmodbus`

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

all: main

clean:
	$(RM) $(OBJECTS) $(DEPENDS) main

run: main
	./main

-include $(DEPENDS)

# Make object files
%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Linking the executable from the object files
main: $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@
