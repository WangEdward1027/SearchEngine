#定义公共路径变量
SRC := ./ReactorV5/
OBJ := ./obj/

#默认目标是 all
all: myclient Server

myclient: $(OBJ)myclient.o
	g++ $(OBJ)myclient.o -o myclient
$(OBJ)myclient.o: myclient.cpp
	g++ -c myclient.cpp ; mv myclient.o $(OBJ)

Server: $(OBJ)Acceptor.o $(OBJ)EchoServer.o $(OBJ)EventLoop.o $(OBJ)InetAddress.o \
	    $(OBJ)Socket.o $(OBJ)SocketIO.o $(OBJ)TaskQueue.o $(OBJ)TcpConnection.o   \
		$(OBJ)TcpServer.o $(OBJ)TestEchoServer.o $(OBJ)ThreadPool.o \
		Dictionary.o		  
		g++ $(OBJ)Acceptor.o $(OBJ)EchoServer.o $(OBJ)EventLoop.o $(OBJ)InetAddress.o \
			$(OBJ)Socket.o $(OBJ)SocketIO.o $(OBJ)TaskQueue.o $(OBJ)TcpConnection.o   \
			$(OBJ)TcpServer.o $(OBJ)TestEchoServer.o $(OBJ)ThreadPool.o \
			Dictionary.o -o Server
$(OBJ)Acceptor.o:  $(SRC)Acceptor.cpp
	g++ -c $(SRC)Acceptor.cpp ; mv Acceptor.o $(OBJ)
$(OBJ)EchoServer.o: $(SRC)EchoServer.cpp
	g++ -c $(SRC)EchoServer.cpp ; mv EchoServer.o $(OBJ)
$(OBJ)EventLoop.o: $(SRC)EventLoop.cpp
	g++ -c $(SRC)EventLoop.cpp ; mv  EventLoop.o $(OBJ)
$(OBJ)InetAddress.o: $(SRC)InetAddress.cpp
	g++ -c $(SRC)InetAddress.cpp ; mv InetAddress.o $(OBJ)
$(OBJ)Socket.o: $(SRC)Socket.cpp
	g++ -c $(SRC)Socket.cpp ; mv Socket.o $(OBJ)
$(OBJ)SocketIO.o: $(SRC)SocketIO.cpp
	g++ -c $(SRC)SocketIO.cpp ; mv SocketIO.o $(OBJ)
$(OBJ)TaskQueue.o: $(SRC)TaskQueue.cpp
	g++ -c $(SRC)TaskQueue.cpp ; mv TaskQueue.o $(OBJ)
$(OBJ)TcpConnection.o: $(SRC)TcpConnection.cpp
	g++ -c $(SRC)TcpConnection.cpp ; mv TcpConnection.o $(OBJ)
$(OBJ)TcpServer.o: $(SRC)TcpServer.cpp
	g++ -c $(SRC)TcpServer.cpp ; mv TcpServer.o $(OBJ)
$(OBJ)TestEchoServer.o: $(SRC)TestEchoServer.cpp
	g++ -c $(SRC)TestEchoServer.cpp ; mv TestEchoServer.o $(OBJ)
$(OBJ)ThreadPool.o: $(SRC)ThreadPool.cpp
	g++ -c $(SRC)ThreadPool.cpp ; mv ThreadPool.o $(OBJ)
$(OBJ)Dictionary.o : Dictionary.cpp
	g++ -c Dictionary.cpp ; mv Dictionary.o $(OBJ)

.PHONY: clean
clean:
	rm -f  Server myclient *.o $(OBJ)*.o
