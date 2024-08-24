#include "../../include/offline1/DictProducer.hpp"
#include "../../include/offline2/PageLibPreprocessor.hpp"

#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::fstream;
using std::ofstream;
using std::stringstream;

namespace se
{
    DictProducer::DictProducer(PageLibPreProcessor *pagelib)
        : _pagelib(pagelib),
          _tool(nullptr),
          _dict(),
          _dict_index(),
          _index()
    {
        buildEnDict();
        createIndex();
    }
    DictProducer::DictProducer(PageLibPreProcessor *pagelib, SplitTool *tool)
        : _pagelib(pagelib),
          _tool(tool),
          _dict(),
          _dict_index(),
          _index()
    {
        cout << "in DictProducer::DictProducer(PageLibPreProcessor *pagelib, SplitTool *tool)" << endl;
        buildCnDict();
        cout << "after buildCnDict();" << endl;
        createIndex();
        cout << "after createIndex();" << endl;
        //showDict();
        cout << "after showDict();" << endl;
    }

    //for test
    /* DictProducer::DictProducer()
        : //_pagelib(pagelib),
          article("a English string"),
          _tool(nullptr),
          _dict(),
          _dict_index(),
          _index()
    {
        buildEnDict();
        createIndex();
    }
    DictProducer::DictProducer(SplitTool *tool)
        : //_pagelib(pagelib),
          article("青记独家丨忆两次重大采访中的丁钢 【导读】与老丁一起的两次共同采访，时间虽短暂，但他的言传身教让我记忆犹新。  丁钢是中国青年报社原国内部的老主任。我在中国青年报工作20多年，诸多的人和事定格我的记忆。丁钢就是其中的一位。  就职中国青年报社，特别是做报社机动记者那段时间，我与丁钢主任交集甚多。老丁一家除小儿子外都是新闻人，他和夫人郭梅尼、女儿郭蓝燕三人都担任过中国青年报社记者部的主任，被中国新闻界传为佳话。老丁调入中国青年报社编辑部之前，在东北、江浙、上海等地做过地方记者，穿行滇藏边界，翻越唐古拉山，报道中印自卫反击战，就读中国人民大学新闻系，丰富的新闻从业经历造就了他敏锐的新闻敏感，使他成为中国青年报社最擅长组织重大新闻战役的一线领导组织者。在见证中国经济体制改革的过程中，我对几十位来自各条战线青年改革人物的采访，参与的十余次全国人大政协两会、中国共产党全国代表大会、国庆阅兵等重大政治新闻报道，都是在他的指挥下成功完成的。     作者（左一）在中国青年报60年社庆时与丁钢（左二）郭梅尼（右一）夫妇的合影。   1983年我与老丁经历的两次采访——沈阳“296劫机事件”和全国两会上廖承志突然逝世的追踪报道。让我对记者应具备的新闻敏感和应该担当的责任有了更为直接和深刻的理解。  （一）  1983年，5月5日上午，卓长仁等6人持枪劫持了沈阳飞往上海的民航296航班。一百多名乘客和机组人员被劫持，飞机落在当时的南朝鲜春川机场。  无论在哪一个国家，发生劫机都是重大事件，其中必有重大幕后新闻。我一时拿不准报社是否会同意对这种突发性重大敏感新闻事件进行采访和报道，迅速接通了老丁的电话。  老丁让我等他回复。他动作很快，不一会儿我就接到回电。他联系了国家民航局，但情况非常复杂，那边不同意采访报道。老丁说：“役军，这件事从哪一个角度看都是大新闻，你可以进行些基础性采访，把事件的来龙去脉搞清楚，下一步看事态的进展再定夺。”  我立即行动，第一时间赶到沈阳某单位，一下插到该单位保卫处进行采访，成为国内外第一个对此采访的记者。保卫处是破译“296劫机事件”内幕的突破口，被带上296航班的几支手枪，都来自这里。  采访顺利，我获得了许多人至今都没得到的第一手资料。这给我了一个重要启示：记者采访突发性重大新闻，必须立即行动，先下手为强。但就在采访结束几小时后，我接到被采访人的电话，不同意被采访内容被报道。  劫机事件后，争夺与反争夺的暗战，在安置着一百多名乘客的酒店里以各种各样的方式展开。乘客中党团员发挥了稳定人心的作用。  老丁得知情况后马上打电话，说要尽可能采访296航班乘客中的代表人物。他立即从北京赶到沈阳，和我马不停蹄，夜以继日采访。  （二）  作为中国青年报社机动记者、特派记者，我曾南下太平洋，报道中国卫星发射的曲折过程。曾跨过罗湖桥，探寻中国涉外婚姻的悲欢奥秘。我在中青报所撰写发表的文章，包含着老丁和其他编辑同志的心血。老丁曾经对我说：你们是新闻捕手，我就是“油漆工”，会让你们的文章在报纸上光鲜亮丽。  老丁是一个耿直、率真的人，说话办事直来直去，不磨叽，不拐弯抹角。记得有一年我从地方记者站抽调回国内部值班，部门里人员生病的生病，出差的出差，老丁又要外出参会，就剩下我一个人。正当我忐忑不安时，老丁说：“这里你都熟悉了，只管干。大事给我打电话，稳当点不会有问题。”  我和老丁另一次共同采访，是六届全国人大一次会议。会议于1983年6月6日至21日在北京举行。6月10日上午，我突然得到廖承志当日凌晨去世的消息。老丁说：“你马上核实，消息确认，应立即追踪采访。”这不仅因为廖公是即将诞生的新一届国家领导人中副主席人选，还因为他曾担任过团中央的副书记和全国青联主席。  随后，老丁和我一起研究制定追踪报道廖公逝世的方案，进行采访。  当我和老丁走进荣高棠老人的家的时候，他正在桌前翻看照片，荣老拿着廖公和毛主席、朱总司令合影的照片让我们看。他说，1949年四五月份，他和廖公、冯文斌、蒋南翔等人一起筹备全国团代会和全国青联大会。会上，冯文斌当选团中央书记，廖公当选团中央副书记、全国青联主席，荣老当选团中央秘书长。当时廖公是中央委员，冯文斌不是。但廖公不计较这些，积极配合冯文斌的工作。荣老说廖公对党忠诚，谦虚谨慎，平易近人，一天到晚总乐呵呵的。乐观的人应长寿，没想到他走得这么早。  林丽韫曾担任全国妇联副主任、全国台联主席。六届人大一次会议，她是台湾代表团团长兼任大会执行主席。晚上，我们赶到她的驻地。提起廖公，她非常难过，声音嘶哑：廖公走得太突然，大家都没想到。  林丽韫第一次见廖公是1953年。她和父亲一起参加日本华侨护送抗日烈士骨灰回国团，廖公与护送团全体成员一起座谈。中日友好这条路走得非常艰难，廖公和许多人一起，推动民间外交，打破壁垒，实现了中日邦交的正常化，为改革开放打开一扇门。  对林丽韫的专访见报后，新华社当天向国内外播发了《中国青年报》这篇专访。  与老丁一起的两次共同采访，时间虽短暂，但他的言传身教让我记忆犹新。中青报岁月，如一座时光丰碑。2018年底，84岁的老丁辞世西行，而对老丁的记忆，在我诸多记忆中凸显其位。他黝黑的时而严肃酷如包公，时而快乐笑纹荡漾的脸总浮现我眼前，随和时叫我声“小马”，严肃起来即称“役军同志”，还真叫人心里放不下……   （作者曾任《中国青年报》副总编辑，《中国改革报》社长兼总编辑）"),
          _tool(tool),
          _dict(),
          _dict_index(),
          _index()
    {

        buildCnDict();
        //showDict();
        createIndex();
        //showIndex();
    } */

