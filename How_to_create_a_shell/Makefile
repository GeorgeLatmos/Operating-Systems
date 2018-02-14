SHELL := /bin/bash

# ==================================================
# COMMANDS

CC = gcc
RM = rm -f

# ==================================================
# TARGETS

all: myShell

# final link for executable
myShell: main.o interactive.o batch.o functions.o
	$(CC) $^ -o $@

# generate objects
%.o: %.c
	$(CC) -c $<

# clean temporary files
clean:
	$(RM) *.o *~

# remove executable
purge: clean
	$(RM) myShell