#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    char *arg[] = {"echo", "-n", "hello", NULL};
    execve("/bin/echo", arg, envp);
}