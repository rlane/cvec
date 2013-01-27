CFLAGS = -g -O3 -std=c99 -fstrict-aliasing -Wall -Wextra -Werror -pedantic
LIBS = -lm

all: test

test: test.c cvec.h
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

check: test
	./test
	@echo "Tests passed"

clean:
	rm -f test
