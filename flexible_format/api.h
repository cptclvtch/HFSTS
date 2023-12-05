#ifndef FLEXIBLE_FORMAT
#define FLEXIBLE_FORMAT

// #include <stdint.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(__LINUX__) || defined(__APPLE__)
#include <stdio.h>
#define FILE_TYPE FILE
#elif defined(__ANDROID__)

#endif

typedef struct s_data_chunk{
    uint8_t* data;

    uint8_t cached;
}data_chunk;

typedef struct s_data_buffer{
    data_chunk* chunks;
    uint32_t max_chunk_index;
    uint32_t max_chunk_data_index;
    uint32_t max_data_index;
}data_buffer;

void free_data_buffer(data_buffer* target);
data_buffer* create_data_buffer(data_buffer* target);
void resize_chunks(data_buffer* target, uint32_t new_max_chunk_index);

//Hidden utility scripts
void add_new_chunks(data_buffer* target, uint32_t number_of_additional_chunks);
void remove_chunk_range(data_buffer* target, uint32_t range_start, uint32_t range_end);

//Utility scripts
// void concatenate_data_buffers(data_buffer* target, data_buffer* source);
// void split_off_data_range(data_buffer* target, uint32_t split_index);

//void save_to_storage(data_buffer* target);
//void load_from_storage(data_buffer* target);

//Format utilities
//void create_format();
//void load_format();
//void save_format();
//void attach_format_to_file_type();
//void attach_standard_formats();

#endif