#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int isprime(int x)
{
    if (x == 2)
        return 1;
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *agrv[])
{
    int nums[2];
    pipe(nums);

    if (fork() != 0)
    {
        // parents
        close(nums[0]);
        for (int i = 2; i <= 35; i++)
        {
            write(nums[1], &i, 4);
        }
        close(nums[1]);
        wait(0);
    }
    else
    {
        // son
        int num;
        close(nums[1]);
        while (read(nums[0], &num, 4) != 0)
        {
            if (isprime(num) == 1)
            {
                int prime[2];
                pipe(prime);
                if (fork() != 0)
                {
                    close(prime[0]);
                    write(prime[1], &num, 4);
                    close(prime[1]);
                    wait(0);
                }
                else
                {
                    // grandson
                    close(prime[1]);
                    int num2;
                    read(prime[0], &num2, 4);
                    printf("prime %d\n", num2);
                    close(prime[0]);
                    exit(0);
                }
            }
        }
    }
    exit(0);
}