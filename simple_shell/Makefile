CC=gcc
CFLAGS=-Wall -D_GNU_SOURCE

all: simsh

simsh: simsh.o
	$(CC) $(CFLAGS) -o $@ $^
	
%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

%.o : %.c
	$(CC)  $(CFLAGS) -o $@ -c $<

clean :
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -f simsh
