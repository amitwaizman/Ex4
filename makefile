CC=gcc
AR=ar
FLAGS=-g -Wall

all: graphProg

#creat libraries
libmygraph.a:graph.o 
	$(AR) -rcs libmygraph.a graph.o 

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c 

graphProg: main.o libmygraph.a
	$(CC) $(FLAGS) -o graphProg main.o libmygraph.a -lm

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c



.PHONY: clean all

clean:
	rm -f *.o *.a *.so main graph
 
