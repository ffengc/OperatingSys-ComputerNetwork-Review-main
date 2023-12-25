
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// 复习C语言文件接口
#if false
int main()
{
    FILE *fp = fopen("log.txt", "w");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    // 文件操作
    while(true)
    {
        sleep(1);
    }
    fclose(fp);
    return 0;
}
#endif

// 模拟实现一个cat命令
#if false
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("args error!\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r"); // 打开这个文件
    if (fp == NULL)
    {
        perror("fopen");
        return 2;
    }
    // 读取文件里面的内容
    char line[64];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        fprintf(stdout, "%s", line);
    }
    fclose(fp);
    return 0;
}
#endif

// 系统调用
#if false
int main()
{
    int fd = open("log.txt", O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    printf("open success, fd: %d\n", fd);
    return 0;
}
#endif

#if false
int main()
{
    umask(0);
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    printf("open success, fd: %d\n", fd);

    const char *s = "aa\n";
    write(fd, s, strlen(s));
    close(fd);
    return 0;
}
#endif


// 文件描述符和FILE*
int main()
{
    printf("stdin: %d\n", stdin->_fileno);
    printf("stdout: %d\n", stdout->_fileno);
    printf("stderr: %d\n", stderr->_fileno);
    return 0;
}