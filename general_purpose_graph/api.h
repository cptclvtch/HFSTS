#include <stdlib.h>

#define NODE_NO_ERROR 0
#define NODE_ERROR_NO_NODE 1
#define NODE_ERROR_NO_COMPONENT 2
#define NODE_ERROR_NO_GRAPH 3
#define NODE_ERROR_NO_MEMORY 4

//Node component
typedef struct s_node_component node_component;

typedef struct s_node_component
{
    //Data
    char* text;
    uint32_t integer_number;
    float float_number;

    //
    // node_component* children;
    // uint32_t number_of_children;
}node_component;

node_component* create_node_component();
uint8_t free_node_component(node_component* target);
// uint8_t add_child_component(node_component* target, node_component* child);

//Node
typedef struct s_node node;

typedef struct s_node
{
    // uint32_t id;

    float x,y,z;
    float width,height;
    
    node_component** components;
    uint32_t max_component_index;

    // node* connections;
    // uint32_t number_of_connections;

    //node* children;
    //uint32_t number_of_children;
}node;

node* create_node();
uint8_t free_node(node* target);

//Graph
typedef struct s_graph
{
    node** nodes;
    uint32_t size;
}graph;

graph* create_graph();
uint8_t free_graph(graph* target);
uint8_t add_graph_node(graph* target, node* to_add);
// uint8_t remove_graph_node();

//Utilities
uint8_t add_existing_node_component(node* target, node_component* component);
uint8_t add_new_node_component(node* target);
// uint8_t add_connection(node* target, node* connection);