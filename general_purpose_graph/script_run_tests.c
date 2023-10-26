#include <stdlib.h>

int main()
{
    system("echo Attempting build...");
    system("tcc api.c -c");
    system("echo Done.Running tests.");
    system("tcc tests.c api.o -run");
}