CC = clang
CFLAGS = -I/opt/homebrew/Cellar/mupdf/1.23.5/include -I/opt/homebrew/Cellar/cjson/1.7.16/include
LDFLAGS = -L/opt/homebrew/Cellar/mupdf/1.23.5/lib -L/opt/homebrew/Cellar/cjson/1.7.16/lib

TARGET = pdftoc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lmupdf -lmupdf-third -lm -lcjson

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
