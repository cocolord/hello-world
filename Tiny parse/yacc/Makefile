CC = gcc

CFLAGS = 

OBJS = scan.o parse.o

tiny: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o tiny

scan.o: lex.yy.c scan.h 
	$(CC) $(CFLAGS) -c lex.yy.c -o scan.o

parse.o: y.tab.c scan.h 
	$(CC) $(CFLAGS) -c y.tab.c -o parse.o

clean:
	-rm tiny
	-rm $(OBJS)

all: tiny 

