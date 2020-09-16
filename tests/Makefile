
CC = cc
CFLAGS = -I ../include -std=c11

DIR = ../libcx
LIB = $(DIR)/libcx.a
OBJ = $(patsubst %.c, %.o, $(wildcard *.c))
BIN = $(patsubst %.c, %, $(wildcard *.c))

default: build $(BIN)

build:
	@make -C $(DIR) -s

%: %.c build
	$(CC) $(CFLAGS) -c $(@).c
	$(CC) $(@).o $(LIB) -o $(@)

clean:
	@rm -f $(BIN) $(OBJ)
	@make -C $(DIR) -s clean
