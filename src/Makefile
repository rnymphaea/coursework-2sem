CC=gcc
CFLAGS=-I$(HEADERS) -std=c99 -Wall -Wextra

BIN=./bin/
HEADERS=../headers

SRC = $(wildcard ./*.c)
SRC_CLI = $(wildcard ./cli/*.c)
SRC_TASKS = $(wildcard ./tasks/*.c)

OBJ =  $(patsubst ./%.c, $(BIN)%.o, $(SRC))
OBJ_CLI =  $(patsubst ./cli/%.c, $(BIN)%.o, $(SRC_CLI))
OBJ_TASKS =  $(patsubst ./tasks/%.c, $(BIN)%.o, $(SRC_TASKS))

OBJECTS = $(OBJ) $(OBJ_CLI) $(OBJ_TASKS)

.PHONY: all clean

all: $(BIN) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o cw

$(BIN):
	@ mkdir $(BIN)

${BIN}%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

${BIN}%.o: ./cli/%.c
	@ $(CC) $(CFLAGS) -c $< -o $@

${BIN}%.o: ./tasks/%.c
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) cw *.o
