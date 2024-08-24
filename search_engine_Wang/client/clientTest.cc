///
/// @file    clientTest.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-02-03 21:10:10
///
#include "../include/proparse/json.hpp"
//#include "json.hpp"
#include "../include/proparse/protocol.hpp"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <linux/socket.h>

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void process()
{
	int clientfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientfd < 0)
	{
		perror("socket");
		return;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	socklen_t length = sizeof(serverAddr);

	if (::connect(clientfd, (struct sockaddr *)&serverAddr, length) < 0)
	{
		perror("connect");
		close(clientfd);
		return;
	}
	cout << "conn has connected!..." << endl;

	while (1)
	{
		string line;
		// cout << ">> pls input some message: ";
		cout << ">> 请输入需要查询的内容: ";
		getline(cin, line);
		//line.append("\n");
		//send(clientfd, line.c_str(), line.size(), 0);

		//1. 客户端先发数据
		ProtocolParser tran;
		// if (line.substr(0, 2) == "1 ")
		if (line.substr(0, 1) == "1")
		{
			//cout << "before send key " << endl;
			string ret = tran.doPack(1, line.data() + 2);
			ret.append("\n");
			cout << ret << endl;
			send(clientfd, ret.c_str(), ret.size(), 0);
			//cout << "after send key " << endl;
		}
		// else if (line.substr(0, 2) == "2 ")
		else if (line.substr(0, 1) == "2")
		{
			// cout << "before send web " << endl;
			string ret = tran.doPack(2, line.data() + 2);
			ret.append("\n");
			cout << ret << endl;
			send(clientfd, ret.c_str(), ret.size(), 0);
			// cout << "after send web " << endl;
		}
		else
		{
			cout << "请输入正确的查询语句!" << endl;
			continue;
		}

		char buf[65535] = {0};
		recv(clientfd, buf, sizeof(buf), 0);

		// cout << buf << endl;
		struct res
		{
			int _id;
			vector<string> _content;
		};

		auto res = tran.doParse(buf);
		if (res._id == 100)
		{
			// cout << "before recv key " << endl;
			/* if (res._content.size() == 0)
			{
				cout << "对不起，未查询到符合要求的内容！" << endl;
				continue;
			} */
			cout << ">> 为您推荐以下搜索词:" << endl;
			for (auto &i : res._content)
			{
				cout << i << endl;
			}
			// cout << "after recv key " << endl;
		}
		else if (res._id == 200)
		{
			if (res._content.size() == 0)
			{
				cout << "对不起，未查询到符合要求的内容！" << endl
					 << endl;
				continue;
			}
			// cout << "before recv web " << endl;
			cout << ">> 为您查询到以下内容:" << endl;
			for (auto &i : res._content)
			{
				cout << i << endl;
			}
			// cout << "after recv web " << endl;
		}
		else
		{
			cout << "查询出错" << endl
				 << endl;
		}
	}
	//close(clientfd);
	return;
}

/* sleep(1); */
/* close(clientfd); */
/* break; */

/* close(clientfd); */

int main(void)
{
	process();
	return 0;
}
