CC = gcc
CFLAGS = -Wall -Wextra

test: src/connect-n.c
	$(CC) $(CFLAGS) $^ -o $@
