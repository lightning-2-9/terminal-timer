CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

.PHONY = all clean

all: timer

timer: timer.c
	$(CC) $(CFLAGS) -o tt timer.c $(LDFLAGS)

clean:
	rm -f tt
