#include <stdlib.h>

/*Data structs*/
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

//Node storage?

/*Functions*/
node* allocate_new_node();
void deallocate_node(node* target);