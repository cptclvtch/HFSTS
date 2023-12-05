#include "api.c"

#define PRINT_FN printf
#include "../unit_testing.c"

int main()
{
    data_buffer* temp_buffer;

    #define TITLE "Data buffers"
    TEST_PRINT(TITLE"\n")

    #define SUBTITLE "Buffer allocation - Best case scenario"
    temp_buffer = create_data_buffer(temp_buffer);

    VERIFY_SINGLE_VALUE(data_buffer,!=,NULL)
    COLLECT_FINDINGS

    ADD_SEPARATOR

    DEBRIEF
}