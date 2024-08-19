# 定义编译器
CXX = g++
CXXFLAGS = -g -std=c++11 -I../include -I../include/cppjieba -I../include/dict

# 定义目标文件和依赖
TARGET = buildDictIndex
SRCS = ../src/buildDict.cpp ../src/DictProducer.cpp ../src/SplitTool.cpp ../src/SplitToolCppJieba.cpp
OBJS = $(SRCS:.cpp=.o)
INCLUDES = ../include/Configuration.h \
           ../include/DictProducer.h \
           ../include/SplitTool.h \
           ../include/SplitToolCppJieba.h \
           ../include/cppjieba/DictTrie.hpp \   
           # ../include/dict/yyy.h         # 根据实际情况替换为dict目录中的具体头文件

# 定义最终生成的可执行文件路径
BIN_DIR = .
TARGET_EXEC = $(BIN_DIR)/$(TARGET)

# 生成规则
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 生成.o文件规则
%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理规则
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET_EXEC)

