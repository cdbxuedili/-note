#如果makefile中有多个伪目标，不指定为目标名称时，默认调用第一个伪目标
a:
	@echo "hello"

b:
	@echo "world"

c:
	@echo "farsight"