    void DictProducer::showDict()
    {
        for (auto &it : _dict)
        {
            cout << it.first << " " << it.second << endl;
        }
    }

    void DictProducer::showIndex()
    {
        for (auto &it : _index)
        {
            cout << it.first << " " << it.second << endl;
        }
    }

    void DictProducer::buildEnDict()
    {
        stringstream instr;
        string word, in_word;

        unordered_set<string> stop_words;
        Configuration *config1 = Configuration::getInstance();
        stop_words = config1->getStopWordList();

        vector<WebPage> articles = _pagelib->getPageList();

        for (auto &it : articles)
        {
            instr.flush();
            instr << it.getDocContent();
            //for test
            //instr << article;
            while (instr >> word)
            {
                in_word.clear();
                for (char c : word)
                {
                    //去大写
                    if (c >= 'A' || c <= 'Z')
                    {
                        c += 32;
                    }
                    //去符号
                    if (isalpha(c) || c == '-')
                    {
                        in_word += c;
                    }
                }

                //查停用词表
                auto if_stop = stop_words.find(in_word);
                if (if_stop != stop_words.end())
                {
                    continue;
                }
                else
                {
                    //在unorderd_map里找，插入vector和unorderd_map
                    auto exist = _dict_index.find(in_word);
                    if (exist != _dict_index.end())
                    {
                        ++(_dict[exist->second].second);
                    }
                    else
                    {
                        _dict.push_back(pair<string, int>(in_word, 1));
                        _dict_index.insert(pair<string, int>(in_word, _dict.size()));
                    }
                }
            }
        }
    }

