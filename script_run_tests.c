#include <stdlib.h>
#include "crossplatform_app/script_helper.c"

int main()
{    
    uint8_t number_of_directories = 2;
    char* api_directories[number_of_directories];

    api_directories[0] = "flexible_format";
    api_directories[1] = "general_purpose_graph";

    uint8_t i = 0;
    for(; i < number_of_directories; i++)
    {
        set_cwd(api_directories[i]);
        system("tcc script_tests.c -run");
        set_cwd("..");
    }
}