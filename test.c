#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void    *nul_guard(void *malloc)
{
    if (!malloc)
        exit (errno);
    return (malloc);
}

int main(int argc, char **argv, char **envp)
{
    char *str;

    for(int i = 0; i < 10000; i++)
    {
        str = nul_guard(malloc(1024 * 1024 * 1024 * 1000L));
        printf("%d\n", i);
    }
}