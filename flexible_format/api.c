#include "api.h"

#define INITIAL_FORMAT_SIZE 64
format* create_format()
{
    format* new_format = (format*)realloc(NULL, sizeof(format));

    new_format->specifiers = (uint32_t*)realloc(NULL, sizeof(uint32_t)*INITIAL_FORMAT_SIZE);
    new_format->current_index = 0;
    new_format->max_index = INITIAL_FORMAT_SIZE-1;

    new_format->size = 0;

    return new_format;
}

uint8_t specifier_format_sizes[] = 
{
    1, //INT8_T
    1, //UINT8_T
    2, //INT16_T
    2, //UINT16_T
    4, //INT32_T
    4, //UINT32_T

    4 //ANOTHER_FORMAT
};

uint8_t specifier_takes_argument(uint8_t specifier)
{
    uint8_t it_takes_an_argument = 0;
    
    // it_takes_an_argument += (specifier == ANOTHER_FORMAT);

    return it_takes_an_argument > 0;
}

uint8_t add_new_format_specifier(format* target, uint32_t specifier, uint32_t specifier_argument)
{
    if(!target) return FORMAT_ERROR_NO_FORMAT;
    if(specifier >= NUMBER_OF_FORMAT_SPECIFIERS) return FORMAT_ERROR_UNRECOGNIZED_SPECIFIER;

    uint8_t takes_argument = specifier_takes_argument(specifier);
    uint8_t specifier_size = 1 + takes_argument;

    uint32_t* new_specifier_list;
    if((target->current_index + specifier_size) > target->max_index)
    {
        new_specifier_list = (uint32_t*)realloc(target->specifiers, target->max_index *= 2);
        
        if(new_specifier_list == NULL) return FORMAT_ERROR_NO_MEMORY;

        target->specifiers = new_specifier_list;
    }

    target->specifiers[target->current_index++] = specifier;
    if(takes_argument)
        target->specifiers[target->current_index++] = specifier_argument;

    target->size += specifier_format_sizes[specifier];

    return FORMAT_NO_ERROR;
}

uint8_t free_format(format* target)
{
    if(!target) return FORMAT_ERROR_NO_FORMAT;

    realloc(target->specifiers,0);
    realloc(target,0);

    return FORMAT_NO_ERROR;
}

uint8_t free_data_buffer(data_buffer* target)
{
    if(!target) return DATA_ERROR_NO_BUFFER;

    uint32_t i = 0;
    for(;i <= target->max_chunk_index; i++)
        realloc(target->chunks[i].data,0);

    realloc(target->chunks,0);
    free_format(target->associated_format);
    realloc(target,0);
    target = NULL;

    return DATA_NO_ERROR;
}

#define DEFAULT_MAX_CHUNK_DATA_INDEX 0xff
data_buffer* create_data_buffer()
{
    data_buffer* new_buffer = (data_buffer*)malloc(sizeof(data_buffer));

    //allocate data buffer memory
    new_buffer->max_data_index = 0;
    new_buffer->max_chunk_index = 0;
    new_buffer->max_chunk_data_index = DEFAULT_MAX_CHUNK_DATA_INDEX;
    
    //create seed chunk
    data_chunk* chunk = (data_chunk*)malloc(sizeof(data_chunk));
    chunk->data = (uint8_t*)realloc(NULL, new_buffer->max_chunk_data_index);
    chunk->cached = 0;
    new_buffer->chunks = chunk;

    //
    new_buffer->associated_format = NULL;

    return new_buffer;
}

uint8_t resize_chunks(data_buffer* target, uint32_t new_max_chunk_data_index)
{
    if(!target) return DATA_ERROR_NO_BUFFER;
    if(target->max_chunk_data_index == new_max_chunk_data_index) return DATA_NO_ERROR;

    // IMPLEMENTATION_MISSING
}

uint8_t add_new_chunks(data_buffer* target, uint32_t number_of_additional_chunks)
{
    if(!target) return DATA_ERROR_NO_BUFFER;
    if(!number_of_additional_chunks) return DATA_NO_ERROR;

    //
    data_chunk* new_chunk_list = (data_chunk*)malloc(sizeof(data_chunk*)*(target->max_chunk_index + number_of_additional_chunks));

    uint32_t i = 0;
    for(;i <= target->max_chunk_index; i++)
        new_chunk_list[i] = target->chunks[i];

    for(;i <= target->max_chunk_index + number_of_additional_chunks; i++)
    {
        new_chunk_list[i].data = (uint8_t*)malloc(target->max_chunk_data_index*sizeof(uint8_t));
        new_chunk_list[i].cached = 0;
    }

    target->max_chunk_index += number_of_additional_chunks;

    free(target->chunks);
    target->chunks = new_chunk_list;

    return DATA_NO_ERROR;
}

uint8_t remove_chunk_range(data_buffer* target, uint32_t range_start, uint32_t range_end)
{
    if(!target) return DATA_ERROR_NO_BUFFER;
    if(range_start > target->max_chunk_index && range_end > target->max_chunk_index) return DATA_NO_ERROR;
    if(range_start > range_end)
    {
        uint32_t temp = range_end;
        range_end = range_start;
        range_start = temp;
    }
    if(range_end > target->max_chunk_index) range_end = target->max_chunk_index;
    
    //
    uint32_t range_length = range_end - range_start + 1;
    data_chunk* new_chunk_list = (data_chunk*)realloc(NULL,sizeof(data_chunk*)*(target->max_chunk_index - range_length));

    // uint32_t i = 0;
    // for(;i <= target->max_chunk_index; i++)
    // {
    //     new_chunk_list[i] = target->chunks[i];
    // }

    // for(;i <= target->max_chunk_index + number_of_additional_chunks; i++)
    // {
    //     data_chunk* chunk = (data_chunk*)malloc(sizeof(data_chunk));
    //     chunk->data = (uint8_t*)malloc(target->max_chunk_data_index*sizeof(uint8_t));
    //     chunk->cached = 0;
    //     new_chunk_list[i] = chunk;
    // }
    
    realloc(target->chunks,0);
    target->chunks = new_chunk_list;

    return DATA_NO_ERROR;
}
