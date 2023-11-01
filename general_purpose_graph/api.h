#include <stdlib.h>

//Node component
typedef struct s_node_component node_component;

typedef struct s_node_component
{
    char** strings;
    uint32_t number_of_strings;
    uint32_t* integers;
    uint32_t number_of_integers;
    float* floats;
    uint32_t number_of_floats;

    node_component* children;
}node_component;

node_component* allocate_new_node_component();
void deallocate_node_component();

//Node
typedef struct s_node node;

typedef struct s_node
{
    uint32_t id;
    
    node_component* components;
    uint32_t number_of_components;

    node* connections;
    uint32_t number_of_connections;

    node* children;
}node;

// void add_node_component(node* target, node_component* )

// node* allocate_new_node();
// void deallocate_node(node* target);