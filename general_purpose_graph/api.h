#include <stdlib.h>

#define NODE_NO_ERROR 0
#define NODE_ERROR_NO_NODE 1
#define NODE_ERROR_NO_GRAPH 2
#define NODE_ERROR_NO_MEMORY 3
#define NODE_ERROR_UNDEFINED 4

#define NON_RECURSIVE 0
#define RECURSIVE 1

#ifndef REALLOC
#define REALLOC(pointer, size) pointer = realloc(pointer, size)
#endif

//Node context
enum
{
    NO_CONTEXT,
    CODE,
    
    NUMBER_OF_CONTEXT_TYPES,

    CONTEXT_GROUP = 255
};

//Node
typedef struct s_node node;

#define MAX_DATA_INDEX 15
typedef struct s_node
{
    uint32_t* data;

    uint8_t context;
}node;

node* create_node();
uint8_t free_node(node* target);

//Edges
#define NON_DIRECTED 0
#define DIRECTRED 1
typedef struct s_edge
{
    node* start;
    node* end;
    uint8_t type;

    node meta_data;
}edge;

#define DEFAULT_EDGE_LIST_SIZE 1024
uint8_t resize_edge_list(uint32_t new_index);

void flip_edge_direction(uint32_t edge_index);
void switch_edge_type(uint32_t edge_index);

uint8_t connect_existing_node(node* parent, node* target);
//uint8_t connect_new_node(node* parent);

// uint8_t abandon_child(node* target, uint32_t child_index);
// uint8_t murder_child(node* target, uint32_t child_index);

//Graph
typedef struct s_graph
{
    node** nodes;
    uint32_t max_node_index;
}graph;

graph* create_graph();
uint8_t free_graph(graph* target, uint8_t recursive);

// uint8_t save_graph(graph* target, char* path);
uint8_t load_graph(graph* target, char* path);

uint8_t add_graph_node(graph* target, node* to_add);
uint8_t add_new_graph_node(graph* target);

uint8_t delete_graph_node(graph* target, uint32_t node_index);

//Trash
// #define clear_trash free_graph
// uint8_t trash_node(graph* target, uint32_t node_index);