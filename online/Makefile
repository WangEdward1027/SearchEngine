#默认目标是 all
all: myclient Server

myclient: myclient.o
	g++ myclient.o -o myclient
myclient.o: myclient.cpp
	g++ -c myclient.cpp

# g++ ./ReactorV5/*.cpp Dictionary.cpp -o Server
Server: Acceptor.o EchoServer.o EventLoop.o InetAddress.o \
	    Socket.o SocketIO.o TaskQueue.o TcpConnection.o   \
		TcpServer.o TestEchoServer.o ThreadPool.o Dictionary.o		  
		g++ Acceptor.o EchoServer.o EventLoop.o InetAddress.o \
			Socket.o SocketIO.o TaskQueue.o TcpConnection.o   \
			TcpServer.o TestEchoServer.o ThreadPool.o Dictionary.o -o Server
Acceptor.o: ./ReactorV5/Acceptor.cpp
	g++ -c ./ReactorV5/Acceptor.cpp
EchoServer.o: ./ReactorV5/EchoServer.cpp
	g++ -c ./ReactorV5/EchoServer.cpp
EventLoop.o: ./ReactorV5/EventLoop.cpp
	g++ -c ./ReactorV5/EventLoop.cpp
InetAddress.o: ./ReactorV5/InetAddress.cpp
	g++ -c ./ReactorV5/InetAddress.cpp
Socket.o: ./ReactorV5/Socket.cpp
	g++ -c ./ReactorV5/Socket.cpp
SocketIO.o: ./ReactorV5/SocketIO.cpp
	g++ -c ./ReactorV5/SocketIO.cpp
TaskQueue.o: ./ReactorV5/TaskQueue.cpp
	g++ -c ./ReactorV5/TaskQueue.cpp
TcpConnection.o: ./ReactorV5/TcpConnection.cpp
	g++ -c ./ReactorV5/TcpConnection.cpp
TcpServer.o: ./ReactorV5/TcpServer.cpp
	g++ -c ./ReactorV5/TcpServer.cpp
TestEchoServer.o: ./ReactorV5/TestEchoServer.cpp
	g++ -c ./ReactorV5/TestEchoServer.cpp
ThreadPool.o: ./ReactorV5/ThreadPool.cpp
	g++ -c ./ReactorV5/ThreadPool.cpp
Dictionary.o : Dictionary.cpp
	g++ -c Dictionary.cpp

.PHONY: clean
clean:
	rm -f  Server myclient *.o
