CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++0x
DEPS = src/IrcBot.h cstrlib/cstrlib.h
OBJ = src/IrcBot.o cstrlib/cstrlib.o src/main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cppTsunku: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm cppTsunku
