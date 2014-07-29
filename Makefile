CC = g++
CCFLAGS = -Wall -Wextra -pedantic-errors -std=c++0x
ODIR = obj
SOURCE = src

DEPS = 	$(SOURCE)/IrcBot.h $(SOURCE)/cstrlib/cstrlib.h
OBJ = 	$(SOURCE)/IrcBot.o $(SOURCE)/main.o $(SOURCE)/cstrlib/cstrlib.o


TARGET = cppTsunku

all: $(ODIR) $(TARGET)

$(ODIR):
	mkdir $(ODIR)

#Is this needed? it doesnt even seem to be using this
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $(ODIR)/$@ $< $(CCFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^

move:
	@for file in $(OBJ); do\
		mv $$file $(ODIR);\
	done
	@echo "Object files moved successfully to $(ODIR) from source tree"

clean:
	rm -rf $(ODIR)
	rm $(TARGET