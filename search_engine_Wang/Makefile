#当前路径
CUR_DIR = .#$(shell pwd)
#中间文件存放路径
OBJ_DIR = $(CUR_DIR)/obj

#通常项
CC = g++
OUT = SEserver
FLAGS = -O3 -g -Wall -std=c++11 -pthread 


#源文件集合
LOG_PATH = $(CUR_DIR)/lib/easylogger

#addsuffix p1 p2 ：把p1接到p2后
C_SRCS = $(wildcard $(addsuffix /*.c,$(LOG_PATH)))
C_SRCS += $(wildcard $(addsuffix /*.c,$(LOG_PATH)/src))
C_SRCS += $(wildcard $(addsuffix /*.c,$(LOG_PATH)/port))
C_SRCS += $(wildcard $(addsuffix /*.c,$(LOG_PATH)/plugins/file))

SERVER_PATH = $(CUR_DIR)/src

CPP_SRCS = $(wildcard $(addsuffix /*.cc,$(SERVER_PATH)))
CPP_SRCS += $(wildcard $(addsuffix /*.cc,$(SERVER_PATH)/Reactor))
CPP_SRCS += $(wildcard $(addsuffix /*.cc,$(SERVER_PATH)/Cache))
CPP_SRCS += $(wildcard $(addsuffix /*.cc,$(SERVER_PATH)/keyRecommand))
CPP_SRCS += $(wildcard $(addsuffix /*.cc,$(SERVER_PATH)/WebPageQuery))
CPP_SRCS += $(wildcard $(addsuffix /*.cc,$(SERVER_PATH)/OnlineServer))

#中间文件集合
# notdir ：除去文件名前的地址信息
# basename ：除去后缀名
# addprefix p1 p2 ： 把p1接到p2前 
OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(basename $(notdir $(CPP_SRCS)))))
OBJS += $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(basename $(notdir $(C_SRCS)))))

#头文件集合
INC_DIR  =  ./lib/easylogger/inc ./lib/easylogger/plugins/file
INC_DIR  += ./lib/easylogger/plugins/port
INC_DIR  += ./include/ 	./include/Cache 
INC_DIR  += ./include/OnlineServer ./include/proparse 
INC_DIR  += ./include/PageLib  ./include/keyRecommand
INC_DIR  += ./src/Reactor

INC = $(addprefix -I,$(INC_DIR))

#源文件搜索路径集合
C_DIR = $(LOG_PATH) $(LOG_PATH)/src \
		$(LOG_PATH)/port $(LOG_PATH)/plugins/file

CPP_DIR = $(SERVER_PATH) $(SERVER_PATH)/OnlineServer \
		  $(SERVER_PATH)/Reactor $(SERVER_PATH)/Cache \
		  $(SERVER_PATH)/keyRecommand \
		  $(SERVER_PATH)/WebPageQuery

#搜索路径
vpath
vpath %.c $(C_DIR)
vpath %.cc $(CPP_DIR)
vpath %.h $(INC_DIR)
vpath %.o $(OBJ_DIR)

ALL:$(OUT)

$(OUT):$(notdir $(OBJS))
	$(CC) $(OBJ_DIR)/*.o $(FLAGS) $(INC) -o $(OUT) 

%.o:%.c
	@cc $< -g -Wall  $(INC) -c -o $(OBJ_DIR)/$@ 

%.o:%.cc
	@$(CC) $< $(FLAGS) $(INC) -c -o $(OBJ_DIR)/$@ 


.PHONY:clean rebuild
clean:
	rm -f $(OUT) $(OBJ_DIR)/*.o

rebuild:clean ALL

