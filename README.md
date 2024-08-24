# SearchEngine
搜索引擎项目 <br>


### 项目简介

服务器端基于`Linux` 平台、`C/C++`语言

该项目是一个用于网页查询的轻量级搜索引擎。实现了`处理网页`，`显示结果`等整个搜索引擎的流程。该项目分为三个阶段：**线下阶段**，**线上阶段**，**优化阶段**。**线下部分**使用`tinyxml2`解析爬取的网页，以此建立`网页库`，网页`偏移库`；再使用`cppjieba`分词库，`TopK算法`生成`指纹信息`作为`去重`标准并生成新的`网页库`与`网页偏移库`，去重后通过`TF-IDF算法`建立`倒排索引库`。**线上部分**则使用`EchoLib框架`搭建服务器，客户端发送查询词后，服务器计算`文本特征`并建立`VSM模型`，并使用`余弦相似度算法`匹配网页，将匹配的网页通过`余弦值`排序后使用`jsoncpp`封装后发送。**优化部分**则使用`mysql`作为网页存储的数据库，`redis`作为`Cache缓存`，`log4cpp`添加`日志系统`。

<br>


### 项目详细流程
该项目主要分为三个阶段：**线下阶段**，**线上阶段**，**优化阶段**。


* **线下阶段**

1. 首先使用**tinyxml2**解析python爬取的网页，将爬取的网页进行进行解析之后放入内存，再将内存中的网页**整理格式**之后，输出到磁盘，这也就时创建 **网页库** 与 **网页偏移库** 的过程。

2. 读取网页库与网页偏移库，使用 **cppjieba库** 对文章进行分词，再使用 **TopK算法** 计算出每一篇文章最高频的k个单词，以这k个单词作为该文章的 **指纹信息**， 这样可以达到对**文章去重**的效果。根据去重之后的 文章，建立 **新的网页库** 与 **新的网页偏移库**。

3. 使用 **TF-IDF** 算法建立 **倒排索引库**。

**补充**：

1. **TF-IDF算法**

该算法实质上是一种**计算权值**的算法，主要用于计算出每一个词在每一篇文章中所占的权值，也可以理解成某个单词在某个文章中的重要程度。

举例：
有很多不同的数学公式可以用来计算TF-IDF。这边的例子以上述的数学公式来计算。词频 (TF) 是一词语出现的次数除以该文件的总词语数。假如一篇文件的总词语数是100个，而词语“母牛”出现了3次，那么“母牛”一词在该文件中的词频就是3/100=0.03。一个计算文件频率 (IDF) 的方法是文件集里包含的文件总数除以测定有多少份文件出现过“母牛”一词。所以，如果“母牛”一词在1,000份文件出现过，而文件总数是10,000,000份的话，其逆向文件频率就是 lg(10,000,000 / 1,000)=4。最后的TF-IDF的分数为0.03 * 4=0.12。

计算过程较为复杂，详细可参考：
[百度百科：TF-IDF算法](https://baike.baidu.com/item/tf-idf/8816134)

2. **倒排索引**

倒排索引是**通过属性值来查找记录**。通常我们使用索引，是通过记录来查找属性，但是这样显然效率太低；于是倒排索引的出现帮助我们解决了效率的问题，因为它可以通过属性值找到对应的记录。

项目中建立的倒排索引：
 

```clike
unordered_map<string, vector<pair<int, double>>> _invertIndexTable; //倒排索引 <单词，<所在文档ID, 单词权重>>
```

[百度百科：倒排索引](https://baike.baidu.com/item/%E5%80%92%E6%8E%92%E7%B4%A2%E5%BC%95/11001569?fr=aladdin)

<br>


* **线上阶段**

采用**EchoLib**并发服务器框架，此时假设客户端发送查找 **如何成为大师级程序员** 相关的网页。

服务器的处理流程如下：

1.  将客户端发送的查询语句**看成一篇文章**，通过**TF-IDF**算法计算出各个单词在该篇文章中的权重。

2. 通过**倒排索引**，查找出**所有匹配的网页**。这里的匹配代表着该网页中包含客户端查询词中的所有关键词。

3. 使用 **余弦相似度算法** 计算出每一篇网页对应查询语句的余弦相似度，根据余弦相似度大小对网页进行排序。

4. 为每一篇网页都形成**摘要**。

5. 将文章封装成**json字符串**返回给客户端。

6. 客户端**解析json**字符串并显示。



<br>


* **优化阶段**

1. 使用**mysql**数据库来存储网页。

2. 使用**redis**来作为缓存cache。

3. **log4cpp**记录日志文件。


<br>



### Demo展示
![image](https://github.com/user-attachments/assets/bd633a76-bcef-49d7-a9b1-120f8f238797)
![image](https://github.com/user-attachments/assets/d9fb8ae5-06b9-41eb-9575-e7081b3f8898)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105174446463.gif#pic_center)


同时，在`VScode`的后台也记录了查询词，并且将其记录到了`日志文件`中，方便查看。
![在这里插入图片描述](https://img-blog.csdnimg.cn/202011051743412.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dvcnRoeV9XYW5n,size_16,color_FFFFFF,t_70#pic_center)


### 架构图
![image](https://github.com/user-attachments/assets/09c1885a-c0a2-4e25-8d06-1094f5cd1397)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200713090409283.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dvcnRoeV9XYW5n,size_16,color_FFFFFF,t_70)
<br>

### 技术亮点
#### 离线版本
1. 建立网页库与网页偏移库
技术亮点：`开源库tinyxml2(DFS遍历节点)`, `正则表达式`，`文件流字符串流操作`, `Unix目录操作`，`单例模式(饿汉)`
2. 网页去重
技术亮点: `开源库cppjieba分词`，`set停词集合`，`TopK算法(判断网页重复)`
3. 建立倒排索引
技术亮点：`unordered_map倒排哈希表`，`TF-IDF算法(计算权重)`



#### 在线部分
1. 搭建线程池框架
技术亮点：`基于对象线程池设计`，`Posix线程类，互斥锁，条件变量`，`任务队列`，`自动加解锁类`，`子线程安全退出机制`，`回调函数`，` 智能指针unique_ptr`
2. 搭建服务器框架
技术亮点：`基于对象服务器设计`，`回调函数`，`socket网络编程`，`IO多路复用epoll`，`eventfd(IO线程与计算线程分离)`，`客户端安全退出机制` ，`智能指针shared_ptr`
（前两步框架可直接使用博主的开源项目 [MirrorLib](https://github.com/Worthy-Wang/MirrorLib)）
3. 搭建搜索引擎框架
技术亮点：`文件流字符串流操作`，`TF-IDF算法`，`开源库log4cpp记录日志`，`余弦相似度算法`，`开源库jsoncpp`


#### 优化功能
1. 使用mysql作为网页存储的数据库
2. 使用redis作为Cache缓存

<br>

#### 算法详解
如果对于上述算法感觉不是很理解，可以看看这一篇文章：
[基于 K-means 算法实现的文本聚类（干货）](https://blog.csdn.net/qq_29110265/article/details/90769363)
