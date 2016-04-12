CC=gcc
SDLFLAGS=-framework SDL2 -framework SDL2_image -framework SDL2_ttf
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=peerpong

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDLFLAGS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $< -o $@

clean:
	rm -rf *.o