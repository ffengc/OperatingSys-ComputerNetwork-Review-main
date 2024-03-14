

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

// 输出重定向
#if 0
int main()
{
    close(1);
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC);
    assert(fd >= 0);
    printf("fd: %d\n", fd);
    printf("hello world!\n");
    fflush(stdout);
    close(fd);
    return 0;
}
#endif

// 输入重定向
#if 1 // bug
int main()
{
    close(0);
    int fd = open("log.txt", O_RDWR);
    assert(fd >= 0);
    char *buffer = (char *)malloc(sizeof(char) * 1000);
    memset(buffer, '\0', sizeof(buffer));
    scanf("%s", buffer); // 这里应该只有 "111", 因为scanf识别回车
    fflush(stdin);
    printf("fd: %d, %s\n", fd, buffer);
    close(fd);
    return 0;
}
#endif

// dup2
#if 0
int main()
{
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC);
    assert(fd >= 0);
    dup2(fd, 1);
    printf("%s\n", "hello world");
    return 0;
}
#endif

// 缓冲区
#if 0
int main()
{
    // C语言
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n");
    const char *s = "hello fputs\n";
    fputs(s, stdout);
    // 系统调用
    const char *ss = "hello write\n";
    write(1, ss, strlen(ss)); // 写到fd=1的文件上->stdout
    fork();
    return 0;
}
#endif