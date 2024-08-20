//打开目录流opendir，关闭目录流closedir,读取目录流 readir
//使用 readdir 函数读取并打印某目录中的所有 文件名 和 目录名 (暂时不会递归遍历目录)

#include <stdio.h>
#include <dirent.h>
#include <error.h>
#include <errno.h>
#include <string.h>

int main() {
    //定义并初始化路径
    const char path[] = "../cutWor/dict";

    // 打开目录
    DIR* dir = opendir(path);
    if(dir == NULL){
    	error(1, errno, "opendir %s", path);  //使用errno来获取错误信息
    }

    // 读取目录中的每一项
    struct dirent* entry;
    while((entry = readdir(dir)) != NULL){
        //过滤 . 和 ..
        if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
            continue;
        //打印文件名 或 目录名
        printf("%s\n", entry->d_name);
    }

    // 关闭目录
    closedir(dir);

    return 0;
}
