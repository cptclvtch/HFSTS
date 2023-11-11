#include <stdlib.h>

#define NODE_NO_ERROR 0
#define NODE_ERROR_NO_NODE 1
#define NODE_ERROR_NO_COMPONENT 2
#define NODE_ERROR_NO_MEMORY 3

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

node_component* allocate_new_node_component();
uint8_t deallocate_node_component(node_component* target);
// uint8_t add_child_component(node_component* target, node_component* child);

//Node
typedef struct s_node node;

typedef struct s_node
{
    // uint32_t id;

    float x,y,z;
    float width,height;
    
    node_component* components;
    uint32_t max_component_index;

    // node* connections;
    // uint32_t number_of_connections;
}node;

node* allocate_new_node();
uint8_t deallocate_node(node* target);

//Utilities
uint8_t add_existing_node_component(node* target, node_component* component);
node_component* add_new_node_component(node* target);
// uint8_t add_connection(node* target, node* connection);