#include "EchoServer.h"
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../nlohmann/json.hpp"
using std::bind;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

#if 0
void test(){
    //测试:输出 map<string,set<type>>
    cout << "---------\n";
    for(auto &elem : _candidetaWordSet){
        cout << elem.first <<": ";
        for(auto &e: elem.second){
            cout << e << " ";
        }        
        cout << "\n";
    }
    cout << "--------\n";
}
#endif

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con)
: _msg(msg)
, _con(con)
, _dict()
{
    //预热
    _dict.loadCnIndex();
    _dict.loadCnDictionary();
}
 
void MyTask::process()
{
    //在process函数中进行业务逻辑的处理
    nlohmann::json json_object = nlohmann::json::parse(_msg);      
    
    string type, context;
    for(auto &p: json_object.items()){
        type = p.key();
        context = p.value();
    }

    //根据type处理不同的业务:1 候选词推荐, 2 网页查询
    //1.候选词推荐
    if(type == "1"){
        //候选词分解为一个个字符
        for(size_t i = 0; i < context.size();){
            // 1000 0000 & ch
            if((context[i] & 0x80) == 0){  //英文
                _character.push_back(context.substr(i,1));
                i++;
            }else{  //中文
                _character.push_back(context.substr(i,3));
                i += 3;
            }
        }
        
        //根据索引找到字典中对应的词,放入对应字符的候选词集合set
        for(auto &character: _character){
            /* set index = _index_cn[character]; */
            set index = _dict._index_cn[character];
            for(auto &idx : index){
                /* _candidetaWordSet[character].insert(_dict_cn[idx]); */
                _candidetaWordSet[character].insert(_dict._dict_cn[idx]);
            }                       
        }
               
        //将候选词插入json数组中
        nlohmann::json json_array;
        for(auto &elem : _candidetaWordSet){
            nlohmann::json child_object;
            for(auto &candidateword: elem.second){
                child_object.push_back(candidateword);
            }
            json_array.push_back(child_object); 
        }
        //序列化
        _msg = json_array.dump();
    
    //2.网页查询
    }else if(type == "2"){
        _msg = "客官要网页查询\n";


    }else{ //预防手段。实际上非1、2的type,已经在客户端进行拦截,不会发送到服务器
        cout << "type == " << type << "\n";
        _msg = "请输入正确的type\n";
    }

    _con->sendInLoop(_msg);
}

EchoServer::EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port)
: _pool(threadNum, queSize)
, _server(ip, port)
{}

EchoServer::~EchoServer(){}

void EchoServer::start()
{
    _pool.start();
    cout << "EchoServer:线程池启动" << endl;
    //注册所有回调函数
    using namespace std::placeholders;
    _server.setAllCallback(bind(&EchoServer::onNewConnection, this, _1),
                           bind(&EchoServer::onMessage, this, _1),
                           bind(&EchoServer::onClose, this, _1));
 
    cout << "EchoServer:Tcp服务器启动" << endl;
    _server.start();
}

void EchoServer::stop()
{
    _pool.stop();
    _server.stop();
}

//三个回调函数
//1.连接建立
void EchoServer::onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << "has connected!!!" << endl;
}

//2.消息到达
void EchoServer::onMessage(const TcpConnectionPtr &con)
{
    //接收客户端的数据
    string msg = con->receive();
    cout << ">>recv msg from client: " << msg;

    MyTask task(msg, con);

    _pool.addTask(bind(&MyTask::process, task));
}

//3.连接断开
void EchoServer::onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << "has closed!!!" << endl;
}
