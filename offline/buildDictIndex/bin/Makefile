# 定义编译器
CXX = g++
CXXFLAGS = -g -std=c++11 -I../include -I../include/cppjieba -I../include/dict

# 定义目标文件和依赖
TARGET = buildDictIndex
SRCS = ../src/buildDict.cpp      \
	   ../src/DictProducer.cpp    \
	   ../src/SplitTool.cpp        \
	   ../src/SplitToolCppJieba.cpp \
	   ../src/DirScanner.cpp         \

OBJS = $(SRCS:.cpp=.o)
INCLUDES = ../include/Configuration.h  \
           ../include/DictProducer.h    \
           ../include/SplitTool.h        \
           ../include/SplitToolCppJieba.h \
		   ../include/DirScanner.h         \			

# 定义最终生成的可执行文件路径
BIN_DIR = .
TARGET_EXEC = $(BIN_DIR)/$(TARGET)

# 生成规则
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	$(MAKE) clean_objs  # 清理 .o 文件

# 生成.o文件规则
%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
.PHONY: clean clean_objs
clean: clean_objs
	rm -f $(TARGET_EXEC)

clean_objs:
	rm -f $(OBJS)
