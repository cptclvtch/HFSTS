#ifndef FLEXIBLE_FORMAT
#define FLEXIBLE_FORMAT

#include <stdlib.h>
#include <stdint.h>
#if defined(_WIN32) || defined(__LINUX__) || defined(__APPLE__)
#include <stdio.h>
#define FILE_TYPE FILE
#elif defined(__ANDROID__)

#endif

enum
{
    INT8_T,
    UINT8_T,
    INT16_T,
    UINT16_T,
    INT32_T,
    UINT32_T,

    // ANOTHER_FORMAT,

    NUMBER_OF_FORMAT_SPECIFIERS
};

typedef struct s_format
{
    uint32_t* specifiers;
    uint8_t current_index;
    uint8_t max_index;

    uint8_t size;
}format;

#define FORMAT_NO_ERROR 0
#define FORMAT_ERROR_NO_FORMAT 1
#define FORMAT_ERROR_NO_MEMORY 2
#define FORMAT_ERROR_UNRECOGNIZED_SPECIFIER 3

format* create_format();
uint8_t add_new_format_specified(format* target, uint32_t specifier, uint32_t specifier_argument);
uint8_t free_format(format* target);
//void load_format();
//void save_format();
//void attach_format_to_file_type();
//void attach_standard_formats();

#define DATA_NO_ERROR 0
#define DATA_ERROR_NO_BUFFER 1
typedef struct s_data_chunk data_chunk;

typedef struct s_data_chunk
{
    void* data;
    uint8_t cached;
}data_chunk;

typedef struct s_data_buffer
{
    data_chunk* chunks;
    uint32_t max_chunk_index;
    uint32_t max_chunk_data_index;
    uint32_t max_data_index;

    format* associated_format;
}data_buffer;

uint8_t free_data_buffer(data_buffer* target);
data_buffer* create_data_buffer();

#define BUFFER_AT(buffer,i) buffer->chunks[i/buffer->max_chunk_data_index]->data[i%buffer->max_chunk_data_index]

//Utility scripts
// void concatenate_data_buffers(data_buffer* target, data_buffer* source);
// void split_off_data_range(data_buffer* target, uint32_t split_index);

//void save_to_storage(data_buffer* target);
//void load_from_storage(data_buffer* target);
#endif