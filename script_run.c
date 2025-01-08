#include <stdlib.h>
#include "../crossplatform_app/script_helper.c"
#include "app_configuration.c"

int main()
{
    #define START ""
    #ifdef _WIN32
        #undef START
        #define START "start"
    #endif

    #ifdef RELEASE
    system(START" ./build/" EXECUTABLE);
    #else
    system("gdb -q ./build/" EXECUTABLE);
    #endif
}