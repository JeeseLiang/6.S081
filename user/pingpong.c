#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("usage : pingpong\n");
        return -1;
    }
    // 0 : read , 1 : write
    int fa[2], son[2];
    pipe(fa);
    pipe(son);
    int pid = fork();

    if (pid == 0)
    {
        // 子进程
        char c;
        read(fa[0], &c, 1);
        printf("%d: received ping\n", getpid());
        write(son[1], "-", 1);
    }
    else
    {
        // 父进程
        char c;
        write(fa[1], "+", 1);
        read(son[0], &c, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
    }
    exit(0);
}