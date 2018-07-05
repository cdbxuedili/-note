obj = linklist.o main.o
CC = gcc
FLAGS = -c -o

link:$(obj)
	$(CC) $^ -o $@

linklist.o:linklist.c
	$(CC) $^ $(FLAGS) $@

main.o:main.c
	$(CC) $^ $(FLAGS) $@

clean:
	rm link *.o
