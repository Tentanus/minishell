#include <unistd.h>
#include <stdlib.h>

void f(void)
{
	system("leaks a.out");
}

int    main(void)
{
    int pid;

	atexit(f);
    pid = fork();
    return (0);
}