#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int run(int p[2])
{
    close(p[1]);
    int num;
    int n = read(p[0], &num, 4);

    if (n == 0)
    {
        exit(0);
    }

    printf("prime %d\n", num);

    int new_pipe[2];
    pipe(new_pipe);

    if (fork() == 0)
    {
        run(new_pipe);
    }
    else
    {
        close(new_pipe[0]);
        int num2;
        while (read(p[0], &num2, 4) != 0)
        {
            if (num2 % num != 0)
            {
                write(new_pipe[1], &num2, 4);
            }
        }
        close(new_pipe[1]);
        close(p[0]);
        wait(0);
    }
    exit(0);
}

int main(int argc, char *agrv[])
{
    int _pipe[2];
    pipe(_pipe);

    if (fork() == 0)
    {
        run(_pipe);
    }
    else
    {
        close(_pipe[0]);
        for (int i = 2; i <= 35; i++)
        {
            write(_pipe[1], &i, 4);
        }
        close(_pipe[1]);
        wait(0);
    }
    exit(0);
}