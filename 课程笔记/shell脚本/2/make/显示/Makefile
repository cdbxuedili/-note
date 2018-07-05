link:linklist.o main.o
	gcc linklist.o main.o -o link 

linklist.o:linklist.c
	gcc -c linklist.c -o linklist.o

main.o:main.c
	gcc -c main.c -o main.o

#名字叫什么无所谓，没有依赖文件,这种文件叫做伪目标文件

.PHONY:clean  
#严格区分clean一定是伪目标文件

clean:
	rm link *.o
