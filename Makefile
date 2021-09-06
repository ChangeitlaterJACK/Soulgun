CC=g++

OBJS=*.cpp

FLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -Wall

all: $(OBJS)
		$(CC) $(OBJS) $(FLAGS)

lab: $(OBJS)
		$(CC) $(OBJS) $(FLAGS) -D LAB
