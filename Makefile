CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++0x
DEPS = src/IrcBot.h src/cstrlib/cstrlib.h
OBJ = src/IrcBot.o src/main.o src/cstrlib/cstrlib.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

cppTsunku: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)
#clean:
#	rm *.o
#	rm cppTsunku