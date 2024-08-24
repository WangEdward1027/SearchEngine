#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include "./json.hpp"

#include <fstream>
#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
using namespace nlohmann;

using json = nlohmann::json;

//namespace se
//{
class ProtocolParser
{
public:
    struct res
    {
        int _id;
        vector<string> _content;
    };

    void addString(const string &str);
    //void readFile(const string filename);
    string doPack(int, vector<string>);
    string doPack(int, string);
    struct res doParse(const string &str);

private:
    json _j;
};

// void ProtocolParser::readFile(const string filename)
// {
//     ifstream ifs(filename, ifstream::in);
//     if (!ifs) {
//         cerr << "open file error" << endl;
//     }
//     ifs >> _j;
// }

// 将对象序列化为json格式 发送给客户端
string ProtocolParser::doPack(int id, vector<string> content)
{
    _j["id"] = id;
    _j["content"] = content;
    try
    {
        return _j.dump();
    }
    catch (nlohmann::detail::exception &e)
    {
        std::string ret = "{\"id\":-1,\"content\":[\"null\"]}";
        if (e.id == 316)
        {
            cout << "error id = 316" << endl;
        }
        cout << "error content : ";
        for (auto &text : content)
        {
            cout << text << endl;
        }
        return ret;
    }
}

string ProtocolParser::doPack(int id, string content)
{
    _j["id"] = id;
    _j["content"].push_back(content);

    try
    {
        return _j.dump();
    }
    catch (nlohmann::detail::exception &e)
    {
        std::string ret = "{\"id\":-1,\"content\":[\"null\"]}";
        if (e.id == 316)
        {
            cout << "error id = 316" << endl;
        }
        cout << "error content : " << content << endl;
        return ret;
    }
}

// 将json格式反序列化为对象
struct ProtocolParser::res ProtocolParser::doParse(const string &str)
{
    struct res tmp;
    json mp;

    string _str = str;
    try
    {
        mp = json::parse(str);
        tmp._id = mp.at("id").get<int>();

        for (auto &i : mp.at("content"))
        {
            tmp._content.push_back(i);
            // cout << "tmp.content " << tmp._content.back() << endl;
        }
    }
    catch (nlohmann::detail::exception &e)
    {
        cout << "error id = " << e.id << endl;
        cout << "content = " << str << endl;
        tmp._id = -1;
    }
    return tmp;
}

#endif