    void DictProducer::buildCnDict()
    {
        vector<WebPage> articles = _pagelib->getPageList();

        //cout << "........................" << endl;
        //cout << articles.size() << endl;

        for (auto &it : articles)
        {
            string sentence = it.getDocContent();

            //string sentence = article;
            vector<string> words = _tool->cut(sentence);

            for (auto &v_it : words)
            {
                auto exist = _dict_index.find(v_it);
                if (exist != _dict_index.end())
                {
                    ++(_dict[exist->second].second);
                }
                else
                {
                    _dict.push_back(pair<string, int>(v_it, 1));
                    _dict_index.insert(pair<string, int>(v_it, _dict.size()));
                }
            }
        }
    }
#if 0
    void DictProducer::createIndex()
    {
        string letter;
        int index = 0;
        //tool是nullptr是英文，否则是中文
        if (_tool == nullptr)
        //英文
        {
            for (auto &it : _dict)
            {
                //拆分字母
                for (char c : it.first)
                {
                    letter = c;
                    auto map_it = _index.find(letter);
                    if (map_it != _index.end())
                    {
                        map_it->second.insert(index);
                    }
                    else
                    {
                        set<int> nset;
                        nset.insert(index);
                        _index.insert(pair<string, set<int>>(letter, nset));
                    }
                }
                ++index;
            }
        }
        else
        //中文
        {
            for (auto &it : _dict)
            {
                //汉字三个字节
                for (int i = 0; i < it.first.size(); i = i + 3)
                {
                    letter = it.first.substr(i, i + 3);
                    //for test
                    cout << letter << endl;

                    auto map_it = _index.find(letter);
                    if (map_it != _index.end())
                    {
                        map_it->second.insert(index);
                    }
                    else
                    {
                        set<int> nset;
                        nset.insert(index);
                        _index.insert(pair<string, set<int>>(letter, nset));
                    }
                }
                ++index;
            }
        }
    }
#endif

#if 1
    void DictProducer::createIndex()
    {
        string letter;
        int index = 0;

        //英文
        if (_tool == nullptr)
        {
            for (auto &it : _dict)
            {
                //拆分字母
                for (char c : it.first)
                {
                    letter = c;
                    auto map_it = _index.find(letter);
                    if (map_it != _index.end())
                    {
                        map_it->second.insert(index);
                    }
                    else
                    {
                        set<int> nset;
                        nset.insert(index);
                        _index.insert(pair<string, set<int>>(letter, nset));
                    }
                }
                ++index;
            }
        }
        else
        //中文中可能混英文
        {
            //cout << "in DictProducer::createIndex() for CN" << endl;
            for (auto &it : _dict)
            {
                int i = 0;
                //拆汉字
                while (i < it.first.size())
                {
                    //编码中开头只有一个1，是英文，英文符号，数字
                    unsigned char c = it.first[i];
                    if (c < 128)
                    {
                        ++i;
                        //cout << "c: it's <128" << endl;
                        continue;
                    }
                    //取得单个汉字共多少字节
                    int cnt = 1;
                    for (cnt; cnt < 6; ++cnt)
                    {
                        unsigned char b = c << cnt;
                        if (b < 128)
                        {
                            break;
                        }
                    }
                    letter = it.first.substr(i, cnt);
                    i += cnt;

                    /* size_t cnt = 1;
                    int N = 6;
                    if(c&(1<<7))
                    {
                        while (it.first[i] & (1 << N)!=0)
                        {
                            ++cnt;
                            --N;
                        }
                    }
                    
                    letter = it.first.substr(i, i + cnt);
                    i += cnt; */

                    /* int cnt = 1;
                    if (it.first[i] & 0x80)
                    {
                        char tmp = it.first[i];
                        tmp <<= 1;
                        do
                        {
                            tmp <<= 1;
                            ++cnt;
                        } while (tmp & 0x80);
                    }
                    letter = it.first.substr(i, i + cnt);
                    i += cnt; */

                    //for test
                    //cout << letter << endl;

                    auto map_it = _index.find(letter);
                    if (map_it != _index.end())
                    {
                        map_it->second.insert(index);
                    }
                    else
                    {
                        set<int> nset;
                        nset.insert(index);
                        _index.insert(pair<string, set<int>>(letter, nset));
                    }
                }
                ++index; //vector下标
            }
        }
    }
#endif
    void DictProducer::storeDict(const char *path)
    {
        ofstream wfile(path);
        if (!wfile.good())
        {
            cout << "error:DictProducer::storeDict(const char *path)" << endl;
            return;
        }
        for (auto &it : _dict)
        {
            wfile << it.first << "  " << it.second << endl;
        }
        wfile.close();
    }

    void DictProducer::storeIndex(const char *path)
    {
        ofstream wfile(path);
        if (!wfile.good())
        {
            cout << "error:DictProducer::storeIndex(const char *path)" << endl;
            return;
        }
        for (auto &it : _index)
        {
            wfile << it.first << "  ";
            for (auto &set_it : it.second)
            {
                wfile << set_it << " ";
            }
            wfile << endl;
        }
        wfile.close();
    }
}