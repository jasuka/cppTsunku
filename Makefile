CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++0x
DEPS = IrcBot.h
OBJ = IrcBot.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cppTsunku: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm cppTsunku
