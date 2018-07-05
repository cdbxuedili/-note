obj = linklist.o main.o
#obj := linklist.o main.o

CC = gcc
FLAGS = -c -o

link:$(obj)
	$(CC) $(obj) -o link 

linklist.o:linklist.c
	#$(CC) -c linklist.c -o linklist.o
	$(CC) linklist.c $(FLAGS) linklist.o

main.o:main.c
	#$(CC) -c main.c -o main.o
	$(CC) main.c $(FLAGS) main.o

#名字叫什么无所谓，没有依赖文件,这种文件叫做伪目标文件

.PHONY:clean  
#严格区分clean一定是伪目标文件

clean:
	rm link *.o
