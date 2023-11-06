#include <stdlib.h>

//Node component
typedef struct s_node_component node_component;

typedef struct s_node_component
{
    char* strings; // null terminated string
    uint32_t integer_number;
    float float_number;

    node_component* children;
}node_component;

node_component* allocate_new_node_component();
void deallocate_node_component();

//Node
typedef struct s_node node;

typedef struct s_node
{
    // uint32_t id;
    
    node_component* components;
    uint32_t max_component_index;

    node* connections;
    uint32_t number_of_connections;

    node* children;
}node;

node* allocate_new_node();
void deallocate_node(node* target);

void add_node_component(node* target, node_component* component);
void add_connection(node* target, node* connection);