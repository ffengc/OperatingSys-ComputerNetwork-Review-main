
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#if false
int main()
{
    while(1)
    {
        std::cout << "hello linux" << std::endl;
        sleep(1);
    }
    return 0;
}
#endif

#if false
int main()
{
    std::cout << "hello world" << std::endl;
    fork();
    std::cout << "you can see me" << std::endl;
    return 0;
}
#endif

#if false
int main()
{
    while (1)
    {
        // std::cout << "hello world" << std::endl;
        ;
    }
    return 0;
}
#endif

// 获取环境变量
#if false
int main(int argc, char *argv[], char *env[])
{
#if false
    std::cout << "begin ..." << std::endl;
    for(int i = 0; env[i]; i++)
    {
        // 遍历这个数组
        std::cout << "env[" << i << "]: " << env[i] << std::endl;
    }
#endif
    std::cout << "begin ... " << std::endl;
    std::cout << getenv("PATH") << std::endl;
    return 0;
}
#endif

// 验证地址空间的栈结构
int g_unval;     // 未初始化的全局变量
int g_val = 100; // 已经初始化的全局变量
int main(int argc, char *argv[], char *env[])
{
    printf("code addr: %p\n", main);              // 代码块位置
    printf("init global addr: %p\n", &g_val);     // 初始化全局变量
    printf("uninit global addr: %p\n", &g_unval); // 未初始化全局变量

    char *heap_memory = (char *)malloc(10);
    printf("heap addr: %p\n", heap_memory); // 堆上的空间

    printf("stack addr: %p\n", &heap_memory); // 栈上的空间

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %p\n", i, argv[i]);
    }
    for (int i = 0; env[i]; i++)
    {
        printf("env[%d]: %p\n", i, env[i]);
    }
    return 0;
}