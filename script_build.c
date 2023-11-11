#include <stdlib.h>
#include "crossplatform_app/script_helper.c"

#define WINDOWS_FLAGS ""

#ifdef WIN32
#define EXECUTABLE "main.exe"
#define PATH "windows"
#undef WINDOWS_FLAGS
#define WINDOWS_FLAGS "-subsystem,windows"
#endif

#if defined __APPLE__ || __linux__
#define EXECUTABLE "main"
#define PATH "osx"
#endif

int main()
{
    char path[256];
    get_cwd(path, 256);

    system("echo Attempting build...");
    set_cwd("general_purpose_graph");
    system("tcc script_build.c -run");
    set_cwd(path);
    system("tcc main.c general_purpose_graph/api.o -L./crossplatform_app/backend/SDL2/lib/x86 -lSDL2 -w -Wl,"WINDOWS_FLAGS" -o build/"PATH"/"EXECUTABLE);
    system("echo Done.");
}