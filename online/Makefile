#默认目标是 all
all: myclient Server
# myclient: myclient.o
# 	g++ myclient.o -o myclient
# 	rm myclient.o
# myclient.o: myclient.cpp
# 	g++ -c myclient.cpp
myclient:
	g++ myclient.cpp -o myclient
Server:
	g++ ./ReactorV5/*.cpp -o Server

.PHONY: clean
clean:
	rm -f  Server myclient *.o
