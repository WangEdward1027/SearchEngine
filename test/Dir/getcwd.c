//获取当前工作路径

#include <unistd.h>
#include <stdio.h>

int main()
{
    char path[256];
    if(getcwd(path, sizeof(path)) != NULL){
        printf("Current working directory: %s\n", path);
    }else{
        perror("getcwd() error");
        return 1;
    }
    return 0;
}
