CC=gcc
CFLAGS=-Iinclude
SRC=src/main.c src/shell.c
OBJ=$(SRC:.c=.o)
EXEC=fastshell

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXEC)
