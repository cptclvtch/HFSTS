#include <stdlib.h>
#include "script_helper.c"

int main()
{
    system("echo Attempting general_purpose_graph compilation...");
    // set_cwd("../flexible_format");
    // system("tcc script_build.c -run");
    system("tcc api.c -c");
    system("echo Done.");
}