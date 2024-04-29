#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usgae : sleep <time>\n");
        return -1;
    }

    int time;
    time = atoi(argv[1]);
    sleep(time);
    exit(0);
}