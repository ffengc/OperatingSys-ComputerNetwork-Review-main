

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

int main()
{
    // C
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n");
    perror("hello perror"); // stderr
    // 系统调用
    const char* s1 = "hello write(stdout)\n";
    const char* s2 = "hello write(stderr)\n";
    write(1, s1, strlen(s1));
    write(2, s2, strlen(s2));
    // C++
    std::cout << "hello cout" << std::endl;
    std::cerr << "hello cerr" << std::endl;
    return 0;
}