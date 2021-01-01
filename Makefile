# build the game by running 'make' in the source code folder
# BREAKOUT DANIEL HONUS UPR

OBJS	= main.o homescreen.o breakout.o
SOURCE	= main.c homescreen.c breakout.c
HEADER	= homescreen.h breakout.h
OUT	= breakout
CC	 = gcc
FLAGS	 =  -c -Wall
LFLAGS	 = -lSDL2 -lSDL2_ttf -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

# create/compile the individual files separately
main.o: main.c
	$(CC) $(FLAGS) main.c 

homescreen.o: homescreen.c
	$(CC) $(FLAGS) homescreen.c 

breakout.o: breakout.c
	$(CC) $(FLAGS) breakout.c 

# clean remove
clean:
	rm -f $(OBJS) $(OUT)

