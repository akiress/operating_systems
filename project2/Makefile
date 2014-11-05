#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

CC=gcc
MAIN=pagerep
SRC=pagerep.c
OBJ=$(SRC:.c=.o)

all: $(MAIN)

$(MAIN): $(OBJ)
	$(CC) -o $(MAIN) $(OBJ)

.c.o:
	$(CC) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRC)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
