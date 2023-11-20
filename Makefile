CC = clang
CFLAGS = -I/opt/homebrew/Cellar/mupdf/1.23.5/include
LDFLAGS =-L/opt/homebrew/Cellar/mupdf/1.23.5/lib

TARGET = pdftoc
# The line =SRCS = $(wildcard *.c)= in the Makefile sets the variable
# =SRCS= to the list of all C source files (=.c=) in the current
# directory. It uses the =$(wildcard pattern)= function to find the
# files matching the pattern =*.c=.
SRCS = $(wildcard *.c)
# The line `OBJS = $(SRCS:.c=.o)` in the Makefile generates a list of
# object files (`.o`) with the same names as the C source files (`.c`)
# in the `SRCS` variable. It substitutes the `.c` file extension with
# the `.o` extension for each source file. This is done using the
# pattern substitution syntax `$(variable:old_ext=new_ext)`.
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^  -lmupdf -lmupdf-third -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
