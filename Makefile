CC = gcc
CFLAGS = -Wall -Wextra -O2

.PHONY = all clean

all: timer

timer: timer.c
	$(CC) $(CFLAGS) -o tt timer.c

clean:
	rm -f tt
