CFLAGS += -Wall -Wextra -pedantic -g

paoprint: main.c *.h
	gcc $(CFLAGS) -o paoprint main.c
