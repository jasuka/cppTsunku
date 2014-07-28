CC = g++
CCFLAGS = -Wall -Wextra -pedantic-errors -std=c++0x
ODIR = obj
DEPS = src/IrcBot.h src/cstrlib/cstrlib.h
OBJ = src/IrcBot.o src/main.o src/cstrlib/cstrlib.o

TARGET = cppTsunku

all: $(ODIR) $(TARGET) move 

$(ODIR):
	mkdir $(ODIR)

%.o: %.c $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^

move:
	for file in $(OBJ); do\
		mv $$file $(ODIR);\
	done

#clean:
#	rm *.o
#	rm cppTsunku