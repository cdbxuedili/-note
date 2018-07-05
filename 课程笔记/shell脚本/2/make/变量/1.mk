#使用=赋值，这种方法支持向后扩展
#B = $(A)
#A = linklist.o main.o

#　:=的赋值方法，不支持向后扩展
B := $(A)
A := linklist.o main.o
#B := $(A)

link:$(B)
	gcc $(B) -o link 

linklist.o:linklist.c
	gcc -c linklist.c -o linklist.o

main.o:main.c
	gcc -c main.c -o main.o

#名字叫什么无所谓，没有依赖文件,这种文件叫做伪目标文件

.PHONY:clean  
#严格区分clean一定是伪目标文件

clean:
	rm link *.o
