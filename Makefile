PROG = main
NAME = enigma
CC = g++

all: build run

build:
	$(CC) $(PROG).cpp Rotor.cpp Enigma.cpp -o $(NAME)

run:
	./$(NAME)