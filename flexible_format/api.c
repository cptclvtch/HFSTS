#include "api.h"

void free_data_buffer(data_buffer* target)
{
    if(!target) return;

    uint32_t i = 0;
    for(;i <= target->max_chunk_index; i++)
        free(target->chunks[i]); problem here

    free(target->chunks);
    free(target);
}

data_buffer* create_data_buffer(data_buffer* target)
{
    if(!target) return;

    //allocate data buffer memory
    target->max_data_index = 0;
    target->max_chunk_index = 0;
    target->max_chunk_data_index = 0xff;
    
    target->chunks = (data_chunk*)malloc(sizeof(data_chunk*));
    
    //create seed chunk
    data_chunk chunk = (data_chunk*)malloc(sizeof(data_chunk)); problem here
    chunk->data = (uint8_t*)malloc(target->max_chunk_data_index*sizeof(uint8_t));
    chunk->cached = 0;

    //assign seed chunk
    target->chunks = chunk;

    return target;
}

void resize_chunks(data_buffer* target, uint32_t new_max_chunk_data_index)
{
    if(!target) return;

    if(target->max_chunk_data_index == new_max_chunk_data_index) return;

    // IMPLEMENTATION_MISSING
}

void add_new_chunks(data_buffer* target, uint32_t number_of_additional_chunks)
{
    if(!target) return;
    if(!number_of_additional_chunks) return;

    //
    data_chunk* new_chunk_list = (data_chunk*)malloc(sizeof(data_chunk*)*(target->max_chunk_index + number_of_additional_chunks));

    uint32_t i = 0;
    for(;i <= target->max_chunk_index; i++)
    {
        new_chunk_list[i] = target->chunks[i];
    }

    for(;i <= target->max_chunk_index + number_of_additional_chunks; i++)
    {
        data_chunk* chunk = (data_chunk*)malloc(sizeof(data_chunk));
        chunk->data = (uint8_t*)malloc(target->max_chunk_data_index*sizeof(uint8_t));
        chunk->cached = 0;
        new_chunk_list[i] = chunk;
    }

    target->max_chunk_index += number_of_additional_chunks;

    free(target->chunks);
    target->chunks = new_chunk_list;
}

void remove_chunk_range(data_buffer* target, uint32_t range_start, uint32_t range_end)
{
    if(!target) return;
    if(range_start > target->max_chunk_index && range_end > target->max_chunk_index) return;
    if(range_start > range_end)
    {
        uint32_t temp = range_end;
        range_end = range_start;
        range_start = temp;
    }
    if(range_end > target->max_chunk_index) range_end = target->max_chunk_index;
    
    //
    uint32_t range_length = range_end - range_start + 1;
    data_chunk* new_chunk_list = (data_chunk*)malloc(sizeof(data_chunk*)*(target->max_chunk_index - range_length));



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
    
    free(target->chunks);
    target->chunks = new_chunk_list;
}
