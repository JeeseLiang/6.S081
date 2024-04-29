#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

char *add(char *dest, const char *src)
{
    char *temp = dest;
    while (*temp != '\0')
    {
        temp++;
    }
    while ((*temp++ = *src++) != '\0')
        ;
    return dest;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > MAXARG)
    {
        printf("argc = %d, arguments too many or too few\n", argc);
        for (int i = 0; i < argc; i++)
        {
            printf("argv[%d] :%s\n", i, argv[i]);
        }
        exit(-1);
    }

    char *args[MAXARG];
    char buf[512];
    int len = 0;

    for (int i = 1; i < argc; i++)
    {
        args[i - 1] = argv[i];
    }

    while (1)
    {
        char c;
        if (read(0, &c, 1) == 0)
        {
            if (len != 0)
            {
                buf[len] = '\0';
                args[argc - 1] = buf;
                args[argc] = 0;
                if (fork() == 0)
                {
                    exec(args[0], args);
                    exit(-1);
                }
                else
                {
                    wait(0);
                }
            }
            break;
        }

        if (c == '\n')
        {
            buf[len] = '\0';
            args[argc - 1] = buf;
            args[argc] = 0;

            if (fork() == 0)
            {
                exec(args[0], args);
                exit(0);
            }
            else
            {
                wait(0);
            }
            len = 0; // Reset buffer index for next line
        }
        else
        {
            buf[len] = c;
            len++;
        }
    }

    exit(0);
}
