CC=g++
CFLAGS= -O2 -std=c++0x -Wall -I.
DEPS = IrcBot.h
OBJ = IrcBot.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cppTsunku: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm cppTsunku
