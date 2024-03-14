

#include <iostream>
#include <string>
#include <signal.h>
#include <unistd.h>

static void Usage(std::string proc)
{
    std::cout << "Usage:\r\n\t" << proc << "signumber processid" << std::endl;
}
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    int signumber = atoi(argv[1]);
    int procid = atoi(argv[2]);
    kill(procid, signumber);
    return 0;
}