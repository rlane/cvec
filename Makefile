CFLAGS = -g -Wall -Werror -O3
LIBS = -lm

all: test

test: test.c cvec.h
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm -f test
