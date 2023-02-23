CC=gcc
CFLAGS=-I../include
SRC=unit.c shell_test.c ../src/shell.c
OBJ=$(SRC:.c=.o)
EXEC=fastshell_unit

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o ../bin/$@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXEC)
