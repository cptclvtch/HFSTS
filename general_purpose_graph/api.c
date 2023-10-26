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
    free(target);
}

//Node
node* allocate_new_node()
{
    node new_node;

    new_node = (node*)malloc(sizeof(node));

    return &new_node;
}

void deallocate_node(node* target)
{
    free(target);
}