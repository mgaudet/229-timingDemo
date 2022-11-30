CC=clang
CFLAGS=-g -std=c11

guess: guess.o secret.o
	$(CC) -o $@ $^
.c:
	$(CC) $(CFLAGS) $@.c $(LDFLAGS) -o $@