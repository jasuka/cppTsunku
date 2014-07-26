CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++0x
DEPS = IrcBot.h cstd.h
OBJ = IrcBot.o cstd.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cppTsunku: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm cppTsunku
