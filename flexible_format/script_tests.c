#include "api.c"

#define PRINT_FN printf
#include "../unit_testing.c"

int main()
{
    uint8_t result;
    uint8_t temp_a,temp_b;

    format* temp_format;
    data_buffer* temp_buffer;

    #define TITLE "Formats"
    TEST_PRINT(TITLE"\n")

    #define SUBTITLE "Allocation - Best case scenario"
    temp_format = create_format();
    VERIFY_SINGLE_VALUE(temp_format,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_format->specifiers,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_format->current_index,==,0);
    VERIFY_SINGLE_VALUE(temp_format->max_index,==,INITIAL_FORMAT_SIZE-1);
    VERIFY_SINGLE_VALUE(temp_format->size,==,0);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding specifiers - No format specified"
    result = add_new_format_specifier(NULL, 0,0);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_ERROR_NO_FORMAT);
    VERIFY_SINGLE_VALUE(temp_format,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_format->specifiers,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_format->current_index,==,0);
    VERIFY_SINGLE_VALUE(temp_format->max_index,==,INITIAL_FORMAT_SIZE-1);
    VERIFY_SINGLE_VALUE(temp_format->size,==,0);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding specifiers - Unrecognized specifier"
    result = add_new_format_specifier(temp_format, -1,0);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_ERROR_UNRECOGNIZED_SPECIFIER);
    VERIFY_SINGLE_VALUE(temp_format,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_format->specifiers,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_format->current_index,==,0);
    VERIFY_SINGLE_VALUE(temp_format->max_index,==,INITIAL_FORMAT_SIZE-1);
    VERIFY_SINGLE_VALUE(temp_format->size,==,0);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding specifiers - Best case scenario"
    result = add_new_format_specifier(temp_format, INT8_T, 0);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_NO_ERROR);
    VERIFY_SINGLE_VALUE(temp_format->current_index,==,1);
    VERIFY_SINGLE_VALUE(temp_format->size,==,specifier_format_sizes[INT8_T]);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding specifiers - All basic specifier types"
    TEST_PRINT();
    uint8_t i = 1;
    
    for(;i <= UINT32_T; i++)
    {
        temp_a = temp_format->size;
        temp_b = temp_format->current_index;
        result = add_new_format_specifier(temp_format, i, 0);
        VERIFY_SINGLE_VALUE(result,==,FORMAT_NO_ERROR);
        VERIFY_SINGLE_VALUE(temp_format->current_index,==,temp_b + 1 + specifier_takes_argument(i));
        VERIFY_SINGLE_VALUE(temp_format->size,==,temp_a + specifier_format_sizes[i]);
        COLLECT_FINDINGS
    }
    
    // #undef SUBTITLE
    // #define SUBTITLE "Adding specifiers - ANOTHER_FORMAT"
    // temp_a = temp_format->current_index;
    // temp_b = temp_format->size;
    // result = add_new_format_specifier(temp_format, ANOTHER_FORMAT, 0);
    // VERIFY_SINGLE_VALUE(result,==,FORMAT_NO_ERROR);
    // VERIFY_SINGLE_VALUE(temp_format->current_index,==,temp_a + 1 + specifier_takes_argument(ANOTHER_FORMAT));
    // VERIFY_SINGLE_VALUE(temp_format->size,==,temp_b + specifier_format_sizes[ANOTHER_FORMAT]);
    // COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding specifiers - Memory expansion"
    for(i = INITIAL_FORMAT_SIZE - temp_format->current_index; i > 0; i--)
        result |= add_new_format_specifier(temp_format, UINT8_T, 0);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_NO_ERROR);
    VERIFY_SINGLE_VALUE(temp_format->max_index,==,(INITIAL_FORMAT_SIZE-1)*2);
    VERIFY_SINGLE_VALUE(temp_format->current_index,==,INITIAL_FORMAT_SIZE);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No format specified"
    result = free_format(NULL);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_ERROR_NO_FORMAT);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - Best case scenario"
    result = free_format(temp_format);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_NO_ERROR);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No format specified"
    result = free_format(NULL);
    VERIFY_SINGLE_VALUE(result,==,FORMAT_ERROR_NO_FORMAT);
    COLLECT_FINDINGS

    ADD_SEPARATOR
    #undef TITLE
    #define TITLE "Data buffers"
    TEST_PRINT(TITLE"\n")

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No buffer specified"
    result = free_data_buffer(NULL);
    VERIFY_SINGLE_VALUE(result,==,DATA_ERROR_NO_BUFFER);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Allocation - Best case scenario"
    temp_buffer = create_data_buffer();
    VERIFY_SINGLE_VALUE(temp_buffer,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_buffer->chunks,!=,NULL);
    VERIFY_SINGLE_VALUE(temp_buffer->associated_format,==,NULL);
    VERIFY_SINGLE_VALUE(temp_buffer->max_chunk_data_index,==,DEFAULT_MAX_CHUNK_DATA_INDEX);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Chunk addition - Best case scenario"
    
    COLLECT_FINDINGS

    // #undef SUBTITLE
    // #define SUBTITLE "Adding chunks - NULL input"
    // temp_buffer = create_data_buffer(NULL);
    // VERIFY_SINGLE_VALUE(temp_buffer,==,NULL);
    // COLLECT_FINDINGS

    ADD_SEPARATOR

    DEBRIEF
}