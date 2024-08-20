//递归遍历目录

#include <stdio.h>
#include <dirent.h>
#include <error.h>
#include <errno.h>
#include <string.h>

void traverse(const char * path)
{
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
        
        //递归遍历目录
        if(entry->d_type == DT_DIR){  //是目录
            char subpath[1024];
            snprintf(subpath, sizeof(subpath), "%s/%s", path, entry->d_name);
            traverse(subpath);
        }else{ //是文件
            printf("%s\n", entry->d_name); //打印文件名 或 目录名
        }
    }

    // 关闭目录
    closedir(dir);
}

int main() {
    traverse("../cutWord/dict");
    return 0;
}
