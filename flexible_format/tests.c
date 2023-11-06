#include "api.h"

#define PRINT_FN printf
#include "../unit_testing.c"

int main()
{
    data_chunk* chunk = (data_chunk*)malloc(sizeof(data_chunk));

    chunk->cached = 0;
    chunk->data = 0;

    list* data = (list*)malloc(sizeof(list));

    data->max_data_index = 10;
    data->max_chunk_index = 255;
    
    data->chunks = (data_chunk*)malloc();

    PRINT_FN("Hi\n");
}