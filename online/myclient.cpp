#include <sys/types.h>   //对<sys/socket.h>的补充,确保某些旧系统移植性。非必需
#include <sys/socket.h>  //socket()、connect()
#include <stdio.h>       //perror()
#include <arpa/inet.h>   //struct sockaddr_in
#include <string.h>      //memset()
#include <stdlib.h>      //atoi()
#include <unistd.h>      //close()
#include <iostream>      
#include <string>
#include <sstream>
#include <vector>
#include "nlohmann/json.hpp"
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::istringstream;
using std::vector;

//小火车协议
/* typedef struct train{ */
/*     int length; */
/*     string query; */
/* }train_t; */

int main(int argc, char *argv[])
{
    //0.命令行参数判断
    /* if(argc != 3){ */
    /*     cerr << "Usage : ./client IP port\n"; */
    /*     cout << "请重新输入\n"; */
    /*     return 1; */
    /* } */
    
    cout << "正在连接服务器...\n";
    //1.创建套接字
    int listenfd =socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("socket");
        return -1;
    }

    //2.初始化服务器地址结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 ,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = inet_addr(argv[1]);   //要连接的服务器的IP地址
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //要连接的服务器的IP地址
    //server_addr.sin_port = htons(atoi(argv[2]));        //要连接的服务器的端口号
    server_addr.sin_port = htons(8888);                   //要连接的服务器的端口号
    
    //3.连接服务器
    int ret = connect(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret == -1){
        perror("connect");
        close(listenfd);
        return -1;
    }
    cout << "连接服务器成功。\n\n"; 
    
    //4.数据传输
    while(1){
        //读取用户输入
        cout << "1 候选词推荐    2 网页搜索\n";
        cout << ">> 请输入要查询的内容: ";
        string line;
        getline(cin, line);       
        /* //line += "\n";   //getline()会去掉换行符,iss也会去掉换行符 */
    
        //对用户输入的处理
        istringstream iss(line);            
        string type;
        string context;
        iss >> type; 
        if((type != "1") && (type != "2")){
            cout << "请输入正确的查询语句!\n\n";
            continue;
        }
        iss >> context;
        
        //封装小火车协议
        /* train_t t; */       
        /* memset(&t, 0, sizeof(t)); */
        /* t.length = line.size(); */
        /* t.content = line; */       
        
        //创建json,包装查询类型和内容
        nlohmann::json json_object;
        json_object[type] = context;
        string query = json_object.dump() + "\n";

        //发送json到服务器
        int len = send(listenfd, query.c_str(), query.size(), 0); //send()默认是阻塞式的
        if(len == -1){
            cerr << "len == -1, 发送失败\n";
        }else if(len == 0){
            cout << "len == 0\n";
        }else{
            /* cout << "len = " << len << ", 客户端发送正常。\n"; */
        }
        
        //读取服务器返回的数据
        char buffer[65536] = {};  //数组太小会报错json_error
        len = recv(listenfd, buffer, sizeof(buffer), 0);
        if(len == -1){
            perror("recv() error");
            break;
        }else if(len == 0){
            cout << "len == 0\n";
        }else{
            string resp = buffer;   
            /* cout << "recv msg from server: " << resp << "\n"; */
            
            //对收到的json数组进行解析
            nlohmann::json json_array = nlohmann::json::parse(resp);
            
            //错误判断
            if(resp == "null"){  //索引查不到推荐词的情况,会返回null
                cout << "无推荐词\n\n"; 
                continue;
            } 
            if(!json_array.is_array()){
                cerr << "json数组解析错误\n";
                exit(1);
            }
            
            //解析json数组,并存储
            vector<string> candidateword;
            
            for(int i = 0; i < json_array.size(); ++i){
                /* cout << "json_array[" << i << "] = " << json_array[i] << "\n"; */
                nlohmann::json child_array = json_array[i];    
                for(int j = 0; j < child_array.size(); ++j){
                    candidateword.push_back(child_array[j]);
                }
            }
            //显示推荐词(目前是所有相关词,没有进行筛选和排序)
            for(int i = 0; i < candidateword.size(); ++i){
                cout << i+1 << "." << candidateword[i] << "\n";
            }

        }
        cout << "\n\n";
    }
    
    //5.关闭套接字
    close(listenfd);
    return 0;
}
