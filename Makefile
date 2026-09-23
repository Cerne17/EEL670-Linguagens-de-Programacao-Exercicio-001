CPP = g++
LD = g++

CPPFLAGS = -Wall -Wextra -Ilibrary

OBJ = main.o reading.o station.o system.o

BIN = main

all: $(BIN)

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

$(BIN): $(OBJ)
	$(LD) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)
