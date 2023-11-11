#include "api.h"

//Node component
node_component* allocate_new_node_component()
{
    node_component* new_component;

    new_component = (node_component*)malloc(sizeof(node_component));

    return new_component;
}

uint8_t deallocate_node_component(node_component* target)
{
    if(!target) return NODE_ERROR_NO_NODE;

    //recursive free component tree
    // if(target->children) deallocate_node_component(target->children);
    free(target);

    return NODE_NO_ERROR;
}

//Node
node* allocate_new_node()
{
    node* new_node;

    new_node = (node*)malloc(sizeof(node));

    if(!new_node) return 0;

    new_node->components = allocate_new_node_component();
    new_node->max_component_index = 0;
    // new_node->connections = NULL;
    // new_node->number_of_connections = 0;

    return new_node;
}

uint8_t deallocate_node(node* target)
{
    if(!target) return NODE_ERROR_NO_NODE;

    deallocate_node_component(target->components);
    // free(target->connections);

    free(target);

    return NODE_NO_ERROR;
}

//Utilities
uint8_t add_existing_node_component(node* target, node_component* component)
{
    if(!target) return NODE_ERROR_NO_NODE;
    if(!component) return NODE_ERROR_NO_COMPONENT;

    target->max_component_index++;

    node_component* new_component_list;

    new_component_list = (node_component*)malloc(sizeof(node_component)*target->max_component_index+1);

    if(!new_component_list) return NODE_ERROR_NO_MEMORY;

    uint32_t i = 0;
    for(; i < target->max_component_index; i++)
        new_component_list[i] = target->components[i];

    new_component_list[i] = target->components[i];

    free(target->components);
    target->components = new_component_list;

    return NODE_NO_ERROR;
}

node_component* add_new_node_component(node* target)
{
    if(!target) return;

    node_component* component;
    component = allocate_new_node_component();
    
    if(!component) return;
    
    uint8_t result = add_existing_node_component(target, component);
    
    if(result)
    {
        deallocate_node_component(component);
        return;
    }

    return component;
}

// uint8_t add_connection(node* target, node* connection)
// {
//      return NODE_NO_ERROR;
// }