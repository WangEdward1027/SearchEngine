#默认目标是 hello
hello: hello.o main.o
	g++ hello.o main.o -o hello
hello.o: hello.cpp
	g++ -c hello.cpp -o hello.o
main.o: main.cpp
	g++ -c main.cpp -o main.o

.PHONY:clean 
clean:
	rm -f *.o
	rm -f hello a.out
