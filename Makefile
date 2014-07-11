CC=g++
CFLAGS=-I. -O2
DEPS = IrcBot.h
OBJ = IrcBot.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cppTsunku: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
