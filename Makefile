.SUFFIXES: .o .c

CFLAGS += -Wall -Wextra -pedantic -g

paoprint: main.o utils.o
	$(CC) $(CFLAGS) -o paoprint main.o utils.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# BUG: Headers should be included in dependencies too
