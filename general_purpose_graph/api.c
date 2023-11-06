#include "api.h"

//Node component
node_component* allocate_new_node_component()
{
    node_component* new_component;

    new_component = (node_component*)malloc(sizeof(node_component));

    return new_component;
}

void deallocate_node_component(node_component* target)
{
    //recursive free component tree
    if(target->children) deallocate_node_component(target->children);
    free(target);
}

//Node
node* allocate_new_node()
{
    node* new_node;

    new_node = (node*)malloc(sizeof(node));

    new_node->components = allocate_new_node_component();
    new_node->max_component_index = 0;
    new_node->connections = NULL;
    new_node->number_of_connections = 0;

    return new_node;
}

void deallocate_node(node* target)
{
    deallocate_node_component(target->node_components);
    free(target->connections);

    free(target);
}

// void add_node_component(node* target, node_component* component)
// {

// }

// void add_connection(node* target, node* connection)
// {

// }