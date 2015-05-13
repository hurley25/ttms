#!Makefile

PROGRAM = ms

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

CC = clang

C_FLAGS = -std=c11 -c -Wall -Wextra -ggdb -Iutil -Iview -Imodel -Ittms

all: $(C_OBJECTS) 
	@echo 链接...
	$(CC) $(C_OBJECTS) -o $(PROGRAM)

.c.o:
	@echo 编译 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.PHONY:clean
clean:
	$(RM) $(C_OBJECTS) ms

