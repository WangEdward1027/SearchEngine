#include "../../include/PageLib/FileProcessor.hpp"
#include <regex>
#include <iostream>

using std::cerr;
using std::endl;
using std::cout;
using std::make_pair;


/* using namespace tinyxml2; */

namespace se
{

FileProcessor::NetXML FileProcessor::process(const string &FilePath,int &docidN,int &offsetN)
{
    cout << "FilePath" << FilePath << endl;
    NetXML netlib;
    //获取结点
    XMLDocument doc;
    //读取xml文件
    doc.LoadFile(FilePath.c_str());
    if(doc.ErrorID())
    {
        //判断xml文件状态
        std::cerr << "loadFile fail" << endl;
        abort();
    }
    //获取一个item的结点
    XMLElement *itemNode = doc.FirstChildElement("rss")
        ->FirstChildElement("channel")->FirstChildElement("item");

    //遍历结点
    while(itemNode)
    {
        int docSizeN = 0;
        string title = itemNode->FirstChildElement("title")->GetText();
        string url=  itemNode->FirstChildElement("link")->GetText();
        string description = itemNode->FirstChildElement("description")->GetText();

        std::regex reg("<[^>]+>");//通用正则表达式
        title= regex_replace(title, reg, "");
        description = regex_replace(description, reg, "");

        //按照格式拼接一篇网页
        string fmtTxt = "<doc><docid>";
        string docidS = std::to_string(docidN);
        fmtTxt.append(docidS).append("</docid><url>")
            .append(url).append("</url><title>")
            .append(title).append("</title><content>")
            .append(description).append("</content></doc>");
        docSizeN = fmtTxt.size();

        netlib._page.push_back(fmtTxt);

        string offset;
        string offsetS = std::to_string(offsetN);
        string docSizeS = std::to_string(docSizeN);
        offset.append(docidS).append("  ")
            .append(offsetS).append("  ")
            .append(docSizeS);
        netlib._offsetString.push_back(offset);

        netlib._offset.insert(make_pair(docidN,make_pair(offsetN,docSizeN)));

        itemNode = itemNode->NextSiblingElement("item");
        ++docidN;
        offsetN += docSizeN;
        ++offsetN;
    }
    return netlib;
}

}// end of namespace se
